/**
 * @author      : dog head
 * @date        : Created in 2022/1/17
 * @mail        : 396139919@qq.com
 * @project     : pool
 * @file        : pool.go
 * @description : core pool
 */

package taskpool

import (
	"errors"
)

const (
	overMaxNumber   = "init number is over max number"
	maxNumberError  = "max number input err"
	initNumberError = "init number input err"
)

// 接口实现验证
var _ Pool = (*pool)(nil)

func checkOption(option *Option) error {
	if option.MaxWorkerNumb < 0 {
		return errors.New(maxNumberError)
	}
	if option.MaxWorkerNumb < 0 {
		return errors.New(initNumberError)
	}
	if option.InitWorkerNumb > option.MaxWorkerNumb {
		return errors.New(overMaxNumber)
	}

	return nil
}

func NewPool(option *Option) (*pool, error) {
	if nil == option {
		goto defaultInit
	} else {
		err := checkOption(option)
		if nil != err {
			return nil, err
		}

		p := pool{
			maxWorkerNumb: option.MaxWorkerNumb,
		}
		p.initPoolWorker(option.InitWorkerNumb)

		return &p, nil
	}

defaultInit:
	p := pool{
		maxWorkerNumb: 0,
	}
	return &p, nil
}

func (p *pool) initPoolWorker(numb int) {
	for i := 0; i < numb; i++ {
		p.workerQueue = append(p.workerQueue, newWorker(p))
	}
}

func (p *pool) taskStartTrigger(w *worker) {
	p.locker.Lock()

	if len(p.taskWaiteQueue) == 0 { // 如果没有任务等待，则重新将执行完毕的worker加入可用队列
		p.workerQueue = append(p.workerQueue, w)
	} else { // 如果有任务在等待，则直接使用worker
		t := p.taskWaiteQueue[0]
		p.taskWaiteQueue = p.taskWaiteQueue[1:]
		w.Go(t)
	}
	p.locker.Unlock()
}

func (p *pool) Go(tFunc taskFunc, params ...interface{}) {
	t := taskImpl{
		tFunc:  tFunc,
		params: params,
	}

	var w *worker
	p.locker.Lock()
	if len(p.workerQueue) != 0 { // worker仍存在空闲,取出执行
		w = p.workerQueue[len(p.workerQueue)-1]
		p.workerQueue = p.workerQueue[0 : len(p.workerQueue)-1]
		w.Go(t)
	} else { // worker无空闲

		if p.maxWorkerNumb == 0 ||
			(p.maxWorkerNumb > 0 &&
				p.currentWorkerNumb < p.maxWorkerNumb) { // 区分worker限制：1.worker无限制；2.有限制未达到；
			p.newWorkerWithTask(t)
		} else { // 达到限制则放入排队队列
			p.taskWaiteQueue = append(p.taskWaiteQueue, t)
		}
	}
	p.locker.Unlock()
}

func (p *pool) newWorkerWithTask(task taskImpl) {
	w := newWorker(p)
	w.start()
	w.Go(task)
	p.currentWorkerNumb++
}

func (p *pool) GetCurrentStatus() Status {
	return Status{
		TotalWorkerNumber : p.currentWorkerNumb,
		workerQueueNumber : len(p.workerQueue),
		taskWaitingNUmber : len(p.taskWaiteQueue),
	}
}

func (p *pool) KillIdleWorkers() {
	p.locker.Lock()
	for _, w := range p.workerQueue {
		w.stop()
	}
	p.workerQueue = p.workerQueue[0:0]
	p.locker.Unlock()
}
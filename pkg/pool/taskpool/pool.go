/**
 * @author      : dog head
 * @date        : Created in 2022/1/17
 * @mail        : 396139919@qq.com
 * @project     : pool
 * @file        : pool.go
 * @description : core pool
 */

package taskpool

import "errors"

const (
	overMaxNumber = "init number is over max number"
	maxNumberError = "max number input err"
	initNumberError = "init number input err"
)

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

func Newpool(option *Option) (*pool, error) {
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
		p.initpoolWorker(option.InitWorkerNumb)

		return &p, nil
	}

defaultInit:
	p := pool{
		maxWorkerNumb: 0,
	}
	return &p, nil
}

func (p *pool) initpoolWorker(numb int){
	for i := 0; i < numb; i++ {
		p.workerQueue = append(p.workerQueue, newWorker())
	}
}

func (p *pool) taskStartTrigger(w *worker) {
	p.locker.Lock()
	

}
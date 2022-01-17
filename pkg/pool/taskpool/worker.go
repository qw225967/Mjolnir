/**
 * @author      : dog head
 * @date        : Created in 2022/1/17
 * @mail        : 396139919@qq.com
 * @project     : pool
 * @file        : worker.go
 * @description : worker impl
 */

package taskpool

func newWorker(p *pool) *worker {
	return &worker{
		taskChan:     make(chan taskImpl),
		poolInstance: p,
	}
}

func (w *worker) start() {
	go func() {
		for {
			task, ok := <-w.taskChan
			if !ok {
				return
			}
			task.tFunc(task.params)

			// 完成后触发钩子，重新将worker加入待工作队列
			w.poolInstance.taskStartTrigger(w)
		}
	}()
}

func (w *worker) stop() {
	close(w.taskChan)
}

func (w *worker) Go(t taskImpl) {
	w.taskChan <- t
}

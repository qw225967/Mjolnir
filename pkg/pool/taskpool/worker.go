/**
 * @author      : dog head
 * @date        : Created in 2022/1/17
 * @mail        : 396139919@qq.com
 * @project     : pool
 * @file        : worker.go
 * @description : worker impl
 */

package taskpool

func newWorker() *worker {
	return &worker{
		task: make(chan taskImpl),
	}
}

func (w *worker) start() {
	go func() {
		task := <- w.task
		task.tFunc()
		w.poolInstance.taskStartTrigger(w)
	}()
}

func (w *worker) stop() {
	close(w.task)
}

func (w *worker) Go(t taskImpl) {
	w.task <- t
}

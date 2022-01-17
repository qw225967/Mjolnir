/**
 * @author      : dog head
 * @date        : Created in 2022/1/17
 * @mail        : 396139919@qq.com
 * @project     : pool
 * @file        : model.go
 * @description : struct for task pool
 */

package taskpool

import "sync"

/* -------------- core struct -------------- */
type pool struct {
	maxWorkerNumb     int
	currentWorkerNumb int

	locker      sync.Mutex
	workerQueue []*worker
}

// worker内部包含上层pool的实例，用于交互
type worker struct {
	task         chan taskImpl
	poolInstance *pool
}

type taskFunc func()

type taskImpl struct {
	tFunc	taskFunc
}

/* -------------- core struct -------------- */

/* -------------- input struct -------------- */
type Option struct {
	InitWorkerNumb int
	MaxWorkerNumb  int
}

/* -------------- input struct -------------- */

/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/1/17
 * @mail        : 396139919@qq.com
 * @project     : pool
 * @file        : model.go
 * @description : struct for task pool
 *******************************************************/

package taskpool

import "sync"

/* -------------- core struct -------------- */
type pool struct {
	maxWorkerNumb     int
	currentWorkerNumb int
	needDestroyNumb	  int

	locker         sync.Mutex
	workerQueue    []*worker
	taskWaiteQueue []taskImpl
}

// worker内部包含上层pool的实例，用于交互
type worker struct {
	taskChan     chan taskImpl
	poolInstance *pool
}

type taskFunc func(params ...interface{})

type taskImpl struct {
	tFunc  taskFunc
	params []interface{}
}


/* -------------- input struct -------------- */
type Option struct {
	InitWorkerNumb int
	MaxWorkerNumb  int
}


/* -------------- output struct -------------- */
type Status struct {
	TotalWorkerNumber int	// 当前总协程数
	WorkerQueueNumber int	// 当前可用的worker数
	TaskWaitingNUmber int	// 正在排队的任务数
}

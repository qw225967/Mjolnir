/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/1/17
 * @mail        : 396139919@qq.com
 * @project     : pool
 * @file        : interface.go
 * @description : interface for task pool
 *******************************************************/

package taskpool

type Pool interface {
	// 非阻塞
	Go(tFunc taskFunc, params ...interface{})

	// 获取当前协程池的状态
	GetCurrentStatus() Status

	// 关闭所有空闲的协程
	KillIdleWorkers()

	// 修改最大协程数
	ChangeMaxWorkersNumber(num int)
}

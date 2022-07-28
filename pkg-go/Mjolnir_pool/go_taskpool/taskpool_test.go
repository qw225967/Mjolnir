/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/1/17
 * @mail        : 396139919@qq.com
 * @project     : pool
 * @file        : taskpool_test.go
 * @description : TODO
 *******************************************************/

package taskpool_test

import (
	"fmt"
	"sync"
	"sync/atomic"
	"testing"

	"github.com/Mjolnir/pkg-go/Mjolnir_pool/go_taskpool"
)

func TestNewPoolNewPool(t *testing.T) {
	pool,_ := taskpool.NewPool(&taskpool.Option{
		MaxWorkerNumb: 4,
	})
	var sum int32
	var wg sync.WaitGroup
	n := 1000
	wg.Add(n)
	for i := 0; i < n; i++ {
		pool.Go(func(param ...interface{}) {
			ii := param[0].(int)
			atomic.AddInt32(&sum, int32(ii))
			fmt.Printf("sum: %v \n", sum)
			wg.Done()
		}, i)
	}
	wg.Wait()
	fmt.Println(sum)
}

func TestPool_ChangeMaxWorkersNumber(t *testing.T) {
	pool, _ := taskpool.NewPool(&taskpool.Option{
		MaxWorkerNumb: 4,
	})
	var sum int32
	var wg sync.WaitGroup
	n := 1000
	wg.Add(n)
	for i := 0; i < n; i++ {
		if i >= 8 {
			pool.ChangeMaxWorkersNumber(8)
			fmt.Println("----------------")
			fmt.Println(pool.GetCurrentStatus().TotalWorkerNumber)
			fmt.Println(pool.GetCurrentStatus().WorkerQueueNumber)
			fmt.Println(pool.GetCurrentStatus().TaskWaitingNUmber)
			fmt.Println("----------------")
		}
		if i >= 16 {
			pool.ChangeMaxWorkersNumber(16)
			fmt.Println("----------------")
			fmt.Println(pool.GetCurrentStatus().TotalWorkerNumber)
			fmt.Println(pool.GetCurrentStatus().WorkerQueueNumber)
			fmt.Println(pool.GetCurrentStatus().TaskWaitingNUmber)
			fmt.Println("----------------")
		}
		pool.Go(func(param ...interface{}) {
			ii := param[0].(int)
			atomic.AddInt32(&sum, int32(ii))
			wg.Done()
		}, i)
	}
	wg.Wait()
	fmt.Println(sum)
	// Output:
	// 499500
}
/**
 * @author      : dog head
 * @date        : Created in 2022/1/17
 * @mail        : 396139919@qq.com
 * @project     : pool
 * @file        : taskpool_test.go
 * @description : TODO
 */

package taskpool_test

import (
	"fmt"
	"sync"
	"sync/atomic"
	"testing"

	"github.com/Mjolnir/pkg/pool/taskpool"
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
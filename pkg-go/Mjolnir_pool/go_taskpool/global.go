/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/1/17
 * @mail        : 396139919@qq.com
 * @project     : pool
 * @file        : global.go
 * @description : TODO
 *******************************************************/

package taskpool

var globalPoolInstance_ *pool

func Go(tFunc taskFunc, params ...interface{}) {
	globalPoolInstance_.Go(tFunc, params...)
}

func GetCurrentStatus() Status {
	return globalPoolInstance_.GetCurrentStatus()
}

func KillIdleWorkers() {
	globalPoolInstance_.KillIdleWorkers()
}


func Init(option *Option) error {
	var err error
	globalPoolInstance_, err = NewPool(&Option{})
	return err
}

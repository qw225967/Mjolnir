/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/2/7
 * @mail        : 396139919@qq.com
 * @project     : Mjolnir
 * @file        : mchannel_test.go
 * @description : TODO
 *******************************************************/

package mchannel

import (
	"fmt"
	"testing"
)

func TestIsChannelClosed(t *testing.T) {
	//ch := make(chan int)
	ch := make(chan string)
	fmt.Println(IsChannelClosed(ch))
	close(ch)
	fmt.Println(IsChannelClosed(ch))
}

func TestSafeClose(t *testing.T) {
	ch := make(chan T)
	close(ch)
	//close(ch) // panic
	fmt.Println(SafeClose(ch))  // false
}
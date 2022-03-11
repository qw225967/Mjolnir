/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/2/7
 * @mail        : 396139919@qq.com
 * @project     : Mjolnir
 * @file        : mchannel.go
 * @description : TODO
 *******************************************************/

package mchannel

import (
	"reflect"
	"unsafe"
)

/********************************************************************
 * 这个函数会返回 chan.closed > 0
 * chan的结构体地址空间如下，操作地址返回closed即可
 * type hchan struct {
 * 	   qcount   uint
 *	   dataqsiz uint
 *	   buf      unsafe.Pointer
 *	   elemsize uint16
 *	   closed   uint32
 *	   elemtype *_type
 *	   sendx    uint
 *	   recvx    uint
 *	   recvq    waitq
 *	   sendq    waitq
 *
 *	   lock mutex
 * }
 *********************************************************************/
func IsChannelClosed(ch interface{}) bool {
	if reflect.TypeOf(ch).Kind() != reflect.Chan {
		panic("only channels!")
	}
	cptr := *(*uintptr)(unsafe.Pointer(uintptr(unsafe.Pointer(&ch)) + unsafe.Sizeof(uint(0))))

	cptr += unsafe.Sizeof(uint(0))*2
	cptr += unsafe.Sizeof(unsafe.Pointer(uintptr(0)))
	cptr += unsafe.Sizeof(uint16(0))
	return *(*uint32)(unsafe.Pointer(cptr)) > 0
}


// 如果你非要从接收端关闭channel或者在多个发送者中关闭channel
// 请使用以下函数帮助你做panic恢复
type T int // 修改成任何一个需要channel传输的类型

func SafeClose(ch chan T) (closed bool) {
	defer func() {
		if recover() != nil {
			closed =  false
		}
	}()

	close(ch)
	return true
}



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
 * this function will return true if chan.closed > 0
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


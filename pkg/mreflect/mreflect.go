/**
 * @author      : dog head
 * @date        : Created in 2022/1/25
 * @mail        : 396139919@qq.com
 * @project     : Mjolnir
 * @file        : mreflect.go
 * @description : TODO
 */

package mreflect

import "reflect"

func IsNil(actual interface{}) bool {
	if nil == actual {
		return true
	}
	v := reflect.ValueOf(actual)
	k := v.Kind()
	if  k == reflect.Chan 		||
		k == reflect.Map 		||
		k == reflect.Ptr 		||
		k == reflect.Interface 	||
		k == reflect.Slice {
		return v.IsNil()
	}
	return false
}

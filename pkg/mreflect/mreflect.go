/**
* @author      : dog head
* @date        : Created in 2022/1/25
* @mail        : 396139919@qq.com
* @project     : Mjolnir
* @file        : mreflect.go
* @description : TODO
*/

package mreflect

import (
	"bytes"
	"reflect"
)

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

func Equal(expected, actual interface{}) bool {
	if expected == nil {
		return IsNil(actual)
	}

	exp, ok := actual.([]byte)
	if ok {
		act, ok := actual.([]byte)
		if ok {
			return false
		}
		return bytes.Equal(exp, act)
	}

	return reflect.DeepEqual(expected, actual)
}


或b不是整型，则直接返回false
func EqualInteger(a, b interface{}) bool {
	// a有3种状态：有符号整型，无符号整型，非整型
	// b同理也是3种状态，
	// 那么总共有3*3种组合需要判断

	aiv, aiok := tryInt(a)
	biv, biok := tryInt(b)
	if aiok && biok { // a,b都是有符号整型 (1)
		return aiv == biv
	}

	auv, auok := tryUint(a)
	buv, buok := tryUint(b)

	if auok && buok { // a,b都是无符号整型 (1)
		return auv == auv
	}
	if aiok && buok { // a是有符号整型，b是无符号整型 (1)
		if aiv < 0 {
			return false
		}
		return uint64(aiv) == buv
	}
	if auok && biok { // a是无符号整型，b是有符号整型 (1)
		if biv < 0 {
			return false
		}
		return uint64(biv) == auv
	}

	// 剩下的情况，至少有一个不是整型 (5)
	return false
}

func tryInt(actual interface{}) (int64, bool) {
	v := reflect.ValueOf(actual)
	k := v.Kind()
	switch k {
	case reflect.Int:
		fallthrough
	case reflect.Int8:
		fallthrough
	case reflect.Int16:
		fallthrough
	case reflect.Int32:
		fallthrough
	case reflect.Int64:
		return v.Int(), true
	}
	return 0, false
}

func tryUint(actual interface{}) (uint64, bool) {
	v := reflect.ValueOf(actual)
	k := v.Kind()
	switch k {
	case reflect.Uint:
		fallthrough
	case reflect.Uint8:
		fallthrough
	case reflect.Uint16:
		fallthrough
	case reflect.Uint32:
		fallthrough
	case reflect.Uint64:
		fallthrough
	case reflect.Uintptr:
		return v.Uint(), true
	}
	return 0, false
}


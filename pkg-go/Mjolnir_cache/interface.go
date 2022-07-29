/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/7/28
 * @mail        : 396139919@qq.com
 * @project     : Mjolnir
 * @file        : interface.go
 * @description : TODO
 *******************************************************/

package Mjolnir_cache

type MjolnirCache interface {
	Cache(business string, Items ...Item) error
	GetAllItemByBusiness(business string) (map[string]string, error)
}
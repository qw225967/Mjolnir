/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/7/28
 * @mail        : 396139919@qq.com
 * @project     : Mjolnir
 * @file        : cache_mgr.go
 * @description : TODO
 *******************************************************/

package Mjolnir_cache

import (
	"errors"
	"fmt"
	"sync"

	"github.com/go-redis/redis"
)

// 接口实现验证
var _ MjolnirCache = (* cacheManager)(nil)

var cacheManagerGlobal_ *cacheManager
var cacheManagerGlobalOnce_ sync.Once

type cacheManager struct {
	BusinessItemList map[string]map[string]Item

	RedisClient *redis.Client
	locker sync.Mutex
}

// 获取缓存器单例
func GetCacheManager() *cacheManager {
	if cacheManagerGlobal_ != nil {
		return cacheManagerGlobal_
	}
	return nil
}

func InitCacheManager(option CacheOption) error {

	// 测试redis连接
	if option.RedisClient != nil {
		status, err := option.RedisClient.Ping().Result()
		if err != nil {
			return err
		} else {
			fmt.Printf("[Mjolnir] InitCachaManager status %s", status)
		}
	}
	cacheManagerGlobalOnce_.Do(func() {
		cacheManagerGlobal_ = &cacheManager{
			BusinessItemList: make(map[string]map[string]Item),
			RedisClient:      option.RedisClient,
		}
	})

	return nil
}

// 按业务区分缓存任务
func (mgr *cacheManager) Cache(business string, Items ...Item) error {
	var m map[string]Item

	// 检查是否存在
	mgr.locker.Lock()
	defer mgr.locker.Unlock()

	if _, ok:= mgr.BusinessItemList[business]; ok {
		m = mgr.BusinessItemList[business]
	} else {
		m = make(map[string]Item)
	}


	for _, v := range Items {
		m[v.Key] = v
		err := mgr.setItemToRedis(business, v)
		if err != nil {
			return err
		}
	}

	mgr.BusinessItemList[business] = m
	return nil
}

func (mgr *cacheManager) GetAllItemByBusiness(business string) (map[string]string, error){
	if _, ok := mgr.BusinessItemList[business];ok {
		result, err := mgr.getAllItemByRedis(business)
		if err != nil {
			return nil, err
		}
		return result, nil
	}
	return nil, errors.New("business is not find")
}


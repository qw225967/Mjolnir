/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/7/28
 * @mail        : 396139919@qq.com
 * @project     : Mjolnir
 * @file        : mjolnir_cache_test.go
 * @description : TODO
 *******************************************************/

package Mjolnir_cache

import (
	"fmt"
	"github.com/go-redis/redis"
	"testing"
)

func TestCacheManager_Cache(t *testing.T) {
	client := redis.NewClient(&redis.Options{
		Addr: "127.0.0.1:6379",
		MaxRetries: 3,
	})

	_ = InitCacheManager(CacheOption{
		RedisClient: client,
	})

	mgr := GetCacheManager()

	if mgr != nil {
		_ = mgr.Cache("test", Item{
			Key: "AABBCC",
			Contents: "valueAABBCC",
		})

		result, _ := mgr.GetAllItemByBusiness("test")
		for k, v := range result {
			fmt.Println(k)
			fmt.Println(v)
		}
	}


}
/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/7/28
 * @mail        : 396139919@qq.com
 * @project     : Mjolnir
 * @file        : cache_helper.go
 * @description : TODO
 *******************************************************/

package Mjolnir_cache

import (
	"errors"
	"fmt"
)

const (
	MJOLNIR_CACHE_REDISKEY_PRE = "MJOLNIR_CACHE_REDISKEY_PRE_"
)

func (mgr *cacheManager) setItemToRedis(business string, item Item) error {
	if mgr.RedisClient != nil {
		businessKey := MJOLNIR_CACHE_REDISKEY_PRE + business

		_, err := mgr.RedisClient.HSet(businessKey, item.Key, item.Contents).Result()
		if err != nil {
			return err
		} else {
			fmt.Printf("[Mjolnir] HSet status by [business Key:%s, item Key:%s]\n",
				businessKey, item.Key)
		}
	} else {
		return errors.New("redis client is nil")
	}
	return nil
}

func (mgr *cacheManager) getItemByRedis(business, itemKey string) (string, error) {
	var result string
	if mgr.RedisClient != nil {
		businessKey := MJOLNIR_CACHE_REDISKEY_PRE + business

		value, err := mgr.RedisClient.HGet(businessKey, itemKey).Result()
		if err != nil {
			return "", err
		} else {
			result = value
			fmt.Printf("[Mjolnir] HGet by [business Key:%s, item Key:%s, value:%s]\n",
				businessKey, itemKey, value)
		}
	} else {
		return "", errors.New("redis client is nil")
	}
	return result, nil
}

func (mgr *cacheManager) getAllItemByRedis(business string) (map[string]string, error){
	var result map[string]string
	if mgr.RedisClient != nil {
		businessKey := MJOLNIR_CACHE_REDISKEY_PRE + business

		value, err := mgr.RedisClient.HGetAll(businessKey).Result()
		if err != nil {
			return result, err
		} else {
			result = value
		}
	} else {
		return result, errors.New("redis client is nil")
	}
	return result, nil
}
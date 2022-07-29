/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/7/28
 * @mail        : 396139919@qq.com
 * @project     : Mjolnir
 * @file        : model.go
 * @description : TODO
 *******************************************************/

package Mjolnir_cache

import (
	"github.com/go-redis/redis"
)

// 初始化内容
// 两种存储方式：本地文件存储 和 数据库存储（redis）
type CacheOption struct {
	// 本地存储
	Path string

	// 数据库存储
	// redis 需要外部进行数据库初始化
	RedisClient *redis.Client
}


// 缓存内容
type Item struct {
	Key      string
	Contents string
}
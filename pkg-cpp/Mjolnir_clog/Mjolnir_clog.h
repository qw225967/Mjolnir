/*******************************************************
 * @author      : dog head
 * @modified    : 2022-03-11 15:58
 * @mail        : qw225967@github.com
 * @file        : Mjolnir_clog.h
 * @idea        : vim
 * @description : TODO
 *******************************************************/

#ifndef __MJOLNIR_LOG_H__
#define __MJOLNIR_LOG_H__

#include <pthread.h>
#include <string>

#include "Buffer.h"
#include "UTC_Timer.h"

namespace mjolnir {
  enum _MJOLNIR_LOG_ENUM {
    FATAL = 1,
    ERROR,
    WARN,
    INFO,
    DEBUG,
    TRACE,
    };

  class MjolnirCLog {
  public:
    /* ---------------- init ---------------- */
    static MjolnirCLog* GetInstance() {
      pthread_once(&once_, MjolnirCLog::InitInstance);
      return single_instance_; 
    }

    /* ---------------- business ---------------- */
    void SetInitParams(std::string path, std::string name, _MJOLNIR_LOG_ENUM level, uint32_t buffer_capacity );
    int GetLevel() const { return level_; }
    void TryAppend(const char* lvl, const char* format, ...);
    void StartLogWriting() {
      while(true) {
        Write2Disk();
      }
    }

  private:
    MjolnirCLog();
    ~MjolnirCLog();
    MjolnirCLog(const MjolnirCLog&);
    const MjolnirCLog& operator=(const MjolnirCLog&);

    static void InitInstance() {
      while(!single_instance_) single_instance_ =  new MjolnirCLog;
    }

    void Write2Disk();
    void WritingBufferFreeWait();
    bool FileProcessor(int year, int month, int day);
    void FileGenerator(int year, int month, int day);
    void FileRenameAndGenerator();
    std::string GetLogoString();

  private:
    // lazy singleton 
    static pthread_once_t once_;
    static MjolnirCLog * single_instance_;
    static pthread_mutex_t mutex_;
    static pthread_cond_t cond_;

    // info
    std::string log_path_;
    std::string name_;
    int level_;
    uint32_t buffer_capacity_; // 单个buffer容量
    int node_count_; // buffer 节点计数

    FILE* file_fp_;
    int log_count_; // 用于记录超限制大小的日志量计数

    int year_;
    int month_;
    int day_;
    int pid_;

    _UTC_TIMER utc_timer_;
    uint64_t last_lts_;   //日志无法写入的最后时间，如果值不为0则证明日志无法写入，并且值为最后无法写入的时间

    // list operation
    // 当前节点
    Buffer* current_node_;
    // 最后的节点
    Buffer* last_node_;
    // 待写硬盘的节点
    Buffer* writing_node_;
  };

} // mjolnir


#endif // __MJOLNIR_LOG_H__

/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/3/14 3:27 下午
 * @mail        : qw225967@github.com
 * @project     : Mjolnir_clog
 * @file        : Mjolnir_clog_header.h
 * @description : TODO
 *******************************************************/


#ifndef MJOLNIR_CLOG_MJOLNIR_CLOG_HEADER_H
#define MJOLNIR_CLOG_MJOLNIR_CLOG_HEADER_H

#include <unistd.h>
#include <sys/syscall.h>

#include "Mjolnir_clog.h"

namespace Mjolnir {
  void* LogWriting(void* args) {
    Mjolnir::MjolnirCLog::GetInstance()->StartLogWriting();
    return nullptr;
  }

  pid_t gettid()
  {
#ifdef __APPLE__
    int pid = syscall(SYS_thread_selfid);
    return pid;
#endif
#ifdef __linux__
    int pid = syscall(__NR_gettid);
    return pid;
#endif
  }
}// Mjolnir

  #define LOG_INIT(log_dir, prog_name, level, mem_len) \
  do { \
    Mjolnir::MjolnirCLog::GetInstance()->SetInitParams(log_dir, prog_name, level, mem_len); \
    pthread_t tid; \
    pthread_create(&tid, NULL, Mjolnir::LogWriting, NULL); \
    pthread_detach(tid); \
  } while (0)

  //format: [LEVEL][yy-mm-dd h:m:s.ms][tid]file_name:line_no(func_name):content
  #define LOG_TRACE(fmt, args...) \
  do { \
    if (Mjolnir::MjolnirCLog::GetInstance()->GetLevel() >= Mjolnir::TRACE) { \
      Mjolnir::MjolnirCLog::GetInstance()->TryAppend("[TRACE]", "[%u]%s:%d(%s): " fmt "\n", \
      gettid(), __FILE__, __LINE__, __FUNCTION__, ##args); \
    } \
  } while (0)

  #define LOG_DEBUG(fmt, args...) \
  do { \
    if (Mjolnir::MjolnirCLog::GetInstance()->GetLevel() >= Mjolnir::DEBUG) { \
      Mjolnir::MjolnirCLog::GetInstance()->TryAppend("[DEBUG]", "[%u]%s:%d(%s): " fmt "\n", \
      gettid(), __FILE__, __LINE__, __FUNCTION__, ##args); \
    } \
  } while (0)

  #define LOG_INFO(fmt, args...) \
  do { \
    if (Mjolnir::MjolnirCLog::GetInstance()->GetLevel() >= Mjolnir::INFO) { \
    Mjolnir::MjolnirCLog::GetInstance()->TryAppend("[INFO]", "[%u]%s:%d(%s): " fmt "\n", \
    gettid(), __FILE__, __LINE__, __FUNCTION__, ##args); \
    } \
  } while (0)

  #define LOG_NORMAL(fmt, args...) \
  do { \
    if (Mjolnir::MjolnirCLog::GetInstance()->GetLevel() >= Mjolnir::INFO) { \
      Mjolnir::MjolnirCLog::GetInstance()->TryAppend("[INFO]", "[%u]%s:%d(%s): " fmt "\n", \
      gettid(), __FILE__, __LINE__, __FUNCTION__, ##args); \
    } \
  } while (0)

  #define LOG_WARN(fmt, args...) \
  do { \
    if (Mjolnir::MjolnirCLog::GetInstance()->GetLevel() >= WARN) { \
      Mjolnir::MjolnirCLog::GetInstance()->TryAppend("[WARN]", "[%u]%s:%d(%s): " fmt "\n", \
      gettid(), __FILE__, __LINE__, __FUNCTION__, ##args); \
    } \
  } while (0)

  #define LOG_ERROR(fmt, args...) \
  do { \
    if (Mjolnir::MjolnirCLog::GetInstance()->GetLevel() >= Mjolnir::ERROR) { \
      Mjolnir::MjolnirCLog::GetInstance()->TryAppend("[ERROR]", "[%u]%s:%d(%s): " fmt "\n", \
      Mjolnir::gettid(), __FILE__, __LINE__, __FUNCTION__, ##args); \
    } \
  } while (0)

  #define LOG_FATAL(fmt, args...) \
  do { \
    Mjolnir::MjolnirCLog::GetInstance()->TryAppend("[FATAL]", "[%u]%s:%d(%s): " fmt "\n", \
    gettid(), __FILE__, __LINE__, __FUNCTION__, ##args); \
  } while (0)

  #define TRACE(fmt, args...) \
  do { \
    if (Mjolnir::MjolnirCLog::GetInstance()->GetLevel() >= Mjolnir::TRACE) { \
      Mjolnir::MjolnirCLog::GetInstance()->TryAppend("[TRACE]", "[%u]%s:%d(%s): " fmt "\n", \
      gettid(), __FILE__, __LINE__, __FUNCTION__, ##args); \
      } \
  } while (0)

  #define DEBUG(fmt, args...) \
  do { \
    if (Mjolnir::MjolnirCLog::GetInstance()->GetLevel() >= Mjolnir::DEBUG) { \
      Mjolnir::MjolnirCLog::GetInstance()->TryAppend("[DEBUG]", "[%u]%s:%d(%s): " fmt "\n", \
      gettid(), __FILE__, __LINE__, __FUNCTION__, ##args); \
    } \
  } while (0)

  #define INFO(fmt, args...) \
  do { \
    if (Mjolnir::MjolnirCLog::GetInstance()->GetLevel() >= Mjolnir::INFO) { \
      Mjolnir::MjolnirCLog::GetInstance()->TryAppend("[INFO]", "[%u]%s:%d(%s): " fmt "\n", \
      gettid(), __FILE__, __LINE__, __FUNCTION__, ##args); \
    } \
  } while (0)

  #define NORMAL(fmt, args...) \
  do { \
    if (Mjolnir::MjolnirCLog::GetInstance()->GetLevel() >= Mjolnir::INFO) { \
      Mjolnir::MjolnirCLog::GetInstance()->TryAppend("[INFO]", "[%u]%s:%d(%s): " fmt "\n", \
      gettid(), __FILE__, __LINE__, __FUNCTION__, ##args); \
    } \
  } while (0)

  #define WARN(fmt, args...) \
  do { \
    if (Mjolnir::MjolnirCLog::GetInstance()->GetLevel() >= Mjolnir::WARN) { \
      Mjolnir::MjolnirCLog::GetInstance()->TryAppend("[WARN]", "[%u]%s:%d(%s): " fmt "\n", \
      gettid(), __FILE__, __LINE__, __FUNCTION__, ##args); \
    } \
  } while (0)

  #define ERROR(fmt, args...) \
  do { \
    if (Mjolnir::MjolnirCLog::GetInstance()->GetLevel() >= Mjolnir::ERROR) { \
      Mjolnir::MjolnirCLog::GetInstance()->TryAppend("[ERROR]", "[%u]%s:%d(%s): " fmt "\n", \
      gettid(), __FILE__, __LINE__, __FUNCTION__, ##args); \
    } \
  } while (0)

  #define FATAL(fmt, args...) \
  do { \
    Mjolnir::MjolnirCLog::GetInstance()->TryAppend("[FATAL]", "[%u]%s:%d(%s): " fmt "\n", \
    gettid(), __FILE__, __LINE__, __FUNCTION__, ##args); \
  } while (0)



#endif //MJOLNIR_CLOG_MJOLNIR_CLOG_HEADER_H

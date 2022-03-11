/*******************************************************
 * @author      : dog head
 * @date        : 2022-03-11 16:50
 * @mail        : qw225967@github.com
 * @file        : Mjolnir_clog.cpp
 * @idea        : vim
 * @description : TODO
 *******************************************************/

#include "Mjolnir_clog.h"


#define MEM_USE_LIMIT (3u * 1024 * 1024 * 1024)//3GB
#define LOG_USE_LIMIT (1u * 1024 * 1024 * 1024)//1GB
#define LOG_LEN_LIMIT (4 * 1024)//4K
#define RELOG_THRESOLD 5
#define BUFF_WAIT_TIME 1

namespace Mjolnir {
  // static init
  pthread_mutex_t MjolnirCLog::mutex_ = PTHREAD_MUTEX_INITIALIZER;
  pthread_once_t MjolnirCLog::once_ = PTHREAD_ONCE_INIT;
  MjolnirCLog* MjolnirCLog::single_instance_ = nullptr;

  void MjolnirCLog::SetInitParams(std::string path, std::string name, _MJOLNIR_LOG_ENUM level) {
    pthread_mutex_lock(&mutex_);


  }


} // Mjolnir
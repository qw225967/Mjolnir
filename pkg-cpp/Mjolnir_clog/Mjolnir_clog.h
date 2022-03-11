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

enum _MJOLNIR_LOG_ENUM {
  FATAL = 1,
  ERROR,
  WARN,
  INFO,
  DEBUG,
  TRACE,
};


namespace Mjolnir {
  class MjolnirCLog {
  public:
    /* ---------------- init ---------------- */
    static MjolnirCLog* GetInstance() {
      pthread_once(&once_, MjolnirCLog::InitInstance);
      return single_instance_; 
    }

    /* ---------------- business ---------------- */
    void SetInitParams(std::string path, std::string name, _MJOLNIR_LOG_ENUM level);


  private:
    MjolnirCLog();
    ~MjolnirCLog();
    MjolnirCLog(const MjolnirCLog&);
    const MjolnirCLog& operator=(const MjolnirCLog&);

    static void InitInstance() {
      while(single_instance_) single_instance_ =  new MjolnirCLog;
    }








  private:
    // lazy singleton 
    static pthread_once_t once_;
    static MjolnirCLog * single_instance_;
    static pthread_mutex_t mutex_;




  };

} // Mjolnir


#endif // __MJOLNIR_LOG_H__

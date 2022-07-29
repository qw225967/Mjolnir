/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/3/14 3:07 下午
 * @mail        : qw225967@github.com
 * @project     : Mjolnir_clog
 * @file        : UTC_Time.h
 * @description : TODO
 *******************************************************/


#ifndef MJOLNIR_CLOG_UTC_TIME_H
#define MJOLNIR_CLOG_UTC_TIME_H

#include <time.h>
#include <sys/time.h>

namespace mjolnir {
  struct _UTC_TIMER {
    _UTC_TIMER() {
      struct timeval tv;
      gettimeofday(&tv, NULL);
      //set _sys_acc_sec, _sys_acc_min
      sys_acc_sec_ = tv.tv_sec;
      sys_acc_min_ = sys_acc_sec_ / 60;
      //use _sys_acc_sec calc year, month, day, hour, min, sec
      struct tm cur_tm;
      localtime_r((time_t * ) & sys_acc_sec_, &cur_tm);
      year = cur_tm.tm_year + 1900;
      month = cur_tm.tm_mon + 1;
      day = cur_tm.tm_mday;
      hour = cur_tm.tm_hour;
      min = cur_tm.tm_min;
      sec = cur_tm.tm_sec;
      ResetUTCFmt();
    }

    uint64_t GetCurrentTime(int *p_msec = NULL) {
      struct timeval tv;
      //get current ts
      gettimeofday(&tv, NULL);
      if (p_msec)
        *p_msec = tv.tv_usec / 1000;
      //if not in same seconds
      if ((uint32_t) tv.tv_sec != sys_acc_sec_) {
        sec = tv.tv_sec % 60;
        sys_acc_sec_ = tv.tv_sec;
        //or if not in same minutes
        if (sys_acc_sec_ / 60 != sys_acc_min_) {
          //use _sys_acc_sec update year, month, day, hour, min, sec
          sys_acc_min_ = sys_acc_sec_ / 60;
          struct tm cur_tm;
          localtime_r((time_t * ) & sys_acc_sec_, &cur_tm);
          year = cur_tm.tm_year + 1900;
          month = cur_tm.tm_mon + 1;
          day = cur_tm.tm_mday;
          hour = cur_tm.tm_hour;
          min = cur_tm.tm_min;
          //reformat utc format
          ResetUTCFmt();
        } else {
          //reformat utc format only sec
          ResetUTCFmtSec();
        }
      }
      return tv.tv_sec;
    }

    int year, month, day, hour, min, sec;
    char utc_fmt[20];

  private:
    void ResetUTCFmt() {
      snprintf(utc_fmt, 20, "%d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, min, sec);
    }

    void ResetUTCFmtSec() {
      snprintf(utc_fmt + 17, 3, "%02d", sec);
    }

    uint64_t sys_acc_min_;
    uint64_t sys_acc_sec_;
  };
} // mjolnir

#endif //MJOLNIR_CLOG_UTC_TIME_H

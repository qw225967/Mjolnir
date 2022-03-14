/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/3/14 10:44 上午
 * @mail        : qw225967@github.com
 * @project     : Mjolnir_clog
 * @file        : Buffer.h
 * @description : TODO
 *******************************************************/


#ifndef MJOLNIR_CLOG_BUFFER_H
#define MJOLNIR_CLOG_BUFFER_H

#ifdef __APPLE__
#include <cstdio>
#include <cstdint>
#endif

#ifdef __linux__
#include <stdio.h>
#include <stdint.h>
#endif


#include <pthread.h>

namespace Mjolnir {
  class Buffer {
  public:
    enum _BUFFER_STATUS {
      FREE,
      FULL
    };

  public:
    Buffer(uint32_t capacity);
    ~Buffer();

    uint32_t GetRemainSpace() const { return capacity_ - used_space_; }
    _BUFFER_STATUS GetBufferStatus() { return status_; }
    bool IsEmpty() const { return used_space_ == 0; }

    void Append(const char *log_line, uint32_t len);
    void Clear();
    void Write2Disk(FILE *fp);
    void SetBufferStatus(_BUFFER_STATUS status) { status_ = status; }

  private:
    Buffer(const Buffer &);
    Buffer &operator=(const Buffer &);

  public:
    Buffer* prev_;
    Buffer* next_;

  private:
    _BUFFER_STATUS status_;
    uint32_t capacity_;
    uint32_t used_space_;
    char *data_;
  };
} // Mjolnir

#endif //MJOLNIR_CLOG_BUFFER_H

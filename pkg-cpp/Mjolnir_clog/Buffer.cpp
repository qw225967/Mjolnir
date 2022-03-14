/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/3/14 10:52 上午
 * @mail        : qw225967@github.com
 * @project     : Mjolnir_clog
 * @file        : Buffer.cpp
 * @description : TODO
 *******************************************************/

#include <iostream>

#include "Buffer.h"

namespace Mjolnir {
  /* ---------------- Buffer ---------------- */
  Buffer::Buffer(uint32_t capacity)
  : status_(FREE)
  , capacity_(capacity)
  , used_space_(0) {

    data_ = new char[capacity];
    if (!data_) {
      std::cout << "[Buffer Init] Init Buffer error!" << std::endl;
      exit(1);
    }

  }

  Buffer::~Buffer() {
    if (data_ != nullptr) {
      delete[] data_;
      data_ = nullptr;
    }
  }


  void Buffer::Append(const char *log_line, uint32_t len) {
    if (GetRemainSpace() < len)
      return;
    memcpy(data_ + used_space_, log_line, len);
    used_space_ += len;
  }

  void Buffer::Clear() {
    used_space_ = 0;
    status_ = FREE;
  }

  void Buffer::Write2Disk(FILE *fp) {
    uint32_t wt_len = fwrite(data_, 1, used_space_, fp);
    if (wt_len != used_space_) {
      std::cout<< stderr << "write log to disk error, wt_len %u" << wt_len << std::endl;
    }
  }
} // Mjolnir
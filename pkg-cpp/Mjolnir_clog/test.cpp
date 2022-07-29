/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/3/14 4:31 下午
 * @mail        : qw225967@github.com
 * @project     : Mjolnir_clog
 * @file        : test.cpp
 * @description : TODO
 *******************************************************/

#include <iostream>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

#include "Mjolnir_clog_header.h"

int64_t get_current_millis(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (int64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main(int argc, char** argv)
{
  LOG_INIT("./logs", "test", mjolnir::ERROR, 0);
  uint64_t start_ts = get_current_millis();
  for (int i = 0;i < 8000; ++i)
  {
    LOG_ERROR("my number is number my number is my number is my number is my number is my number is my number is %d", i);
  }
  uint64_t end_ts = get_current_millis();
  std::cout << "time use:" <<  end_ts - start_ts <<  std::endl;
  sleep(3);
}

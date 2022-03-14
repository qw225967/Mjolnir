/*******************************************************
 * @author      : dog head
 * @date        : 2022-03-11 16:50
 * @mail        : qw225967@github.com
 * @file        : Mjolnir_clog.cpp
 * @idea        : vim
 * @description : TODO
 *******************************************************/

#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#ifdef __APPLE__
#include <cerrno>
#include <ctime>
#include <cassert>
#endif

#ifdef __linux__
#include <errno.h>
#include <time.h>
#include <assert.h>
#endif

#include "Mjolnir_clog.h"

#define MEM_USE_LIMIT (3u * 1024 * 1024 * 1024)//3GB
#define LOG_USE_LIMIT (1u * 1024 * 1024 * 1024)//1GB
#define LOG_LEN_LIMIT (4 * 1024)//4K
#define RELOG_THRESOLD 5
#define BUFF_WAIT_TIME 1
#define DEFAULT_LOG_DIR "../logs"

namespace Mjolnir {
  // static init
  pthread_mutex_t MjolnirCLog::mutex_ = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t MjolnirCLog::cond_ = PTHREAD_COND_INITIALIZER;
  pthread_once_t MjolnirCLog::once_ = PTHREAD_ONCE_INIT;
  MjolnirCLog* MjolnirCLog::single_instance_ = nullptr;

  MjolnirCLog::MjolnirCLog()
  : log_path_(DEFAULT_LOG_DIR)
  , name_("Mjolnir_log")
  , level_(FATAL)
  , file_fp_(nullptr)
  , log_count_(0)
  , buffer_capacity_(30*1024*1024/*30MB*/)
  , node_count_(3) {
    //create double linked list
    Buffer* head = new Buffer(buffer_capacity_);
    if (!head) {
      std::cout << stderr << "no space to allocate cell_buffer" << std::endl;
      exit(1);
    }
    Buffer* current;
    Buffer* prev = head;

    // 初始化3个buffer
    for (int i = 1;i < node_count_; ++i) {
      current = new Buffer(buffer_capacity_);
      if (!current) {
        std::cout << stderr << "no space to allocate cell_buffer" << std::endl;
        exit(1);
      }
      current->prev_ = prev;
      prev->next_ = current;
      prev = current;
    }
    prev->next_ = head;
    head->prev_ = prev;

    current_node_ = head;
    writing_node_ = head;

    pid_ = getpid();
  }

  MjolnirCLog::~MjolnirCLog() {
    if (file_fp_ != nullptr) {
      fclose(file_fp_);
      file_fp_ = nullptr;
    }
  }


  void MjolnirCLog::SetInitParams(std::string path, std::string name, _MJOLNIR_LOG_ENUM level, uint32_t buffer_capacity) {
    pthread_mutex_lock(&mutex_);

    if (buffer_capacity < 90 * 1024 * 1024) {
      buffer_capacity = 90 * 1024 * 1024;
    } else if (buffer_capacity > 1024 * 1024 * 1024) {
      buffer_capacity = 1024 * 1024 * 1024;
    }
    buffer_capacity_ = buffer_capacity;

    if (path != "")
      log_path_ = path;
    if (name != "")
      name_ = name;

    level_ = level;

    mkdir(log_path_.c_str(), 0777);

    //查看是否存在此目录、目录下是否允许创建文件
    if (access(log_path_.c_str(), F_OK | W_OK) == -1) {
      std::cout << "[Log Init] log_path_ :" << log_path_ << "error!(using default log path)" << std::endl;
    }
    if (level > TRACE)
      level = TRACE;
    if (level < FATAL)
      level = FATAL;
    level_ = level;

    pthread_mutex_unlock(&mutex_);

    std::string logo = this->GetLogoString();
    current_node_->Append(logo.c_str(), logo.size());
  }

  void MjolnirCLog::Write2Disk() {
    // 如果Buffer为空等待1s
    pthread_mutex_lock(&mutex_);
    this->WritingBufferFreeWait();

    if(writing_node_->IsEmpty()) {
      std::cout << "[BufferList Working] writing_node_ is empty" << std::endl;
      pthread_mutex_unlock(&mutex_);
      return;
    }

    if (writing_node_->GetBufferStatus() == Buffer::FREE)
    {
      assert(current_node_ == writing_node_);//to test
      current_node_->SetBufferStatus(Buffer::FULL);
      current_node_ = current_node_->next_;
    }
    pthread_mutex_unlock(&mutex_);

    if (!this->FileProcessor(utc_timer_.year, utc_timer_.month, utc_timer_.day))
      return;

    //write
    writing_node_->Write2Disk(file_fp_);
    fflush(file_fp_);

    pthread_mutex_lock(&mutex_);
    writing_node_->Clear();
    writing_node_ = writing_node_->next_;
    pthread_mutex_unlock(&mutex_);
  }

  void MjolnirCLog::WritingBufferFreeWait() {
    // 等待1s 或者 等待append已完成
    if (writing_node_->GetBufferStatus() == Buffer::FREE) {
      struct timespec tsp;
      struct timeval now;
      gettimeofday(&now, NULL);
      tsp.tv_sec = now.tv_sec;
      tsp.tv_nsec = now.tv_usec * 1000;//nanoseconds
      tsp.tv_sec += BUFF_WAIT_TIME;//wait for 1 seconds
      pthread_cond_timedwait(&cond_, &mutex_, &tsp);
    }
  }

  bool MjolnirCLog::FileProcessor(int year, int month, int day) {
    if (file_fp_ == nullptr) {                       // step 1. 初始化
      this->FileGenerator(year, month, day);
    } else if (day_ != day) {                        // step 2. 日期翻转
      // 已打开则关闭重新开启新的日志文件
      fclose(file_fp_);
      file_fp_ = nullptr;
      log_count_ = 0; // 重置计数

      this->FileGenerator(year, month, day);
    } else if (ftell(file_fp_) > LOG_USE_LIMIT) {    // step 3. 大小翻转
      // 已打开则关闭重新开启新的日志文件
      fclose(file_fp_);
      file_fp_ = nullptr;

      this->FileRenameAndGenerator();
    }
    return file_fp_ != nullptr;
  }

  void MjolnirCLog::FileGenerator(int year, int month, int day) {
    year_ = year, month_ = month, day_ = day;
    char log_path[1024] = {};
    sprintf(log_path, "%s/%s.%d%02d%02d.%u.log", log_path_.c_str(), name_.c_str(), year_, month_, day_, pid_);
    file_fp_ = fopen(log_path, "w");
    if (file_fp_) ++log_count_;
  }

  void MjolnirCLog::FileRenameAndGenerator() {
    char old_path[1024] = {};
    char new_path[1024] = {};
    //mv xxx.log.[i] xxx.log.[i + 1]
    for (int i = log_count_ - 1;i > 0; --i)
    {
      sprintf(old_path, "%s/%s.%d%02d%02d.%u.log.%d", log_path_.c_str(), name_.c_str(), year_, month_, day_, pid_, i);
      sprintf(new_path, "%s/%s.%d%02d%02d.%u.log.%d", log_path_.c_str(), name_.c_str(), year_, month_, day_, pid_, i + 1);
      rename(old_path, new_path);
    }
    //mv xxx.log xxx.log.1
    sprintf(old_path, "%s/%s.%d%02d%02d.%u.log", log_path_.c_str(), name_.c_str(), year_, month_, day_, pid_);
    sprintf(new_path, "%s/%s.%d%02d%02d.%u.log.1", log_path_.c_str(), name_.c_str(), year_, month_, day_, pid_);
    rename(old_path, new_path);
    file_fp_ = fopen(old_path, "w");
    if (file_fp_)
      log_count_ += 1;
  }

  void MjolnirCLog::TryAppend(const char* lvl, const char* format, ...) {
    int ms;
    uint64_t curr_sec = utc_timer_.GetCurrentTime(&ms);
    if (last_lts_ && curr_sec - last_lts_ < RELOG_THRESOLD)
      return ;

    char log_line[LOG_LEN_LIMIT];
    //int prev_len = snprintf(log_line, LOG_LEN_LIMIT, "%s[%d-%02d-%02d %02d:%02d:%02d.%03d]", lvl, _tm.year, _tm.mon, _tm.day, _tm.hour, _tm.min, _tm.sec, ms);
    int prev_len = snprintf(log_line, LOG_LEN_LIMIT, "%s[%s.%03d]", lvl, utc_timer_.utc_fmt, ms);

    va_list arg_ptr;
    va_start(arg_ptr, format);

    //TO OPTIMIZE IN THE FUTURE: performance too low here!
    int main_len = vsnprintf(log_line + prev_len, LOG_LEN_LIMIT - prev_len, format, arg_ptr);

    va_end(arg_ptr);

    uint32_t len = prev_len + main_len;

    last_lts_ = 0;
    bool thread_call_flag = false; // 写磁盘线程可能阻塞在FREE，append完成后唤醒写磁盘线程

    pthread_mutex_lock(&mutex_);
    if (current_node_->GetBufferStatus() == Buffer::FREE && current_node_->GetRemainSpace() >= len) {
      current_node_->Append(log_line, len);
    } else {
      //1. 当前节点没满，但是剩余空间不足len时，无法写入
      //2. 当前节点已满
      // 因此直接设置为 FULL，并new新的节点
      if (current_node_->GetBufferStatus() == Buffer::FREE) {
        current_node_->SetBufferStatus(Buffer::FULL);//set to FULL
        Buffer* next_buf = current_node_->next_;
        // 当前节点已满直接写入
        thread_call_flag = true;

        //如果下一个buffer已满则证明可能在写磁盘，未完成写磁盘工作
        if (next_buf->GetBufferStatus() == Buffer::FULL) {
          if (buffer_capacity_ * (node_count_ + 1) > MEM_USE_LIMIT) {      // 如果无法申请则偏移
            std::cout << stderr << "no more log space can use" << std::endl;
            current_node_ = next_buf;
            last_lts_ = curr_sec; // 标记无法写入时刻的时间
          } else {                                                          // 如果还能申请新的空间则继续new
            Buffer* new_buffer = new Buffer(buffer_capacity_);
            ++node_count_;
            new_buffer->prev_ = current_node_;
            current_node_->next_ = new_buffer;
            new_buffer->next_ = next_buf;
            next_buf->prev_ = new_buffer;
            current_node_ = new_buffer;
          }
        } else {
          current_node_ = next_buf;
        }

        // 如果没发生无法写入错误则写入
        if (!last_lts_)
          current_node_->Append(log_line, len);
      } else { // 有可能因为允许写入的内存已经满，无法写入
        last_lts_ = curr_sec;
      }
    }
    pthread_mutex_unlock(&mutex_);
    // 通知写线程工作
    if (thread_call_flag) {
      pthread_cond_signal(&cond_);
    }
  }

  std::string MjolnirCLog::GetLogoString() {
    std::string logo = "++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
                       "+                                                      +\n"
                       "+                                 ;.; G                +\n"
                       "+                                ,,:iG G               +\n"
                       "+                               ,tC   , C              +\n"
                       "+                              ,fC    L  C             +\n"
                       "+                             ;fL     iL  G            +\n"
                       "+                            :fi       8   G           +\n"
                       "+                           if          Coio           +\n"
                       "+                          if                          +\n"
                       "+                        .1L                           +\n"
                       "+                       :fL                            +\n"
                       "+            t1it,     :LL                             +\n"
                       "+           LGf::C;1t .tL                              +\n"
                       "+          tG1::;;;G;:1f;                              +\n"
                       "+         GL,;;;;;iiii:8G:if                           +\n"
                       "+         t:iiiiiiiiiiii;;;:ii                         +\n"
                       "+           tt;i;iii;;;i;;iLGi                         +\n"
                       "+              ;fi;;;;;;;;GG,                          +\n"
                       "+                  ff:;:;GL                            +\n"
                       "+                     +L+                              +\n"
                       "+                            ;                         +\n"
                       "+                            @t          GG            +\n"
                       "+                            @t                        +\n"
                       "+   f@@8   0@@  @@C          @t         t@@ to    or   +\n"
                       "+   G8@@: t8@@   G:   L0L    @t ;0 L0C   18  0GGGrr    +\n"
                       "+   8C @@ @ @@   @L @@   @@  @t 1@:  @@  @@  @@        +\n"
                       "+   @L  @@  @@   @L @8   0@  @t 1@.  @@  @@  @@        +\n"
                       "+  C@@:    ,@@@  @L  @@f@@  0@@ @@0 .@@1i@@ t@@        +\n"
                       "+                @L                                    +\n"
                       "+                @L                                    +\n"
                       "+             oGGG                                     +\n"
                       "+                                                      +\n"
                       "++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    return logo;
  }

} // Mjolnir
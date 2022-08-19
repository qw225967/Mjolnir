/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/8/16 11:15 上午
 * @mail        : qw225967@github.com
 * @project     : Mjolnir_PrioQueue
 * @file        : Mjolnir_PriorQueue.h
 * @description : TODO
 *******************************************************/


#ifndef MJOLNIR_PRIOQUEUE_MJOLNIR_PRIORQUEUE_H
#define MJOLNIR_PRIOQUEUE_MJOLNIR_PRIORQUEUE_H

#include <string>
#include <vector>

namespace mjolnir {
  class MjolnirPriorityQueue {
  public:
    // 父元素结构体
    struct Element {
      Element(bool init = false, int prior = 0, uint64_t now = 0, std::string str = "")
      :     isInit(init),
            priority(prior),
            time_stamp(now),
            show_string(std::move(str)) {}
      bool operator<(const Element& e) const {
        if (priority < e.priority)
          return true;
        else if (priority == e.priority){
          if (time_stamp < e.time_stamp) {
            return true;
          }
          return false;
        } else {
          return false;
        }
      }
      bool operator<=(const Element& e) const {
        return priority <= e.priority /*|| time_stamp <= e.time_stamp*/;
      }
      bool operator>=(const Element& e) const {
        return priority >= e.priority /*&& time_stamp >= e.time_stamp*/;
      }

      bool isInit;
      int priority;
      uint64_t time_stamp;
      std::string show_string;
      int index { 0u };

      std::shared_ptr<Element> pre;
      std::shared_ptr<Element> next;
    };
    typedef std::shared_ptr<Element> ElementPtr;

  public:
    MjolnirPriorityQueue();
    ~MjolnirPriorityQueue();

  public:
    void Push(Element element);
    Element Pop();
    void DelOldElement();

    bool IsEmpty() { return element_queue_.empty(); }
    size_t GetQueueSize() { return element_queue_.size(); }

  private:
    ElementPtr QueuePushHeap(Element element);
    ElementPtr QueuePopHeap();
    void QueueDelNode(Element element);

    void PushBackToList(ElementPtr elementPtr);
    void DelListNode(ElementPtr elementPtr);
    Element DelListHead();

  private:
    // 优先级队列索引，用于删除最旧元素
    ElementPtr oldest_element_ptr_{ nullptr };
    ElementPtr last_element_ptr_{ nullptr };

    // 优先级队列存储容器，使用heap计算堆
    std::vector<ElementPtr> element_queue_;
  };
} // mjolnir

#endif//MJOLNIR_PRIOQUEUE_MJOLNIR_PRIORQUEUE_H

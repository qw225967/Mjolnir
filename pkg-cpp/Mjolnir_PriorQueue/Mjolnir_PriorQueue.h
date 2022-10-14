/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/8/16 11:15 上午
 * @mail        : qw225967@github.com
 * @project     : Mjolnir_PrioQueue
 * @file        : Mjolnir_PriorQueue.h
 * @description : MjolnirPriorityQueue 类型是个通用的优先级队列
 *******************************************************/


#ifndef MJOLNIR_PRIOQUEUE_MJOLNIR_PRIORQUEUE_H
#define MJOLNIR_PRIOQUEUE_MJOLNIR_PRIORQUEUE_H

#include <queue>
#include <string>
#include <vector>

namespace mjolnir {
  constexpr size_t MaxMjolnirPriorityQueueSize = 100;

  /*
   *  MjolnirPriorityQueue 类型是个通用的优先级队列
   *  1.优先级比较可通过外部类型重载 < 操作符 外部控制；
   *  2.提供先进先出的淘汰能力。
   */

  template<class Type>
  class MjolnirPriorityQueue {
  public:
    // 父元素结构体
    struct Element {
      Type t;

      int index;
      std::shared_ptr<Element> pre;
      std::shared_ptr<Element> next;
    };
    typedef std::shared_ptr<Type> TypePtr;
    typedef std::shared_ptr<Element> ElementPtr;

  private:

    // 优先级队列索引，用于删除最旧元素
    ElementPtr oldest_element_ptr_{nullptr};
    ElementPtr last_element_ptr_{nullptr};

    // 优先级队列存储容器，使用heap计算堆
    std::vector<ElementPtr> element_queue_;

  public:
    MjolnirPriorityQueue() {}

    ~MjolnirPriorityQueue() {}

    MjolnirPriorityQueue &operator=(const MjolnirPriorityQueue &q) {
      return *this;
    }

    MjolnirPriorityQueue(MjolnirPriorityQueue &&q) {}

    explicit MjolnirPriorityQueue(const MjolnirPriorityQueue &q) {}



  public:
    void Push(Type element) {
      if (element_queue_.size() == MaxMjolnirPriorityQueueSize) {
        DelOldElement();
      }
      auto res = QueuePushHeap(element);
      if (res.get())
        PushBackToList(res);
    }

    Type Pop() {
      Type res;
      auto tmp = QueuePopHeap();
      if (tmp.get()) {
        res = tmp->t;
        DelListNode(tmp);
      }

      return res;
    }

    void DelOldElement() {
      auto res = DelListHead();
      // 清除队列超时元素
      QueueDelNode(res);
    }

    bool IsEmpty() { return element_queue_.empty(); }
    size_t GetQueueSize() { return element_queue_.size(); }

  private:
    // 数组操作
    ElementPtr QueuePushHeap(Type t) {
      ElementPtr e = std::make_shared<Element>();
      e->t = t;
      e->index = element_queue_.size();

      element_queue_.push_back(e);

      SiftUp();

      return e;
    }

    ElementPtr QueuePopHeap() {
      ElementPtr res;
      if (element_queue_.size() > 1) {
        res = element_queue_.front();

        std::swap(*element_queue_.begin(), *--element_queue_.end());
        SiftDown(element_queue_.begin(), element_queue_.end(), element_queue_.size() - 1, element_queue_.begin());
      }
      element_queue_.pop_back();

      return res;
    }

    void QueueDelNode(Element element) {
      auto ite = element_queue_.begin() + element.index;
      auto back = --element_queue_.end();

      std::swap(*ite, *back);
      (*ite)->index = ite - element_queue_.begin();
      element_queue_.pop_back();

      if (element_queue_.size() > 0) {
        SiftDown(element_queue_.begin(), element_queue_.end(), element_queue_.size(), ite);
      }
    }

    // 链表操作
    void PushBackToList(ElementPtr elementPtr) {
      if (!oldest_element_ptr_.get() && !last_element_ptr_.get()) {
        oldest_element_ptr_ = elementPtr;
        last_element_ptr_ = oldest_element_ptr_;
        last_element_ptr_->next = nullptr;
      } else {
        last_element_ptr_->next = elementPtr;
        elementPtr->pre = last_element_ptr_;
        last_element_ptr_ = last_element_ptr_->next;
        last_element_ptr_->next = nullptr;
      }
    }
    void DelListNode(ElementPtr elementPtr) {
      if (elementPtr.get()) {
        // 删除的是中间元素
        if (elementPtr->pre.get() && elementPtr->next.get()) {
          // 向前链接
          elementPtr->next->pre = elementPtr->pre;
          // 向前后
          elementPtr->pre->next = elementPtr->next;
        } else if (elementPtr->pre.get() && !elementPtr->next.get()) {
          // 证明是尾删除，切换尾
          last_element_ptr_ = elementPtr->pre;
          elementPtr->pre->next = nullptr;
        } else if (!elementPtr->pre.get() && elementPtr->next.get()) {
          // 证明是头删除，切换头
          oldest_element_ptr_ = elementPtr->next;
          elementPtr->next->pre = nullptr;
        }

        elementPtr.reset();
      }
    }
    Element DelListHead() {
      Element res;
      // 没有数据直接返回
      if (!oldest_element_ptr_.get()) return res;
      // 只有一个数据
      if (!oldest_element_ptr_->next.get()) {
        res = *(oldest_element_ptr_.get());
        return res;
      }
      res = *(oldest_element_ptr_.get());
      oldest_element_ptr_ = oldest_element_ptr_->next;

      return res;
    }


    // 堆操作，参考 stl
    void SiftUp() {
      auto len = element_queue_.size();
      auto first = element_queue_.begin();
      auto last = element_queue_.end();

      if (len > 1) {
        len = (len - 2) / 2;
        auto ite = first + len;
        if ((**--last).t < (**ite).t) {
          auto t(std::move(*last));
          do {
            *last = std::move(*ite);
            (*last)->index = last - first;
            last = ite;
            if (len == 0)
              break;
            len = (len - 1) / 2;
            ite = first + len;
          } while ((*t).t < (**ite).t);
          *last = std::move(t);
          (*last)->index = last - first;
        }
      }
    }
    void SiftDown(typename std::vector<ElementPtr>::iterator first,
                  typename std::vector<ElementPtr>::iterator /*__last*/,
                  int len,
                  typename std::vector<ElementPtr>::iterator start) {
      // left-child of __start is at 2 * __start + 1
      // right-child of __start is at 2 * __start + 2
      auto child = start - first;

      if (len < 2 || (len - 2) / 2 < child)
        return;

      child = 2 * child + 1;
      auto child_i = first + child;

      if ((child + 1) < len && (**(child_i + 1)).t < (**child_i).t) {
        // right-child exists and is greater than left-child
        ++child_i;
        ++child;
      }

      // check if we are in heap-order
      if ((**start).t < (**child_i).t)
        // we are, __start is larger than it's largest child
        return;

      auto top(std::move(*start));
      do {
        // we are not in heap-order, swap the parent with it's largest child
        *start = std::move(*child_i);
        (*start)->index = start - first;
        start = child_i;


        if ((len - 2) / 2 < child)
          break;

        // recompute the child based off of the updated parent
        child = 2 * child + 1;
        child_i = first + child;

        if ((child + 1) < len && (**(child_i + 1)).t < (**child_i).t) {
          // right-child exists and is greater than left-child
          ++child_i;
          ++child;
        }

        // check if we are in heap-order
      } while (!((*top).t < (**child_i).t));
      *start = std::move(top);
      (*start)->index = start - first;
    }
    void MakeHeap() {
      auto n = element_queue_.end() - element_queue_.begin();
      auto first = element_queue_.begin();
      auto last = element_queue_.end();

      if (n > 1) {
        // start from the first parent, there is no need to consider children
        for (auto start = (n - 2) / 2; start >= 0; --start) {
          SiftDown(first, last, n, first + start);
        }
      }
    }
  };
}// namespace mjolnir

#endif//MJOLNIR_PRIOQUEUE_MJOLNIR_PRIORQUEUE_H

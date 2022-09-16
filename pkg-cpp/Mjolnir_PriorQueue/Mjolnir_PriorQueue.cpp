/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/8/16 11:15 上午
 * @mail        : qw225967@github.com
 * @project     : Mjolnir_PrioQueue
 * @file        : Mjolnir_PriorQueue.cpp
 * @description : TODO
 *******************************************************/

#include "Mjolnir_PriorQueue.h"
#include "Mjolnir_Queue_opt.h"
#include <iostream>

namespace mjolnir {
  constexpr size_t MaxMjolnirPriorityQueueSize = 100;

  MjolnirPriorityQueue::MjolnirPriorityQueue() {}
  MjolnirPriorityQueue::~MjolnirPriorityQueue() {}

  void MjolnirPriorityQueue::PushBackToList(ElementPtr elementPtr) {
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

  void MjolnirPriorityQueue::DelListNode(ElementPtr elementPtr) {
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

  MjolnirPriorityQueue::Element MjolnirPriorityQueue::DelListHead() {
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

//  MjolnirPriorityQueue::ElementPtr MjolnirPriorityQueue::QueuePushHeap(Element element) {
//    ElementPtr e = std::make_shared<Element>(element);
//
//    element_queue_.push_back(e);
//
//    int p, i = element_queue_.size() - 1;
//    while (i > 0) {
//      // 父亲节点的编号
//      p = (i - 1) / 2;
//
//      if ((*element_queue_[p]) < *e) break;
//      //把父亲的节点放下来
//      std::swap((element_queue_[p]), (element_queue_[i]));
//      element_queue_[i]->index = i;
//      element_queue_[p]->index = p;
//
//      //当前节点更新
//      i = p;
//    }
//    element_queue_[i] = e;
//    element_queue_[i]->index = i;
//
//    // 保证儿子有序
//    int a = i * 2 + 1, b = i * 2 + 2;
//    if (b < element_queue_.size() && *element_queue_[b] < *element_queue_[a]) {
//      std::swap(element_queue_[b], element_queue_[a]);
//      element_queue_[b]->index = b;
//      element_queue_[a]->index = a;
//    }
//
//    return e;
//  }
MjolnirPriorityQueue::ElementPtr MjolnirPriorityQueue::QueuePushHeap(Element element) {
    ElementPtr e = std::make_shared<Element>(element);

    element_queue_.push_back(e);
    int i, j, gap, n = element_queue_.size();

    for (gap = n / 2; gap > 0; gap /= 2)
      for (i = gap; i < n; i++)
        for (j = i - gap; j >= 0 && *element_queue_[j + gap] < *element_queue_[j]; j -= gap)
          std::swap(element_queue_[j], element_queue_[j + gap]);

    return e;
  }

  MjolnirPriorityQueue::ElementPtr MjolnirPriorityQueue::QueuePopHeap() {
    ElementPtr res;

    res = element_queue_[0];//根，最小值
    element_queue_.erase(element_queue_.begin());

    return res;
  }

  void MjolnirPriorityQueue::QueueDelNode(Element element) {
    element_queue_.erase(element_queue_.begin() + element.index);
  }

  //  MjolnirPriorityQueue::ElementPtr MjolnirPriorityQueue::QueuePopHeap() {
  //    ElementPtr res;
  //
  //    // step 1: 处理空值、剩余两个值（使用i*+1性质，所以最后两个无法区分大小）
  //    if (element_queue_.empty()) { return res; }
  //    if (element_queue_.size() <= 2) {
  //      if (element_queue_.size() == 2 && *element_queue_[1] < *element_queue_[0]) {
  //        std::swap(element_queue_[0], element_queue_[1]);
  //        element_queue_[0]->index = 0;
  //        element_queue_[1]->index = 1;
  //      }
  //      res = element_queue_[0];
  //      element_queue_.erase(element_queue_.begin());
  //      return res;
  //    }
  //
  //    // step 2: 大于2个数据时可以根据i*2+1的性质进行计算
  //    ElementPtr ret = element_queue_[0]; //根，最小值
  //    int preEnd = element_queue_.size() - 1;
  //    ElementPtr e = element_queue_[preEnd];
  //    //最后一个节点， 放到根的数值
  //    std::swap(element_queue_[0], element_queue_[preEnd]);
  //    element_queue_.erase(element_queue_.end() - 1);
  //
  //    int i = 0, end = element_queue_.size();
  //    //从根向下交换
  //    while (i*2+1 < end){
  //      int a = i*2+1, b = i*2+2; //两个儿子的位置
  //      if (b < end && *element_queue_[b] < *element_queue_[a]) a = b;//保证 最小的儿子
  //
  //      if (*element_queue_[a] <= *e) {
  //        //把儿子的值提上来
  //        std::swap(element_queue_[i], element_queue_[a]);
  //        element_queue_[i]->index = i;
  //        element_queue_[a]->index = a;
  //
  //        i = a;
  //      } else {
  //        break;  //如果没有大小颠倒 退出
  //      }
  //    }
  //    element_queue_[i] = e; //最终在找到的位置 i 填入 x；
  //    element_queue_[i]->index = i;
  //
  //    i = element_queue_.size() - 1;
  //    int p;
  //    while (end > 0){
  //      // 父亲节点的编号
  //      p = (i - 1)/2;
  //
  //      if ((*element_queue_[p]) < *e) break;
  //      //把父亲的节点放下来
  //      std::swap((element_queue_[p]), (element_queue_[i]));
  //      element_queue_[i]->index = i;
  //      element_queue_[p]->index = p;
  //
  //      //当前节点更新
  //      i = p;
  //    }
  //
  //    // 剩余两个元素时，保证元素有序
  //    if (element_queue_.size() == 2 && *element_queue_[1] < *element_queue_[0]) {
  //      std::swap(element_queue_[1], element_queue_[0]);
  //      element_queue_[1]->index = 1;
  //      element_queue_[0]->index = 0;
  //    }
  //
  //    res = ret;
  //
  //    return res;
  //  }

//  void MjolnirPriorityQueue::QueueDelNode(Element element) {
//    // step 1: 处理空值、剩余两个值（使用i*2+1性质，所以最后两个无法区分大小）
//    if (element_queue_.empty()) { return; }
//    if (element_queue_.size() <= 2) {
//      element_queue_.erase(element_queue_.begin() + element.index - 1);
//      return;
//    }
//
//    // step 2: 处理大于2数量的删除方法
//    int i = element.index, preEnd = element_queue_.size() - 1;
//    if (*element_queue_[i] <= *element_queue_[preEnd]) {// 当前节点 <= 尾结点：当前节点与父交换，仍然保证最小堆性质不变
//      std::swap(element_queue_[i], element_queue_[preEnd]);
//      element_queue_.erase(element_queue_.end() - 1);
//
//      // 只需要向下调整
//      int end = element_queue_.size() - 1;
//      ElementPtr e = element_queue_[i];
//      while (i * 2 + 1 < end) {
//        int a = i * 2 + 1, b = i * 2 + 2;
//
//        if (b < end && *element_queue_[b] < *element_queue_[a]) a = b;
//
//        if (*element_queue_[a] >= *e) break;
//
//        std::swap(element_queue_[i], element_queue_[a]);
//        element_queue_[i]->index = i;
//        element_queue_[a]->index = a;
//        i = a;
//      }
//      element_queue_[i] = e;//最终在找到的位置 i 填入 x；
//      element_queue_[i]->index = i;
//    } else {// 当前节点 > 尾结点：当前节点与父交换，破坏了当前的堆性质
//      std::swap(element_queue_[i], element_queue_[preEnd]);
//      element_queue_.erase(element_queue_.end() - 1);
//
//      // 需要向上调整
//      ElementPtr e = element_queue_[i];
//      while (i > 0) {
//        int p = (i - 1) / 2;
//        if (*element_queue_[p] < *element_queue_[i]) break;
//        //把父亲的节点放下来
//        std::swap((element_queue_[p]), (element_queue_[i]));
//        element_queue_[i]->index = i;
//        element_queue_[p]->index = p;
//        //当前节点更新
//        i = p;
//      }
//      element_queue_[i] = e;
//      element_queue_[i]->index = i;
//    }
//  }

  void MjolnirPriorityQueue::Push(Element element) {
    if (element_queue_.size() == MaxMjolnirPriorityQueueSize) {
      DelOldElement();
    }
    auto res = QueuePushHeap(element);
    if (res.get())
      PushBackToList(res);
  }

  MjolnirPriorityQueue::Element MjolnirPriorityQueue::Pop() {
    Element res;
    auto tmp = QueuePopHeap();
    if (tmp.get()) {
      res = *(tmp.get());
      if (tmp->isInit)
        DelListNode(tmp);
    }

    return res;
  }

  void MjolnirPriorityQueue::DelOldElement() {
    auto res = DelListHead();
    if (res.isInit) {
      // 清除队列超时元素
      QueueDelNode(res);
    }
  }

}// namespace mjolnir
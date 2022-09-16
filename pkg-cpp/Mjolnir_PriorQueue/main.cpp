#include "Mjolnir_PriorQueue.h"
#include <iostream>

int main() {
  std::cout << "Hello, World!" << std::endl;

  mjolnir::MjolnirPriorityQueue::Element a(true, 1, 10, 687,"687");
  mjolnir::MjolnirPriorityQueue::Element c(true, 1, 11, 705,"705");
  mjolnir::MjolnirPriorityQueue::Element e(true, 1, 12, 706,"706");
  mjolnir::MjolnirPriorityQueue::Element f(true, 1, 13, 707,"707");
  mjolnir::MjolnirPriorityQueue::Element b(true, 1, 14, 708,"708");
  mjolnir::MjolnirPriorityQueue::Element d(true, 1, 15, 709,"709");
  mjolnir::MjolnirPriorityQueue::Element g(true, 1, 16, 710,"710");
  mjolnir::MjolnirPriorityQueue::Element h(true, 1, 17, 711,"711");
  mjolnir::MjolnirPriorityQueue::Element i(true, 1, 18, 712,"712");
  mjolnir::MjolnirPriorityQueue::Element j(true, 1, 19, 713,"713");
  mjolnir::MjolnirPriorityQueue::Element k(true, 1, 20, 714,"714");
  mjolnir::MjolnirPriorityQueue::Element l(true, 1, 21, 715,"715");
  mjolnir::MjolnirPriorityQueue::Element m(true, 1, 22, 716,"716");
  mjolnir::MjolnirPriorityQueue::Element n(true, 1, 23, 717,"717");
  mjolnir::MjolnirPriorityQueue::Element o(true, 1, 25, 718,"718");
  mjolnir::MjolnirPriorityQueue::Element p(true, 1, 25, 719,"719");
  mjolnir::MjolnirPriorityQueue::Element q(true, 1, 26, 720,"720");
  mjolnir::MjolnirPriorityQueue::Element r(true, 1, 27, 721,"721");
  mjolnir::MjolnirPriorityQueue::Element s(true, 1, 28, 722,"722");
  mjolnir::MjolnirPriorityQueue::Element t(true, 1, 29, 723,"723");
  mjolnir::MjolnirPriorityQueue::Element u(true, 1, 30, 724,"724");

  mjolnir::MjolnirPriorityQueue que;
  que.Push(a);
  que.Push(c);
  que.Push(e);
  que.Push(f);
  que.Push(b);
  que.Push(d);
  que.Push(g);
  que.Push(h);
  que.Push(i);
//  for (auto i=0;i<3;i++) {
//    auto tmp = que.Pop();
//    if (tmp.isInit)
//      std::cout << "priority:" << tmp.priority
//      << ", time_stamp:" << tmp.time_stamp
//      << ", show_string:" << tmp.show_string
//      << ", seq:" << tmp.sequence
//      << ", index:" << tmp.index << std::endl;
//  }

  que.Push(j);
  que.Push(k);
  que.Push(l);
  que.Push(m);
  que.Push(n);
  que.Push(o);
  que.Push(p);
  que.Push(q);
  que.Push(r);
  que.Push(s);
  que.Push(t);
  que.Push(u);
//
//  que.Push(h);
//  for (auto i=0;i<1;i++) {
//    auto tmp = que.Pop();
//    if (tmp.isInit)
//      std::cout << "priority:" << tmp.priority
//      << ", time_stamp:" << tmp.time_stamp
//      << ", show_string:" << tmp.show_string
//      << ", seq:" << tmp.sequence
//      << ", index:" << tmp.index << std::endl;
//  }
//
//  que.Push(i);
//  for (auto i=0;i<1;i++) {
//    auto tmp = que.Pop();
//    if (tmp.isInit)
//      std::cout << "priority:" << tmp.priority
//      << ", time_stamp:" << tmp.time_stamp
//      << ", show_string:" << tmp.show_string
//      << ", seq:" << tmp.sequence
//      << ", index:" << tmp.index << std::endl;
//  }
//  que.Push(j);
//  que.Push(k);
//  for (auto i=0;i<1;i++) {
//    auto tmp = que.Pop();
//    if (tmp.isInit)
//      std::cout << "priority:" << tmp.priority
//      << ", time_stamp:" << tmp.time_stamp
//      << ", show_string:" << tmp.show_string
//      << ", seq:" << tmp.sequence
//      << ", index:" << tmp.index << std::endl;
//  }
//  que.Push(l);
//  for (auto i=0;i<5;i++) {
//    auto tmp = que.Pop();
//    if (tmp.isInit)
//      std::cout << "priority:" << tmp.priority
//      << ", time_stamp:" << tmp.time_stamp
//      << ", show_string:" << tmp.show_string
//      << ", seq:" << tmp.sequence
//      << ", index:" << tmp.index << std::endl;
//  }
//  que.Push(m);
//  for (auto i=0;i<5;i++) {
//    auto tmp = que.Pop();
//    if (tmp.isInit)
//      std::cout << "priority:" << tmp.priority
//      << ", time_stamp:" << tmp.time_stamp
//      << ", show_string:" << tmp.show_string
//      << ", seq:" << tmp.sequence
//      << ", index:" << tmp.index << std::endl;
//  }
//  que.Push(n);
//  for (auto i=0;i<1;i++) {
//    auto tmp = que.Pop();
//    if (tmp.isInit)
//      std::cout << "priority:" << tmp.priority
//      << ", time_stamp:" << tmp.time_stamp
//      << ", show_string:" << tmp.show_string
//      << ", seq:" << tmp.sequence
//      << ", index:" << tmp.index << std::endl;
//  }
//  que.Push(o);
//  for (auto i=0;i<2;i++) {
//    auto tmp = que.Pop();
//    if (tmp.isInit)
//      std::cout << "priority:" << tmp.priority
//      << ", time_stamp:" << tmp.time_stamp
//      << ", show_string:" << tmp.show_string
//      << ", seq:" << tmp.sequence
//      << ", index:" << tmp.index << std::endl;
//  }
//  que.Push(p);
auto size =que.GetQueueSize()-1;
  for (auto i=0;i<size;i++) {
    auto tmp = que.Pop();
    if (tmp.isInit)
      std::cout << "priority:" << tmp.priority
      << ", time_stamp:" << tmp.time_stamp
      << ", show_string:" << tmp.show_string
      << ", seq:" << tmp.sequence
      << ", index:" << tmp.index << std::endl;
  }


  return 0;
}

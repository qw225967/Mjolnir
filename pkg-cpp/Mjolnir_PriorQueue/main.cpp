#include "Mjolnir_PriorQueue.h"
#include <iostream>

int main() {
  std::cout << "Hello, World!" << std::endl;

  mjolnir::MjolnirPriorityQueue::Element a(true, 2, 10, 3185,"3185");
  mjolnir::MjolnirPriorityQueue::Element c(true, 2, 11, 3186,"3186");
  mjolnir::MjolnirPriorityQueue::Element e(true, 2, 12, 3187,"3187");
  mjolnir::MjolnirPriorityQueue::Element f(true, 2, 13, 3188,"3188");
  mjolnir::MjolnirPriorityQueue::Element b(true, 2, 14, 3189,"3189");
  mjolnir::MjolnirPriorityQueue::Element d(true, 2, 15, 3190,"3190");
  mjolnir::MjolnirPriorityQueue::Element g(true, 2, 16, 3191,"3191");
  mjolnir::MjolnirPriorityQueue::Element h(true, 2, 17, 3192,"3192");
  mjolnir::MjolnirPriorityQueue::Element i(true, 2, 18, 3193,"3193");
  mjolnir::MjolnirPriorityQueue::Element j(true, 2, 19, 3194,"3194");
  mjolnir::MjolnirPriorityQueue::Element k(true, 2, 20, 3195,"3195");
  mjolnir::MjolnirPriorityQueue::Element l(true, 2, 21, 3196,"3196");
  mjolnir::MjolnirPriorityQueue::Element m(true, 1, 22, 2509,"2509");
  mjolnir::MjolnirPriorityQueue::Element n(true, 1, 23, 2510,"2510");
  mjolnir::MjolnirPriorityQueue::Element o(true, 1, 24, 2511,"2511");
  mjolnir::MjolnirPriorityQueue::Element p(true, 1, 25, 2512,"2512");
  mjolnir::MjolnirPriorityQueue::Element q(true, 1, 26, 2513,"2513");

  mjolnir::MjolnirPriorityQueue que;
  que.Push(a);
  que.Push(c);
  que.Push(e);
  que.Push(f);
  que.Push(b);
  que.Push(d);
  que.Push(g);
  for (auto i=0;i<3;i++) {
    auto tmp = que.Pop();
    if (tmp.isInit)
      std::cout << "priority:" << tmp.priority
      << ", time_stamp:" << tmp.time_stamp
      << ", show_string:" << tmp.show_string
      << ", seq:" << tmp.sequence
      << ", index:" << tmp.index << std::endl;
  }

  que.Push(h);
  for (auto i=0;i<1;i++) {
    auto tmp = que.Pop();
    if (tmp.isInit)
      std::cout << "priority:" << tmp.priority
      << ", time_stamp:" << tmp.time_stamp
      << ", show_string:" << tmp.show_string
      << ", seq:" << tmp.sequence
      << ", index:" << tmp.index << std::endl;
  }

  que.Push(i);
  for (auto i=0;i<1;i++) {
    auto tmp = que.Pop();
    if (tmp.isInit)
      std::cout << "priority:" << tmp.priority
      << ", time_stamp:" << tmp.time_stamp
      << ", show_string:" << tmp.show_string
      << ", seq:" << tmp.sequence
      << ", index:" << tmp.index << std::endl;
  }
  que.Push(j);
  que.Push(k);
  for (auto i=0;i<1;i++) {
    auto tmp = que.Pop();
    if (tmp.isInit)
      std::cout << "priority:" << tmp.priority
      << ", time_stamp:" << tmp.time_stamp
      << ", show_string:" << tmp.show_string
      << ", seq:" << tmp.sequence
      << ", index:" << tmp.index << std::endl;
  }
  que.Push(l);
  for (auto i=0;i<5;i++) {
    auto tmp = que.Pop();
    if (tmp.isInit)
      std::cout << "priority:" << tmp.priority
      << ", time_stamp:" << tmp.time_stamp
      << ", show_string:" << tmp.show_string
      << ", seq:" << tmp.sequence
      << ", index:" << tmp.index << std::endl;
  }
  que.Push(m);
  for (auto i=0;i<5;i++) {
    auto tmp = que.Pop();
    if (tmp.isInit)
      std::cout << "priority:" << tmp.priority
      << ", time_stamp:" << tmp.time_stamp
      << ", show_string:" << tmp.show_string
      << ", seq:" << tmp.sequence
      << ", index:" << tmp.index << std::endl;
  }
  que.Push(n);
  for (auto i=0;i<1;i++) {
    auto tmp = que.Pop();
    if (tmp.isInit)
      std::cout << "priority:" << tmp.priority
      << ", time_stamp:" << tmp.time_stamp
      << ", show_string:" << tmp.show_string
      << ", seq:" << tmp.sequence
      << ", index:" << tmp.index << std::endl;
  }
  que.Push(o);
  for (auto i=0;i<2;i++) {
    auto tmp = que.Pop();
    if (tmp.isInit)
      std::cout << "priority:" << tmp.priority
      << ", time_stamp:" << tmp.time_stamp
      << ", show_string:" << tmp.show_string
      << ", seq:" << tmp.sequence
      << ", index:" << tmp.index << std::endl;
  }
  que.Push(p);

  for (auto i=0;i<2;i++) {
    auto tmp = que.Pop();
    if (tmp.isInit)
      std::cout << "priority:" << tmp.priority
      << ", time_stamp:" << tmp.time_stamp
      << ", show_string:" << tmp.show_string
      << ", seq:" << tmp.sequence
      << ", index:" << tmp.index << std::endl;
  }
  que.Push(q);

  return 0;
}

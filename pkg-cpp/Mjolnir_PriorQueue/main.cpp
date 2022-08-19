#include "Mjolnir_PriorQueue.h"
#include <iostream>

int main() {
  std::cout << "Hello, World!" << std::endl;

  mjolnir::MjolnirPriorityQueue::Element a(true, 2, 22, "22");
  mjolnir::MjolnirPriorityQueue::Element c(true, 1, 10, "10");
  mjolnir::MjolnirPriorityQueue::Element e(true, 1, 10, "10");
  mjolnir::MjolnirPriorityQueue::Element f(true, 1, 50, "50");
  mjolnir::MjolnirPriorityQueue::Element b(true, 1, 10, "10");
  mjolnir::MjolnirPriorityQueue::Element d(true, 3, 31, "31");
  mjolnir::MjolnirPriorityQueue::Element g(true, 1, 16, "16");
  mjolnir::MjolnirPriorityQueue::Element h(true, 3, 32, "32");
  mjolnir::MjolnirPriorityQueue::Element i(true, 1, 17, "17");
  mjolnir::MjolnirPriorityQueue::Element j(true, 3, 37, "37");
  mjolnir::MjolnirPriorityQueue::Element k(true, 2, 21, "21");
  mjolnir::MjolnirPriorityQueue::Element l(true, 3, 38, "38");
  mjolnir::MjolnirPriorityQueue::Element m(true, 2, 24, "24");
  mjolnir::MjolnirPriorityQueue::Element n(true, 3, 37, "37");

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
  que.Push(j);
  que.Push(k);
  que.Push(l);
  que.Push(m);
  que.Push(n);
  que.Push(d);
  que.Push(g);
  que.Push(h);
  que.Push(i);
  que.Push(j);
  que.Push(a);
  que.Push(c);
  que.Push(e);
  que.Push(f);
  que.Push(b);
  que.Push(a);
  que.Push(c);
  que.Push(e);
  que.Push(f);
  que.Push(b);

  auto size = que.GetQueueSize();
  for (auto i = 0; i < size; i++) {
    auto tmp = que.Pop();
    if (tmp.isInit)
      std::cout << "priority:" << tmp.priority
                << ", time_stamp:" << tmp.time_stamp
                << ", show_string:" << tmp.show_string
                << ", index:" << tmp.index << std::endl;
    else
      std::cout << "empty!" << std::endl;
  }
  return 0;
}

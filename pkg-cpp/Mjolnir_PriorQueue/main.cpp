#include "Mjolnir_PriorQueue.h"
#include <iostream>

namespace mjolnir {
  struct TestElement {
    TestElement(bool init = false, int prior = 0, uint64_t now = 0, uint16_t seq = 0, std::string str = "")
        : isInit(init),
          priority(prior),
          time_stamp(now),
          sequence(seq),
          show_string(std::move(str)) {}
    // 必须重载 < 号才能正常判断
    bool operator<(const TestElement &e) const noexcept {
      if (priority < e.priority)
        return true;
      else if (priority == e.priority) {
        if (time_stamp < e.time_stamp) {
          return true;
        } else if (time_stamp == e.time_stamp) {
          if (sequence < e.sequence) {
            if (e.sequence - sequence > 65536 / 2)
              return false;
            return true;
          } else if (sequence - e.sequence > 65536 / 2)
            return true;
          return false;
        }
        return false;
      } else {
        return false;
      }
    }

    int priority;
    uint64_t time_stamp;
    uint16_t sequence;
    std::string show_string;
    bool isInit;
  };
}// namespace mjolnir

int main() {

  mjolnir::TestElement a(true, 1, 10, 687, "687");
  mjolnir::TestElement c(true, 3, 11, 705, "705");
  mjolnir::TestElement e(true, 2, 12, 706, "706");
  mjolnir::TestElement f(true, 3, 13, 707, "707");
  mjolnir::TestElement b(true, 2, 14, 708, "708");
  mjolnir::TestElement d(true, 1, 15, 709, "709");
  mjolnir::TestElement g(true, 2, 10, 687, "687");
  mjolnir::TestElement h(true, 2, 10, 687, "687");
  mjolnir::TestElement i(true, 1, 18, 712, "712");
  mjolnir::TestElement j(true, 2, 9, 713, "713");
  mjolnir::TestElement k(true, 1, 20, 714, "714");
  mjolnir::TestElement l(true, 1, 21, 715, "715");
  mjolnir::TestElement m(true, 1, 22, 716, "716");
  mjolnir::TestElement n(true, 1, 23, 717, "717");
  mjolnir::TestElement o(true, 1, 25, 718, "718");
  mjolnir::TestElement p(true, 1, 25, 719, "719");
  mjolnir::TestElement q(true, 1, 26, 720, "720");
  mjolnir::TestElement r(true, 1, 27, 721, "721");
  mjolnir::TestElement s(true, 1, 28, 722, "722");
  mjolnir::TestElement t(true, 1, 29, 723, "723");
  mjolnir::TestElement u(true, 1, 30, 724, "724");



  mjolnir::MjolnirPriorityQueue<mjolnir::TestElement> que;
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
  auto size = que.GetQueueSize();
  for (auto i = 0; i < size; i++) {
    mjolnir::TestElement tmp = que.Pop();


    if (tmp.isInit)
      std::cout << "priority:" << tmp.priority
                << ", time_stamp:" << tmp.time_stamp
                << ", show_string:" << tmp.show_string
                << ", seq:" << tmp.sequence << std::endl;
  }


  return 0;
}

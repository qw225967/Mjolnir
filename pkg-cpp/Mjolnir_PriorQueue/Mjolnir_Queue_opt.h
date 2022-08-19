/*******************************************************
 * @author      : dog head
 * @date        : Created in 2022/8/16 4:24 下午
 * @mail        : qw225967@github.com
 * @project     : Mjolnir_PrioQueue
 * @file        : Mjolnir_Queue_opt.h
 * @description : TODO
 *******************************************************/


#ifndef MJOLNIR_PRIOQUEUE_MJOLNIR_QUEUE_OPT_H
#define MJOLNIR_PRIOQUEUE_MJOLNIR_QUEUE_OPT_H

#include <memory>

namespace mjolnir {
  // push
  template<class _Compare, class _RandomAccessIterator>
  void
  _Mjolnir_sift_up(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp,
                   typename std::iterator_traits<_RandomAccessIterator>::difference_type __len) {
    typedef typename std::iterator_traits<_RandomAccessIterator>::value_type value_type;
    if (__len > 1) {
      __len = (__len - 2) / 2;
      _RandomAccessIterator __ptr = __first + __len;
      if (__comp(*__ptr, *--__last)) {
        value_type __t(_VSTD::move(*__last));
        do {
          *__last = _VSTD::move(*__ptr);
          __last = __ptr;
          if (__len == 0)
            break;
          __len = (__len - 1) / 2;
          __ptr = __first + __len;
        } while (__comp(*__ptr, __t));
        *__last = _VSTD::move(__t);
      }
    }
  }

  template<class _RandomAccessIterator, class _Compare>
  inline _LIBCPP_INLINE_VISIBILITY void
  Mjolnir_push_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp) {
    typedef typename std::__comp_ref_type<_Compare>::type _Comp_ref;
    _Mjolnir_sift_up<_Comp_ref>(__first, __last, __comp, __last - __first);
  }


  // pop
  template<class _Compare, class _RandomAccessIterator>
  void
  _Mjolnir_sift_down(_RandomAccessIterator __first, _RandomAccessIterator /*__last*/,
                     _Compare __comp,
                     typename std::iterator_traits<_RandomAccessIterator>::difference_type __len,
                     _RandomAccessIterator __start) {
    typedef typename std::iterator_traits<_RandomAccessIterator>::difference_type difference_type;
    typedef typename std::iterator_traits<_RandomAccessIterator>::value_type value_type;
    // left-child of __start is at 2 * __start + 1
    // right-child of __start is at 2 * __start + 2
    difference_type __child = __start - __first;

    if (__len < 2 || (__len - 2) / 2 < __child)
      return;

    __child = 2 * __child + 1;
    _RandomAccessIterator __child_i = __first + __child;

    if ((__child + 1) < __len && __comp(*__child_i, *(__child_i + 1))) {
      // right-child exists and is greater than left-child
      ++__child_i;
      ++__child;
    }

    // check if we are in heap-order
    if (__comp(*__child_i, *__start))
      // we are, __start is larger than it's largest child
      return;

    value_type __top(_VSTD::move(*__start));
    do {
      // we are not in heap-order, swap the parent with it's largest child
      *__start = _VSTD::move(*__child_i);
      __start = __child_i;

      if ((__len - 2) / 2 < __child)
        break;

      // recompute the child based off of the updated parent
      __child = 2 * __child + 1;
      __child_i = __first + __child;

      if ((__child + 1) < __len && __comp(*__child_i, *(__child_i + 1))) {
        // right-child exists and is greater than left-child
        ++__child_i;
        ++__child;
      }

      // check if we are in heap-order
    } while (!__comp(*__child_i, __top));
    *__start = _VSTD::move(__top);
  }


  template<class _Compare, class _RandomAccessIterator>
  inline _LIBCPP_INLINE_VISIBILITY void
  _Mjolnir_pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp,
                    typename std::iterator_traits<_RandomAccessIterator>::difference_type __len) {
    if (__len > 1) {
      std::swap(*__first, *--__last);
      _Mjolnir_sift_down<_Compare>(__first, __last, __comp, __len - 1, __first);
    }
  }

  template<class _RandomAccessIterator, class _Compare>
  inline _LIBCPP_INLINE_VISIBILITY void
  Mjolnir_pop_heap(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp) {
    typedef typename std::__comp_ref_type<_Compare>::type _Comp_ref;
    _Mjolnir_pop_heap<_Comp_ref>(__first, __last, __comp, __last - __first);
  }

}// namespace mjolnir

#endif//MJOLNIR_PRIOQUEUE_MJOLNIR_QUEUE_OPT_H

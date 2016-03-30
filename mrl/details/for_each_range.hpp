//
//  for_each_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 29/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef for_each_range_h
#define for_each_range_h

#include "basic_range.hpp"

namespace mrl {

template <typename ForwardIt, typename F>
struct for_each_iterator : public std::iterator<std::input_iterator_tag, typename ForwardIt::value_type> {

   typedef typename ForwardIt::value_type value_type;

   for_each_iterator(ForwardIt first, ForwardIt last, F f)
      : m_first(first)
      , m_last(last)
      , m_apply(f) {}

   for_each_iterator& operator++() {
      ++m_first;
      return *this;
   }

   //   for_each_iterator operator++(int) {
   //      advance();
   //      return for_each_iterator(m_first, m_last, m_pred);
   //   }

   void operator*() const {
      m_apply(*m_first);
   }


   friend bool operator==(const for_each_iterator& a, const for_each_iterator& b) {
      return a.m_first == b.m_first;
   }

   friend bool operator!=(const for_each_iterator& a, const for_each_iterator& b) {
      return !(a == b);
   }

private:
   ForwardIt m_first;
   ForwardIt m_last;
   F         m_apply;
};

template <typename ForwardIt, typename F>
struct for_each_range {

   typedef for_each_iterator<ForwardIt, F> iterator;
   typedef typename ForwardIt::value_type value_type;

   for_each_range(ForwardIt first, ForwardIt last, F f)
      : m_first(first)
      , m_last(last)
      , m_apply(f) {}

   iterator begin() const {
      return iterator(m_first, m_last, m_apply);
   }

   iterator end() const {
      return iterator(m_last, m_last, m_apply);
   }


private:
   ForwardIt m_first;
   ForwardIt m_last;
   F         m_apply;
};

template <typename R, typename F>
void for_each(const R& r, F f) {}
}


#endif /* for_each_range_h */

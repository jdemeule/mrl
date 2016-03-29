//
//  join_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 29/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef join_range_h
#define join_range_h


#include <iterator>
#include "basic_range.hpp"

namespace mrl {

template <typename ForwardIt1, typename ForwardIt2>
struct join_iterator
   : public std::iterator<std::input_iterator_tag,
                          std::tuple<typename ForwardIt1::value_type, typename ForwardIt2::value_type> > {

   typedef std::tuple<typename ForwardIt1::value_type, typename ForwardIt2::value_type> value_type;

   join_iterator(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2, ForwardIt2 current2)
      : m_first1(first1)
      , m_last1(last1)
      , m_first2(first2)
      , m_last2(last2)
      , m_current2(current2) {}

   join_iterator& operator++() {
      advance();
      return *this;
   }

   join_iterator operator++(int) {
      advance();
      return join_iterator(m_first1, m_last1, m_first2, m_last2, m_current2);
   }

   value_type operator*() const {
      //      if (m_first1 != m_last1)
      //         return *m_first1;
      //      return *m_first2;
      return std::make_tuple(*m_first1, *m_current2);
   }

   friend bool operator==(const join_iterator& a, const join_iterator& b) {
      return a.m_first1 == b.m_first1 && a.m_current2 == b.m_current2;
   }

   friend bool operator!=(const join_iterator& a, const join_iterator& b) {
      return !(a == b);
   }

private:
   void advance() {
      if (++m_current2 == m_last2) {
         ++m_first1;
         if (m_first1 != m_last1)
            m_current2 = m_first2;
      }
   }

private:
   ForwardIt1 m_first1;
   ForwardIt1 m_last1;
   ForwardIt2 m_first2;
   ForwardIt2 m_last2;
   ForwardIt2 m_current2;
};

template <typename ForwardIt1, typename ForwardIt2>
struct join_range : public basic_range {

   typedef join_iterator<ForwardIt1, ForwardIt2> iterator;
   typedef typename ForwardIt1::value_type value_type;

   join_range(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2)
      : m_first1(first1)
      , m_last1(last1)
      , m_first2(first2)
      , m_last2(last2) {}

   iterator begin() const {
      return iterator(m_first1, m_last1, m_first2, m_last2, m_first2);
   }

   iterator end() const {
      return iterator(m_last1, m_last1, m_last2, m_last2, m_last2);
   }

private:
   ForwardIt1 m_first1;
   ForwardIt1 m_last1;
   ForwardIt2 m_first2;
   ForwardIt2 m_last2;
};



template <typename R1, typename R2>
auto make_join_range(const R1& r1, const R2& r2) {
   return join_range<typename R1::iterator, typename R2::iterator>(r1.begin(), r1.end(), r2.begin(), r2.end());
}
}

#endif /* join_range_h */

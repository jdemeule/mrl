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

#include <mrl/details/basic_range.hpp>

namespace mrl {


namespace details {
// rename to cross_join?
// cartesian_join?

template <typename InputIt1, typename ForwardIt2>
struct join_iterator
   : public std::iterator<std::input_iterator_tag,
                          std::tuple<typename InputIt1::value_type, typename ForwardIt2::value_type> > {

   typedef std::tuple<typename InputIt1::value_type, typename ForwardIt2::value_type> value_type;

   join_iterator(InputIt1 first1, InputIt1 last1, ForwardIt2 first2, ForwardIt2 last2, ForwardIt2 current2)
      : m_first1(first1)
      , m_last1(last1)
      , m_first2(first2)
      , m_last2(last2)
      , m_current2(current2) {}

   join_iterator& operator++() {
      next();
      return *this;
   }

   join_iterator operator++(int) {
      auto tmp(*this);
      next();
      return tmp;
   }

   value_type operator*() const {
      return std::make_tuple(*m_first1, *m_current2);
   }

   friend bool operator==(const join_iterator& a, const join_iterator& b) {
      return a.m_first1 == b.m_first1 && a.m_current2 == b.m_current2;
   }

   friend bool operator!=(const join_iterator& a, const join_iterator& b) {
      return !(a == b);
   }

private:
   void next() {
      if (++m_current2 == m_last2) {
         ++m_first1;
         if (m_first1 != m_last1)
            m_current2 = m_first2;
      }
   }

private:
   InputIt1   m_first1;
   InputIt1   m_last1;
   ForwardIt2 m_first2;
   ForwardIt2 m_last2;
   ForwardIt2 m_current2;
};
}

// variadic template on
// typename...ItRanges
template <typename InputIt1, typename ForwardIt2>
struct join_range : public basic_range {

   typedef details::join_iterator<InputIt1, ForwardIt2>                               iterator;
   typedef std::tuple<typename InputIt1::value_type, typename ForwardIt2::value_type> value_type;

   join_range(InputIt1 first1, InputIt1 last1, ForwardIt2 first2, ForwardIt2 last2)
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
   InputIt1   m_first1;
   InputIt1   m_last1;
   ForwardIt2 m_first2;
   ForwardIt2 m_last2;
   // store tuple of ItRanges
};


template <typename InputIt1, typename InputIt2>
auto make_join_range(InputIt1 first1, InputIt2 last1, InputIt2 first2, InputIt2 last2) {
   return join_range<InputIt1, InputIt2>(first1, last1, first2, last2);
}

template <typename R1,
          typename R2,
          typename std::enable_if_t<is_range<R1>::value>* = nullptr,
          typename std::enable_if_t<is_range<R2>::value>* = nullptr>
auto make_join_range(const R1& r1, const R2& r2) {
   // transform typename...Rs to std::tuple<iterator_range<Rs::iterator>...)
   return join_range<typename R1::iterator, typename R2::iterator>(r1.begin(), r1.end(), r2.begin(), r2.end());
}
}

#endif /* join_range_h */

//
//  concat_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 29/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef concat_range_h
#define concat_range_h


#include <iterator>
#include <mrl/details/basic_range.hpp>

namespace mrl {

template <typename ForwardIt1, typename ForwardIt2>
struct concat_iterator : public std::iterator<std::input_iterator_tag, typename ForwardIt1::value_type> {

   typedef typename ForwardIt1::value_type value_type;

   concat_iterator(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2)
      : m_first1(first1)
      , m_last1(last1)
      , m_first2(first2)
      , m_last2(last2) {}

   concat_iterator& operator++() {
      advance();
      return *this;
   }

   concat_iterator operator++(int) {
      advance();
      return concat_iterator(m_first1, m_last1, m_first2, m_last2);
   }

   value_type operator*() const {
      if (m_first1 != m_last1)
         return *m_first1;
      return *m_first2;
   }

   friend bool operator==(const concat_iterator& a, const concat_iterator& b) {
      return a.m_first1 == b.m_first1 && a.m_first2 == b.m_first2;
   }

   friend bool operator!=(const concat_iterator& a, const concat_iterator& b) {
      return !(a == b);
   }

private:
   void advance() {
      if (m_first1 != m_last1)
         ++m_first1;
      else
         ++m_first2;
   }

private:
   ForwardIt1 m_first1;
   ForwardIt1 m_last1;
   ForwardIt2 m_first2;
   ForwardIt2 m_last2;
};

template <typename ForwardIt1, typename ForwardIt2>
struct concat_range : public basic_range {

   typedef concat_iterator<ForwardIt1, ForwardIt2> iterator;
   typedef typename ForwardIt1::value_type value_type;

   concat_range(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2)
      : m_first1(first1)
      , m_last1(last1)
      , m_first2(first2)
      , m_last2(last2) {}

   iterator begin() const {
      return iterator(m_first1, m_last1, m_first2, m_last2);
   }

   iterator end() const {
      return iterator(m_last1, m_last1, m_last2, m_last2);
   }

private:
   ForwardIt1 m_first1;
   ForwardIt1 m_last1;
   ForwardIt2 m_first2;
   ForwardIt2 m_last2;
};



template <typename R1, typename R2>
auto make_concat_range(const R1& r1, const R2& r2) {
   return concat_range<typename R1::iterator, typename R2::iterator>(r1.begin(), r1.end(), r2.begin(), r2.end());
}
}

#endif /* concat_range_h */

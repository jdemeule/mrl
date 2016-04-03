//
//  zip_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef zip_range_h
#define zip_range_h


#include <iterator>

#include <mrl/details/basic_range.hpp>

namespace mrl {
template <typename ForwardIt1, typename ForwardIt2>
struct zip_iterator
   : public std::iterator<std::input_iterator_tag,
                          std::tuple<typename ForwardIt1::value_type, typename ForwardIt2::value_type> > {

   typedef std::tuple<typename ForwardIt1::value_type, typename ForwardIt2::value_type> value_type;

   zip_iterator(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2)
      : m_first1(first1)
      , m_last1(last1)
      , m_first2(first2)
      , m_last2(last2) {}

   zip_iterator& operator++() {
      ++m_first1;
      ++m_first2;
      return *this;
   }

   zip_iterator operator++(int) {
      auto current(*this);
      ++m_first1;
      ++m_first2;
      return current;
   }

   value_type operator*() const {
      return std::make_tuple(*m_first1, *m_first2);
   }

   friend bool operator==(const zip_iterator& a, const zip_iterator& b) {
      return a.m_first1 == b.m_first1 && a.m_first2 == b.m_first2;
   }

   friend bool operator!=(const zip_iterator& a, const zip_iterator& b) {
      return !(a == b);
   }

private:
   ForwardIt1 m_first1;
   ForwardIt1 m_last1;
   ForwardIt2 m_first2;
   ForwardIt2 m_last2;
};

template <typename ForwardIt1, typename ForwardIt2>
struct zip_range : public basic_range {

   typedef zip_iterator<ForwardIt1, ForwardIt2>                                         iterator;
   typedef std::tuple<typename ForwardIt1::value_type, typename ForwardIt2::value_type> value_type;

   zip_range(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2)
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
auto make_zip_range(const R1& r1, const R2& r2) {
   // return a stream of tuple<R1::value, R2::value>
   return zip_range<typename R1::iterator, typename R2::iterator>(r1.begin(), r1.end(), r2.begin(), r2.end());
}
}

#endif /* zip_range_h */

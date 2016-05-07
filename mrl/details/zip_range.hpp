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


template <typename InputIterator>
struct cursor {
   typedef typename InputIterator::value_type value_type;

   cursor() = default;
   cursor(InputIterator first, InputIterator last)
      : m_first(first)
      , m_last(last) {}

   bool done() const {
      return m_first == m_last;
   }

   void next() {
      ++m_first;
   }

   value_type value() const {
      return *m_first;
   }

   InputIterator m_first;
   InputIterator m_last;
};

template <typename InputIt1, typename InputIt2>
struct zip_iterator : public std::iterator<std::input_iterator_tag,
                                           std::tuple<typename InputIt1::value_type, typename InputIt2::value_type> > {

   typedef std::tuple<typename InputIt1::value_type, typename InputIt2::value_type> value_type;

   zip_iterator(cursor<InputIt1> first, cursor<InputIt2> second)
      : m_c0(first)
      , m_c1(second)
      , m_sentinel(false) {}

private:
   explicit zip_iterator(bool sentinel)
      : m_sentinel(true) {}

public:
   static zip_iterator sentinel() {
      return zip_iterator(true);
   }

   zip_iterator& operator++() {
      m_c0.next();
      m_c1.next();
      return *this;
   }

   zip_iterator operator++(int) {
      auto current(*this);
      m_c0.next();
      m_c1.next();
      return current;
   }

   value_type operator*() const {
      return std::make_tuple(m_c0.value(), m_c1.value());
   }

   friend bool operator==(const zip_iterator& a, const zip_iterator& b) {
      if (a.m_sentinel)
         return b.m_c0.done() || b.m_c1.done();
      if (b.m_sentinel)
         return a.m_c0.done() || a.m_c1.done();
      return false;
      //      return a.m_first1 == b.m_first1 && a.m_first2 == b.m_first2;
   }

   friend bool operator!=(const zip_iterator& a, const zip_iterator& b) {
      return !(a == b);
   }

private:
   cursor<InputIt1> m_c0;
   cursor<InputIt2> m_c1;
   bool             m_sentinel;
   //   InputIt1         m_first1;
   //   InputIt1         m_last1;
   //   InputIt2         m_first2;
   //   InputIt2         m_last2;
};

// must stop when 1 range is fully consumed
template <typename InputIt1, typename InputIt2>
struct zip_range : public basic_range {

   typedef zip_iterator<InputIt1, InputIt2>                                         iterator;
   typedef std::tuple<typename InputIt1::value_type, typename InputIt2::value_type> value_type;

   zip_range(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
      : m_first1(first1)
      , m_last1(last1)
      , m_first2(first2)
      , m_last2(last2) {}

   iterator begin() const {
      return iterator(cursor<InputIt1>(m_first1, m_last1), cursor<InputIt2>(m_first2, m_last2));
   }

   iterator end() const {
      return iterator::sentinel();
   }

private:
   InputIt1 m_first1;
   InputIt1 m_last1;
   InputIt2 m_first2;
   InputIt2 m_last2;
};


template <typename InputIt1, typename InputIt2>
auto make_zip_range(InputIt1 first1, InputIt2 last1, InputIt2 first2, InputIt2 last2) {
   return zip_range<InputIt1, InputIt2>(first1, last1, first2, last2);
}


template <typename R1,
          typename R2,
          typename std::enable_if_t<is_range<R1>::value>* = nullptr,
          typename std::enable_if_t<is_range<R2>::value>* = nullptr>
auto make_zip_range(const R1& r1, const R2& r2) {
   // return a stream of tuple<R1::value, R2::value>
   return zip_range<typename R1::iterator, typename R2::iterator>(r1.begin(), r1.end(), r2.begin(), r2.end());
}
}

#endif /* zip_range_h */

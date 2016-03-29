//
//  flatten_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 29/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef flatten_range_h
#define flatten_range_h


#include <iterator>
#include <memory>
#include "basic_range.hpp"


namespace mrl {

// template <typename ForwardIt>
// struct flatten_cursor {
//};

template <typename ForwardIt1>
struct flatten_iterator : public std::iterator<std::input_iterator_tag, typename ForwardIt1::value_type::value_type> {

   typedef typename ForwardIt1::value_type::const_iterator ForwardIt2;
   typedef typename ForwardIt2::value_type                 value_type;


   flatten_iterator(ForwardIt1 first1, ForwardIt1 last1, bool sentinel = false)
      : m_first1(first1)
      , m_last1(last1)
      , m_first2()
      , m_last2()
      , m_sentinel(sentinel) {
      if (m_first1 != m_last1) {
         m_first2 = std::make_unique<ForwardIt2>((*m_first1).begin());
         m_last2  = std::make_unique<ForwardIt2>((*m_first1).end());
      }
   }

   flatten_iterator(const flatten_iterator& rhs)
      : m_first1(rhs.m_first1)
      , m_last1(rhs.m_last1)
      , m_first2()
      , m_last2()
      , m_sentinel(rhs.m_sentinel) {
      if (m_first1 != m_last1) {
         m_first2 = std::make_unique<ForwardIt2>(*rhs.m_first2);
         m_last2  = std::make_unique<ForwardIt2>(*rhs.m_last2);
      }
   }

   flatten_iterator& operator=(const flatten_iterator& rhs) {
      flatten_iterator tmp(rhs);
      swap(tmp);
      return *this;
   }

   void swap(flatten_iterator& that) {
      std::swap(m_first1, that.m_first1);
      std::swap(m_last1, that.m_last1);
      auto ptr = m_first2.release();
      m_first2.reset(that.m_first2.release());
      that.m_first2.reset(ptr);
      ptr = m_last2.release();
      m_last2.reset(that.m_last2.release());
      that.m_last2.reset(ptr);
      std::swap(m_sentinel, that.m_sentinel);
   }

   flatten_iterator& operator++() {
      advance();
      return *this;
   }

   //   join_iterator operator++(int) {
   //      advance();
   //      return join_iterator(m_first1, m_last1, m_first2, m_last2, m_current2);
   //   }

   value_type operator*() const {
      return **m_first2;
   }

   friend bool operator==(const flatten_iterator& a, const flatten_iterator& b) {
      if (a.m_sentinel || b.m_sentinel)
         return a.m_first1 == b.m_first1;
      return a.m_first1 == b.m_first1 && *a.m_first2 == *b.m_first2;
   }

   friend bool operator!=(const flatten_iterator& a, const flatten_iterator& b) {
      return !(a == b);
   }

private:
   void advance() {
      if (++(*m_first2) == (*m_last2)) {
         ++m_first1;
         if (m_first1 != m_last1) {
            *m_first2 = (*m_first1).begin();
            *m_last2  = (*m_first1).end();
         }
      }
   }

private:
   ForwardIt1 m_first1;
   ForwardIt1 m_last1;

   std::unique_ptr<ForwardIt2> m_first2;
   std::unique_ptr<ForwardIt2> m_last2;

   bool m_sentinel;
};

template <typename ForwardIt>
struct flatten_range : public basic_range {

   typedef flatten_iterator<ForwardIt>                iterator;
   typedef flatten_iterator<ForwardIt>                const_iterator;
   typedef typename ForwardIt::value_type::value_type value_type;

   flatten_range(ForwardIt first1, ForwardIt last1)
      : m_first(first1)
      , m_last(last1) {}

   iterator begin() const {
      return iterator(m_first, m_last);  // iterator from *m_first
      // iterator(m_first, m_last)
   }

   iterator end() const {
      return iterator(m_last, m_last, true);  // sentinel
      // sentinel
   }

private:
   ForwardIt m_first;
   ForwardIt m_last;
};



template <typename R1>
auto make_flatten_range(const R1& r1) {
   return flatten_range<typename R1::iterator>(r1.begin(), r1.end());
}
}

#endif /* flatten_range_h */

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

#include <mrl/details/basic_range.hpp>


namespace mrl {


template <typename ForwardIt1>
struct flatten_iterator : public std::iterator<std::input_iterator_tag, typename ForwardIt1::value_type::value_type> {

   typedef typename ForwardIt1::value_type::const_iterator ForwardIt2;
   typedef typename ForwardIt2::value_type                 value_type;


   flatten_iterator(ForwardIt1 first, ForwardIt1 last, bool sentinel = false)
      : m_outer_it(first)
      , m_outer_last(last)
      , m_inner_it()
      , m_sentinel(sentinel) {
      if (m_outer_it != m_outer_last) {
         m_inner_it = std::make_unique<ForwardIt2>((*m_outer_it).begin());
         skip_to_next_inner_range();
      }
   }

   flatten_iterator(const flatten_iterator& rhs)
      : m_outer_it(rhs.m_outer_it)
      , m_outer_last(rhs.m_outer_last)
      , m_inner_it()
      , m_sentinel(rhs.m_sentinel) {
      if (m_outer_it != m_outer_last) {
         m_inner_it = std::make_unique<ForwardIt2>(*rhs.m_inner_it);
      }
   }

   flatten_iterator& operator=(const flatten_iterator& rhs) {
      flatten_iterator tmp(rhs);
      swap(tmp);
      return *this;
   }

   void swap(flatten_iterator& that) {
      std::swap(m_outer_it, that.m_outer_it);
      std::swap(m_outer_last, that.m_outer_last);
      auto ptr = m_inner_it.release();
      m_inner_it.reset(that.m_inner_it.release());
      that.m_inner_it.reset(ptr);
      std::swap(m_sentinel, that.m_sentinel);
   }

   flatten_iterator& operator++() {
      ++*m_inner_it;
      skip_to_next_inner_range();
      return *this;
   }

   value_type operator*() const {
      return **m_inner_it;
   }

   friend bool operator==(const flatten_iterator& a, const flatten_iterator& b) {
      if (a.m_sentinel || b.m_sentinel)
         return a.m_outer_it == b.m_outer_it;
      return a.m_outer_it == b.m_outer_it && *a.m_inner_it == *b.m_inner_it;
   }

   friend bool operator!=(const flatten_iterator& a, const flatten_iterator& b) {
      return !(a == b);
   }

private:
   void skip_to_next_inner_range() {
      if (*m_inner_it == (*m_outer_it).end()) {
         while (m_outer_it != m_outer_last && *m_inner_it == (*m_outer_it).end()) {
            ++m_outer_it;
            *m_inner_it = (*m_outer_it).begin();
         }
      }
   }

private:
   ForwardIt1 m_outer_it;
   ForwardIt1 m_outer_last;

   std::unique_ptr<ForwardIt2> m_inner_it;
   //   std::unique_ptr<ForwardIt2> m_last2;

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

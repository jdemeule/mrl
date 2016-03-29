//
//  transform_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef transform_range_h
#define transform_range_h

#include <iterator>
#include <type_traits>
#include "basic_range.hpp"

namespace mrl {

template <typename ForwardIt, typename F>
struct transform_iterator
   : public std::iterator<std::input_iterator_tag, typename std::result_of<F(typename ForwardIt::value_type)>::type> {

   typedef typename std::result_of<F(typename ForwardIt::value_type)>::type value_type;

   transform_iterator()
      : m_first()
      , m_last()
      , m_apply() {}

   transform_iterator(ForwardIt first, ForwardIt last, F apply)
      : m_first(first)
      , m_last(last)
      , m_apply(apply) {}

   transform_iterator& operator++() {
      ++m_first;
      return *this;
   }

   transform_iterator operator++(int) {
      ++m_first;
      return transform_iterator(m_first, m_last, m_apply);
   }

   value_type operator*() const {
      return m_apply(*m_first);
   }

   friend bool operator==(const transform_iterator& a, const transform_iterator& b) {
      return a.m_first == b.m_first;
   }

   friend bool operator!=(const transform_iterator& a, const transform_iterator& b) {
      return !(a == b);
   }

private:
   ForwardIt m_first;
   ForwardIt m_last;
   F         m_apply;
};

template <typename ForwardIt, typename F>
struct transform_range : public basic_range {

   typedef transform_iterator<ForwardIt, F> const_iterator;
   typedef transform_iterator<ForwardIt, F> iterator;
   typedef typename std::result_of<F(typename ForwardIt::value_type)>::type value_type;

   transform_range(ForwardIt first, ForwardIt last, F apply)
      : m_first(first)
      , m_last(last)
      , m_apply(apply) {}

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

template <typename ForwardIt, typename F>
transform_range<ForwardIt, F> make_transform_range(ForwardIt first, ForwardIt last, F apply) {
   return transform_range<ForwardIt, F>(first, last, apply);
}

template <typename Rg, typename F, typename std::enable_if<std::is_base_of<basic_range, Rg>::value>::type* = nullptr>
transform_range<typename Rg::iterator, F> make_transform_range(const Rg& rg, F apply) {
   return transform_range<typename Rg::iterator, F>(rg.begin(), rg.end(), apply);
};
}

#endif /* transform_range_h */

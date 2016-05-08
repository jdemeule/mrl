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

#include <experimental/optional>

#include <mrl/details/basic_range.hpp>

namespace mrl {

template <typename InputIt, typename F>
struct transform_iterator : public std::iterator<range_iterator_category_t<InputIt>,
                                                 typename std::result_of<F(typename InputIt::value_type)>::type> {

   typedef typename std::result_of<F(typename InputIt::value_type)>::type value_type;

   typedef std::experimental::optional<F> fun_ref;

   transform_iterator()
      : m_first()
      , m_last()
      , m_apply() {}

   transform_iterator(InputIt first, InputIt last, F apply)
      : m_first(first)
      , m_last(last)
      , m_apply(apply) {}

   transform_iterator& operator++() {
      ++m_first;
      return *this;
   }

   transform_iterator operator++(int) {
      auto current(*this);
      ++m_first;
      return current;
   }

   value_type operator*() const {
      return (*m_apply)(*m_first);
   }

   friend bool operator==(const transform_iterator& a, const transform_iterator& b) {
      return a.m_first == b.m_first;
   }

   friend bool operator!=(const transform_iterator& a, const transform_iterator& b) {
      return !(a == b);
   }

private:
   InputIt m_first;
   InputIt m_last;
   fun_ref m_apply;
};

template <typename InputIt, typename F>
struct transform_range : public basic_range {

   typedef transform_iterator<InputIt, F> const_iterator;
   typedef transform_iterator<InputIt, F> iterator;
   typedef typename std::result_of<F(typename InputIt::value_type)>::type value_type;

   transform_range(InputIt first, InputIt last, const F& apply)
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
   InputIt m_first;
   InputIt m_last;
   F       m_apply;
};

template <typename InputIt, typename F>
auto make_transform_range(InputIt first, InputIt last, F apply) {
   return transform_range<InputIt, F>(first, last, apply);
}

template <typename R, typename F, typename std::enable_if_t<is_range<R>::value>* = nullptr>
auto make_transform_range(const R& r, F apply) {
   return transform_range<typename R::iterator, F>(r.begin(), r.end(), apply);
};
}

#endif /* transform_range_h */

//
//  take_n_range.h
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef take_n_range_h
#define take_n_range_h

#include <iterator>

#include <mrl/details/basic_range.hpp>

namespace mrl {

template <typename InputIt>
struct take_n_iterator : public std::iterator<range_iterator_category_t<InputIt>, typename InputIt::value_type> {

   typedef typename InputIt::value_type value_type;

   take_n_iterator(InputIt first, InputIt last, std::size_t count, bool sentinel = false)
      : m_first(first)
      , m_last(last)
      , m_count(count)
      , m_sentinel(sentinel) {}

   take_n_iterator& operator++() {
      next();
      return *this;
   }

   take_n_iterator operator++(int) {
      auto current(*this);
      next();
      return current;
   }

   value_type operator*() const {
      return *m_first;
   }

   friend bool operator==(const take_n_iterator& a, const take_n_iterator& b) {
      if (a.m_sentinel || b.m_sentinel)
         return a.m_count == b.m_count;
      return a.m_first == b.m_first && a.m_count == b.m_count;
   }

   friend bool operator!=(const take_n_iterator& a, const take_n_iterator& b) {
      return !(a == b);
   }

private:
   void next() {
      if (m_first != m_last) {
         ++m_first;
         --m_count;
      }

      if (m_first == m_last)
         m_count = 0;
   }

   InputIt     m_first;
   InputIt     m_last;
   std::size_t m_count;
   bool        m_sentinel;
};

template <typename InputIt>
struct take_n_range : public basic_range {

   typedef take_n_iterator<InputIt>     iterator;
   typedef take_n_iterator<InputIt>     const_iterator;
   typedef typename InputIt::value_type value_type;

   take_n_range(InputIt first, InputIt last, std::size_t count)
      : m_first(first)
      , m_last(last)
      , m_count(count) {}

   iterator begin() const {
      return iterator(m_first, m_last, m_count);
   }

   iterator end() const {
      return iterator(m_last, m_last, 0, true);
   }

private:
   InputIt     m_first;
   InputIt     m_last;
   std::size_t m_count;
};

template <typename InputIt>
auto make_take_n_range(InputIt first, InputIt last, std::size_t count) {
   return take_n_range<InputIt>(first, last, count);
}

template <typename R, typename std::enable_if_t<is_range<R>::value>* = nullptr>
auto make_take_n_range(const R& r, std::size_t count) {
   return take_n_range<typename R::iterator>(r.begin(), r.end(), count);
};
}

#endif /* take_n_range_h */

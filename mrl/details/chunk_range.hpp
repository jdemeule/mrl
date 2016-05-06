//
//  chunk_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 29/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef chunk_range_h
#define chunk_range_h


#include <iterator>
#include <mrl/details/basic_range.hpp>
#include <mrl/details/take_n_range.hpp>

namespace mrl {

template <typename InputIt>
struct chunk_iterator : public std::iterator<range_iterator_category_t<InputIt>, take_n_range<InputIt> > {

   typedef take_n_range<InputIt> value_type;

   chunk_iterator(InputIt first, InputIt last, std::size_t count, bool sentinel = false)
      : m_first(first)
      , m_last(last)
      , m_count(count)
      , m_sentinel(sentinel) {}

   chunk_iterator& operator++() {
      next();
      return *this;
   }

   chunk_iterator operator++(int) {
      auto current(*this);
      next();
      return current;
   }

   value_type operator*() const {
      return make_take_n_range(m_first, m_last, m_count);
   }

   friend bool operator==(const chunk_iterator& a, const chunk_iterator& b) {
      return a.m_first == b.m_first;
   }

   friend bool operator!=(const chunk_iterator& a, const chunk_iterator& b) {
      return !(a == b);
   }

private:
   void next() {
      for (std::size_t count = 0; m_first != m_last && count != m_count; ++m_first, ++count)
         ;
   }

   InputIt     m_first;
   InputIt     m_last;
   std::size_t m_count;
   bool        m_sentinel;
};

template <typename InputIt>
struct chunk_range : public basic_range {

   typedef chunk_iterator<InputIt> iterator;
   typedef chunk_iterator<InputIt> const_iterator;
   typedef take_n_range<InputIt>   value_type;

   chunk_range(InputIt first, InputIt last, std::size_t count)
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
auto make_chunk_range(InputIt first, InputIt last, std::size_t count) {
   return chunk_range<InputIt>(first, last, count);
}

template <typename R, typename std::enable_if_t<is_range<R>::value>* = nullptr>
auto make_chunk_range(const R& r, std::size_t count) {
   return chunk_range<typename R::iterator>(r.begin(), r.end(), count);
};
}

#endif

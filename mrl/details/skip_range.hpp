//
//  skip_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 31/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef skip_range_h
#define skip_range_h

#include <iterator>

#include <mrl/details/basic_range.hpp>

namespace mrl {

namespace details {
template <typename InputIt>
struct skip_iterator : public std::iterator<range_iterator_category_t<InputIt>, typename InputIt::value_type> {

   typedef typename InputIt::value_type value_type;

   skip_iterator(InputIt first, InputIt last, std::size_t count)
      : m_first(first)
      , m_last(last)
      , m_count(count) {
      skip_to_first();
   }

   skip_iterator& operator++() {
      ++m_first;
      return *this;
   }

   skip_iterator operator++(int) {
      auto current(*this);
      ++m_first;
      return current;
   }

   value_type operator*() const {
      return *m_first;
   }

   friend bool operator==(const skip_iterator& a, const skip_iterator& b) {
      return a.m_first == b.m_first;
   }

   friend bool operator!=(const skip_iterator& a, const skip_iterator& b) {
      return !(a == b);
   }

private:
   void skip_to_first() {
      while (m_count != 0 && m_first != m_last) {
         ++m_first;
         --m_count;
      }

      if (m_first == m_last)
         m_count = 0;
   }

   InputIt     m_first;
   InputIt     m_last;
   std::size_t m_count;
};
}

template <typename InputIt>
struct skip_range : public basic_range {

   typedef details::skip_iterator<InputIt> iterator;
   typedef details::skip_iterator<InputIt> const_iterator;
   typedef typename InputIt::value_type    value_type;

   skip_range(InputIt first, InputIt last, std::size_t count)
      : m_first(first)
      , m_last(last)
      , m_count(count) {}

   iterator begin() const {
      return iterator(m_first, m_last, m_count);
   }

   iterator end() const {
      return iterator(m_last, m_last, 0);
   }

private:
   InputIt     m_first;
   InputIt     m_last;
   std::size_t m_count;
};

template <typename InputIt>
auto make_skip_range(InputIt first, InputIt last, std::size_t count) {
   return skip_range<InputIt>(first, last, count);
}

template <typename R, typename std::enable_if_t<is_range<R>::value>* = nullptr>
auto make_skip_range(const R& r, std::size_t count) {
   return skip_range<typename R::iterator>(r.begin(), r.end(), count);
};
}


#endif /* skip_range_h */

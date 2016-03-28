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
#include "basic_range.hpp"

namespace mrl {
template <typename ForwardIt>
struct take_n_iterator : public std::iterator<std::input_iterator_tag, typename ForwardIt::value_type> {

   typedef typename ForwardIt::value_type value_type;

   take_n_iterator(ForwardIt first, ForwardIt last, std::size_t count)
      : m_first(first)
      , m_last(last)
      , m_count(count) {}

   take_n_iterator& operator++() {
      advance();
      return *this;
   }

   //   take_n_iterator operator++(int) {
   //      advance();
   //      return take_n_iterator(m_first, m_last, m_count);
   //   }

   value_type operator*() const {
      return *m_first;
   }

   friend bool operator==(const take_n_iterator& a, const take_n_iterator& b) {
      return a.m_first == b.m_first;
   }

   friend bool operator!=(const take_n_iterator& a, const take_n_iterator& b) {
      return !(a == b);
   }

private:
   void advance() {
      if (m_count == 0)
         m_first = m_last;

      if (m_first != m_last) {
         ++m_first;
         --m_count;
      }

      if (m_count == 0)
         m_first = m_last;
   }

   ForwardIt   m_first;
   ForwardIt   m_last;
   std::size_t m_count;
};

template <typename ForwardIt>
struct take_n_range : public basic_range {

   typedef take_n_iterator<ForwardIt>     iterator;
   typedef typename ForwardIt::value_type value_type;

   take_n_range(ForwardIt first, ForwardIt last, std::size_t count)
      : m_first(first)
      , m_last(last)
      , m_count(count) {}

   iterator begin() const {
      return iterator(m_first, m_last, m_count);
   }

   iterator end() const {
      return iterator(m_last, m_last, m_count);
   }

private:
   ForwardIt   m_first;
   ForwardIt   m_last;
   std::size_t m_count;
};

template <typename ForwardIt>
take_n_range<ForwardIt> make_take_n_range(ForwardIt first, ForwardIt last, std::size_t count) {
   return take_n_range<ForwardIt>(first, last, count);
}

template <typename Rg, typename std::enable_if<std::is_base_of<basic_range, Rg>::value>::type* = nullptr>
take_n_range<typename Rg::iterator> make_take_n_range(const Rg& rg, std::size_t count) {
   return take_n_range<typename Rg::iterator>(rg.begin(), rg.end(), count);
};
}

#endif /* take_n_range_h */

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

template <typename ForwardIt>
struct skip_iterator : public std::iterator<range_iterator_category_t<ForwardIt>, typename ForwardIt::value_type> {

   typedef typename ForwardIt::value_type value_type;

   skip_iterator(ForwardIt first, ForwardIt last, std::size_t count)
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

   ForwardIt   m_first;
   ForwardIt   m_last;
   std::size_t m_count;
};

template <typename ForwardIt>
struct skip_range : public basic_range {

   typedef skip_iterator<ForwardIt>       iterator;
   typedef skip_iterator<ForwardIt>       const_iterator;
   typedef typename ForwardIt::value_type value_type;

   skip_range(ForwardIt first, ForwardIt last, std::size_t count)
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
   ForwardIt   m_first;
   ForwardIt   m_last;
   std::size_t m_count;
};

template <typename ForwardIt>
skip_range<ForwardIt> make_skip_range(ForwardIt first, ForwardIt last, std::size_t count) {
   return skip_range<ForwardIt>(first, last, count);
}

template <typename Rg, typename std::enable_if<std::is_base_of<basic_range, Rg>::value>::type* = nullptr>
skip_range<typename Rg::iterator> make_skip_range(const Rg& rg, std::size_t count) {
   return skip_range<typename Rg::iterator>(rg.begin(), rg.end(), count);
};
}


#endif /* skip_range_h */

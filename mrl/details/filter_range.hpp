//
//  filter_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef filter_range_h
#define filter_range_h

#include <iterator>
#include <mrl/details/basic_range.hpp>

namespace mrl {

// not necessary an input_iterator
// this will depends on int parameter, a forward is minimal to work
// an input will limit the postfix increment.

template <typename ForwardIt, typename Predicate>
struct filter_iterator : public std::iterator<range_iterator_category_t<ForwardIt>, typename ForwardIt::value_type> {


   typedef typename ForwardIt::value_type value_type;

   filter_iterator(ForwardIt first, ForwardIt last, Predicate pred)
      : m_first(first)
      , m_last(last)
      , m_pred(pred) {
      next();
   }


   filter_iterator& operator++() {
      ++m_first;
      next();
      return *this;
   }

   filter_iterator operator++(int) {
      auto current = m_first;
      ++m_first;
      next();
      return filter_iterator(current, m_last, m_pred);
   }

   value_type operator*() const {
      return *m_first;
   }


   friend bool operator==(const filter_iterator& a, const filter_iterator& b) {
      return a.m_first == b.m_first;
   }

   friend bool operator!=(const filter_iterator& a, const filter_iterator& b) {
      return !(a == b);
   }

private:
   void next() {
      if (m_first == m_last)
         return;

      while (m_first != m_last && !m_pred(*m_first))
         ++m_first;
   }

   ForwardIt m_first;
   ForwardIt m_last;
   Predicate m_pred;
};



template <typename ForwardIt, typename Predicate>
struct filter_range : public basic_range {

   typedef filter_iterator<ForwardIt, Predicate> iterator;
   typedef filter_iterator<ForwardIt, Predicate> const_iterator;
   typedef typename ForwardIt::value_type value_type;

   filter_range(ForwardIt first, ForwardIt last, Predicate pred)
      : m_first(first)
      , m_last(last)
      , m_pred(pred) {}

   iterator begin() const {
      return iterator(m_first, m_last, m_pred);
   }

   iterator end() const {
      return iterator(m_last, m_last, m_pred);
   }

private:
   ForwardIt m_first;
   ForwardIt m_last;
   Predicate m_pred;
};

template <typename ForwardIt, typename Predicate>
filter_range<ForwardIt, Predicate> make_filter_range(ForwardIt first, ForwardIt last, Predicate pred) {
   return filter_range<ForwardIt, Predicate>(first, last, pred);
}

template <typename Rg,
          typename Predicate,
          typename std::enable_if<std::is_base_of<basic_range, Rg>::value>::type* = nullptr>
filter_range<typename Rg::iterator, Predicate> make_filter_range(const Rg& rg, Predicate pred) {
   return filter_range<typename Rg::iterator, Predicate>(rg.begin(), rg.end(), pred);
};
}

#endif /* filter_range_h */

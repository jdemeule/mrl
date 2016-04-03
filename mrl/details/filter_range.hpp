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

template <typename InputIt, typename Predicate>
struct filter_iterator : public std::iterator<range_iterator_category_t<InputIt>, typename InputIt::value_type> {


   typedef typename InputIt::value_type value_type;

   filter_iterator(InputIt first, InputIt last, Predicate pred)
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

   InputIt   m_first;
   InputIt   m_last;
   Predicate m_pred;
};



template <typename InputIt, typename Predicate>
struct filter_range : public basic_range {

   typedef filter_iterator<InputIt, Predicate> iterator;
   typedef filter_iterator<InputIt, Predicate> const_iterator;
   typedef typename InputIt::value_type value_type;

   filter_range(InputIt first, InputIt last, Predicate pred)
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
   InputIt   m_first;
   InputIt   m_last;
   Predicate m_pred;
};

template <typename InputIt, typename Predicate>
auto make_filter_range(InputIt first, InputIt last, Predicate pred) {
   return filter_range<InputIt, Predicate>(first, last, pred);
}

template <typename R, typename Predicate, typename std::enable_if_t<is_range<R>::value>* = nullptr>
auto make_filter_range(const R& r, Predicate pred) {
   return filter_range<typename R::iterator, Predicate>(r.begin(), r.end(), pred);
};
}

#endif /* filter_range_h */

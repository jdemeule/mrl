//
//  num_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef num_range_h
#define num_range_h

#include <iterator>
#include <limits>

#include <experimental/optional>

#include <mrl/details/basic_range.hpp>

namespace mrl {

namespace details {
// Rename it itoa_range?

template <typename T, typename Generator>
struct nums_iterator : public std::iterator<std::input_iterator_tag, T> {

   typedef T value_type;

   typedef std::experimental::optional<Generator> gen_ref;

   nums_iterator()
      : m_first()
      , m_gen() {}

   nums_iterator(const nums_iterator& rhs)
      : m_first(rhs.m_first)
      , m_gen(rhs.m_gen) {}

   nums_iterator& operator=(const nums_iterator& rhs) {
      nums_iterator tmp(rhs);
      swap(tmp);
      return *this;
   }

   nums_iterator(T first, Generator gen)
      : m_first(first)
      , m_gen(gen) {}

   nums_iterator(T first, gen_ref gen)
      : m_first(first)
      , m_gen(gen) {}


   void swap(nums_iterator& that) {
      using std::swap;
      swap(m_first, that.m_first);
      swap(m_gen, that.m_gen);
   }

   nums_iterator& operator++() {
      m_first = (*m_gen)(m_first);
      return *this;
   }

   nums_iterator operator++(int) {
      m_first = (*m_gen)(m_first);
      return nums_iterator(m_first, m_gen);
   }

   value_type operator*() const {
      return m_first;
   }

   friend bool operator==(const nums_iterator& a, const nums_iterator& b) {
      return a.m_first == b.m_first;
   }

   friend bool operator!=(const nums_iterator& a, const nums_iterator& b) {
      return !(a == b);
   }

private:
   T       m_first;
   gen_ref m_gen;
};
}


// could be finite or infinite
template <typename T, typename Generator>
struct nums_range : public basic_range {
   typedef details::nums_iterator<T, Generator> iterator;
   typedef details::nums_iterator<T, Generator> const_iterator;
   typedef T value_type;

   explicit nums_range(T first, T last, Generator gen)
      : m_first(first)
      , m_last(last)
      , m_generator(gen) {}

   iterator begin() const {
      return iterator(m_first, m_generator);
   }

   iterator end() const {
      return iterator(m_last, m_generator);
   }

private:
   T         m_first;
   T         m_last;
   Generator m_generator;
};


namespace {

template <typename T, typename Generator>
auto make_nums_range(T first, T last, Generator g) {
   return nums_range<T, Generator>(first, last, g);
}

inline auto ints(int initial_value = 0, int last_value = std::numeric_limits<int>::max()) {
   return make_nums_range(initial_value, last_value, [](int x) { return ++x; });
}
}
}


#endif /* num_range_h */

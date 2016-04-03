//
//  repeat_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef repeat_range_h
#define repeat_range_h

#include <iterator>

#include <mrl/details/basic_range.hpp>

namespace mrl {

template <typename Value>
struct repeat_iterator : public std::iterator<std::input_iterator_tag, Value> {

   typedef Value value_type;

   explicit repeat_iterator(const value_type value, bool sentinel = false)
      : m_value(value)
      , m_sentinel(sentinel) {}

   repeat_iterator& operator++() {
      return *this;
   }

   repeat_iterator operator++(int) {
      return *this;
   }

   value_type operator*() const {
      return m_value;
   }

   friend bool operator==(const repeat_iterator& a, const repeat_iterator& b) {
      return a.m_sentinel == b.m_sentinel;
   }

   friend bool operator!=(const repeat_iterator& a, const repeat_iterator& b) {
      return !(a == b);
   }

private:
   value_type m_value;
   bool       m_sentinel;
};

template <typename Value>
struct repeat_range : public basic_range {

   typedef repeat_iterator<Value> iterator;
   typedef Value                  value_type;

   explicit repeat_range(value_type value)
      : m_value(value) {}

   iterator begin() const {
      return iterator(m_value);
   }

   iterator end() const {
      return iterator(m_value, true);
   }

private:
   value_type m_value;
};

template <typename value_type>
repeat_range<value_type> make_repeat_range(value_type value) {
   return repeat_range<value_type>(value);
}
}


#endif /* repeat_range_h */

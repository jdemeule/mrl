//
//  iterator_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef iterator_range_h
#define iterator_range_h


#include "basic_range.hpp"

namespace mrl {

template <typename ForwardIt>
struct iterator_range : public range<finite_range_tag> {
public:
   typedef ForwardIt                      const_iterator;
   typedef const_iterator                 iterator;
   typedef typename ForwardIt::value_type value_type;

   iterator_range(ForwardIt first, ForwardIt last)
      : m_first(first)
      , m_last(last) {}

   ForwardIt begin() const {
      return m_first;
   }

   ForwardIt end() const {
      return m_last;
   }

private:
   ForwardIt m_first;
   ForwardIt m_last;
};

template <typename ForwardIt>
iterator_range<ForwardIt> make_range(ForwardIt first, ForwardIt last) {
   return iterator_range<ForwardIt>(first, last);
}
}

#endif /* iterator_range_h */

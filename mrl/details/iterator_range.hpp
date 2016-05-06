//
//  iterator_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef iterator_range_h
#define iterator_range_h


#include <mrl/details/basic_range.hpp>

namespace mrl {

template <typename Iterator>
struct iterator_range : public range<finite_range_tag> {
public:
   typedef Iterator                      const_iterator;
   typedef const_iterator                iterator;
   typedef typename Iterator::value_type value_type;

   iterator_range(Iterator first, Iterator last)
      : m_first(first)
      , m_last(last) {}

   Iterator begin() const {
      return m_first;
   }

   Iterator end() const {
      return m_last;
   }

private:
   Iterator m_first;
   Iterator m_last;
};

template <typename Iterator>
auto make_iterator_range(Iterator first, Iterator last) {
   return iterator_range<Iterator>(first, last);
}
}

#endif /* iterator_range_h */

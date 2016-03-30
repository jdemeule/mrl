//
//  join_operator.hpp
//  mrl
//
//  Created by Jérémy Demeule on 29/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef join_operator_h
#define join_operator_h

#include "pipeable_operator.hpp"

namespace mrl_linq {

template <typename R>
struct join_operator : public pipeable_operator {
   explicit join_operator(const R& r)
      : m_range(r) {}

   template <typename Rg>
   auto operator()(const Rg& r) const {
      return make_join_range(r, m_range);
   }

   R m_range;
};

template <typename R>
auto join(const R& r) {
   return join_operator<R>(r);
}
}

#endif /* join_operator_h */

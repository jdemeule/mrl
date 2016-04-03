//
//  concat_operator.hpp
//  mrl
//
//  Created by Jérémy Demeule on 29/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef concat_operator_h
#define concat_operator_h

#include <mrl/details/concat_range.hpp>
#include <mrl/details/pipeable_operator.hpp>

namespace mrl_linq {

template <typename R>
struct concat_operator : public pipeable_operator {
   explicit concat_operator(const R& r)
      : m_range(r) {}

   template <typename Rg>
   auto operator()(const Rg& r) const {
      return make_concat_range(r, m_range);
   }

   R m_range;
};

template <typename R>
auto concat(const R& r) {
   return concat_operator<R>(r);
}
}

#endif /* concat_operator_h */

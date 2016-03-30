//
//  mbind_operator.hpp
//  mrl
//
//  Created by Jérémy Demeule on 30/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef mbind_operator_h
#define mbind_operator_h

#include "flatten_operator.hpp"
#include "pipeable_operator.hpp"
#include "transform_operator.hpp"

namespace mrl_linq {

template <typename F>
struct mbind_operator : public pipeable_operator {
   explicit mbind_operator(F op)
      : m_op(op){};
   template <typename Rg>
   auto operator()(const Rg& r) const {
      return make_flatten_range(make_transform_range(r, m_op));
   }

   F m_op;
};


// rename to flat_select or select_flat?
template <typename F>
auto mbind(F op) {
   return mbind_operator<F>(op);
}
}

#endif /* mbind_operator_h */

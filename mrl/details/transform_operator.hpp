//
//  transform_operator.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef transform_operator_h
#define transform_operator_h


#include <mrl/details/pipeable_operator.hpp>
#include <mrl/details/transform_range.hpp>

namespace mrl_linq {
template <typename F>
struct transform_operator : public pipeable_operator {
   explicit transform_operator(F op)
      : m_op(op){};
   F operator()() const {
      return m_op;
   }
   template <typename Rg>
   auto operator()(const Rg& r) const {
      return make_transform_range(r, m_op);
   }

   F m_op;
};

template <typename F>
transform_operator<F> select(F op) {
   return transform_operator<F>(op);
}
}

#endif /* transform_operator_h */

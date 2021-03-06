//
//  flatten_operator.hpp
//  mrl
//
//  Created by Jérémy Demeule on 30/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef flatten_operator_h
#define flatten_operator_h

#include <mrl/details/flatten_range.hpp>
#include <mrl/details/pipeable_operator.hpp>

namespace mrl_linq {

struct flatten_operator : public pipeable_operator {
   template <typename Rg>
   auto operator()(const Rg& r) const {
      return make_flatten_range(r);
   }
};

namespace {
// todo: rename it as flatmap
inline auto flatten() {
   return flatten_operator();
}
}
}


#endif /* flatten_operator_h */

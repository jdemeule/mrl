//
//  take_n_operator.h
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef take_n_operator_h
#define take_n_operator_h

#include "pipeable_operator.hpp"

namespace mrl_linq {
struct take_n_operator : public pipeable_operator {
   explicit take_n_operator(std::size_t count)
      : n(count) {}
   template <typename Rg>
   auto operator()(const Rg& r) const {
      return make_take_n_range(r, n);
   }
   std::size_t n;
};

take_n_operator take(std::size_t n) {
   return take_n_operator(n);
}
}

#endif /* take_n_operator_h */

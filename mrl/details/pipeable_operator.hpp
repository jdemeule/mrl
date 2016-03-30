//
//  pipeable_operator.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef pipeable_operator_h
#define pipeable_operator_h

#include <type_traits>
#include "range.hpp"

namespace mrl_linq {
using namespace ::mrl;

struct pipeable_operator {};

template <typename Rg,
          typename Op,
          typename std::enable_if<std::is_base_of<basic_range, Rg>::value>::type*       = nullptr,
          typename std::enable_if<std::is_base_of<pipeable_operator, Op>::value>::type* = nullptr>
auto operator|(const Rg& r, Op op) {
   return op(r);
}


template <typename Rg>
auto from(const Rg& rg) {
   return make_ref_range(rg);
}
}


#endif /* pipeable_operator_h */

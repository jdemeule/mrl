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

#include <mrl/range.hpp>

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


template <typename R>
auto from(const R& r) {
   return make_ref_range(r);
}

template <typename It>
auto from(It first, It last) {
   return make_iterator_range(first, last);
}
}


#endif /* pipeable_operator_h */

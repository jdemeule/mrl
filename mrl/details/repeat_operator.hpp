//
//  repeat_operator.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef repeat_operator_h
#define repeat_operator_h

#include <mrl/details/pipeable_operator.hpp>
#include <mrl/details/repeat_range.hpp>

namespace mrl_linq {
//
// struct repeat_operator : public pipeable_operator {
//
//   template <typename Rg>
//   auto operator()(const Rg& r) const {
//      return make_repeat_range(r);
//   }
//};


template <typename Value>
auto repeat(const Value& value) {
   return make_repeat_range(value);
}
}

#endif /* repeat_operator_h */

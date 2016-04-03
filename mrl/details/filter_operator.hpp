//
//  filter_operator.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef filter_operator_h
#define filter_operator_h

#include <mrl/details/filter_range.hpp>
#include <mrl/details/pipeable_operator.hpp>

namespace mrl_linq {
template <typename Predicate>
struct filter_predicate : public pipeable_operator {
   explicit filter_predicate(Predicate pred)
      : p(pred){};


   template <typename Rg>
   auto operator()(const Rg& r) const {
      return make_filter_range(r, p);
   }

   Predicate p;
};

template <typename Predicate>
filter_predicate<Predicate> where(Predicate p) {
   return filter_predicate<Predicate>(p);
}
}


#endif /* filter_operator_h */

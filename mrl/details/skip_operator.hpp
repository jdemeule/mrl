//
//  skip_operator.hpp
//  mrl
//
//  Created by Jérémy Demeule on 31/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef skip_operator_h
#define skip_operator_h

namespace mrl_linq {

struct skip_operator : public pipeable_operator {
   explicit skip_operator(std::size_t count)
      : n(count) {}
   template <typename Rg>
   auto operator()(const Rg& r) const {
      return make_skip_range(r, n);
   }
   std::size_t n;
};

skip_operator skip(std::size_t n) {
   return skip_operator(n);
}
}


#endif /* skip_operator_h */
//
//  zip_operator.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef zip_operator_h
#define zip_operator_h

#include <mrl/details/pipeable_operator.hpp>
#include <mrl/details/zip_range.hpp>

namespace mrl_linq {

template <typename R>
struct zip_operator : public pipeable_operator {
   explicit zip_operator(const R& r)
      : m_range(r) {}

   template <typename Rg>
   auto operator()(const Rg& r) const {
      return make_zip_range(r, m_range);
   }

   R m_range;
};

template <typename R>
auto zip(const R& r) {
   return zip_operator<R>(r);
}
}

#endif /* zip_operator_h */

//
//  linq.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef linq_h
#define linq_h

#include "filter_operator.hpp"
#include "pipeable_operator.hpp"
#include "repeat_operator.hpp"
#include "take_n_operator.hpp"
#include "transform_operator.hpp"
#include "zip_operator.hpp"

namespace mrl_linq {
// using namespace ::mrl;

// template <typename Rg, typename Predicate>
// struct where_builder {
//
// private:
//   Rg        m_range;
//   Predicate m_p;
//};
//
// template <typename Rg>
// struct from_builder {
//   template <typename Predicate>
//   where_builder<Rg, Predicate> where(Predicate p) {
//      return where_builder<Rg, Predicate>(m_range, p);
//   }
//
// private:
//   Rg m_range;
//};
//
// template <typename Rg>
// from_builder<Rg> from(Rg r) {
//   return from_builder<Rg>(r);
//}

//   void from(Rg) -> from_range_builder()
//


struct to_vector_operator : public pipeable_operator {
   template <typename Rg>
   auto operator()(const Rg& r) const {
      return to_vector(r);
   }
};


to_vector_operator to_vector() {
   return to_vector_operator();
}
}



#endif /* linq_h */

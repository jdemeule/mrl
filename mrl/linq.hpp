//
//  linq.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef linq_h
#define linq_h

#include "details/concat_operator.hpp"
#include "details/filter_operator.hpp"
#include "details/flatten_operator.hpp"
#include "details/join_operator.hpp"
#include "details/mbind_operator.hpp"
#include "details/pipeable_operator.hpp"
#include "details/repeat_operator.hpp"
#include "details/skip_operator.hpp"
#include "details/take_n_operator.hpp"
#include "details/transform_operator.hpp"
#include "details/zip_operator.hpp"

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

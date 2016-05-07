//
//  chunk_operator.hpp
//  mrl
//
//  Created by Jérémy Demeule on 29/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef chunk_operator_h
#define chunk_operator_h

#include <mrl/details/chunk_range.hpp>
#include <mrl/details/pipeable_operator.hpp>

namespace mrl_linq {


struct chunk_operator : public pipeable_operator {
   explicit chunk_operator(std::size_t n)
      : m_n(n) {}

   template <typename Rg>
   auto operator()(const Rg& r) const {
      return make_chunk_range(r, m_n);
   }

   std::size_t m_n;
};


namespace {
inline auto chunk(std::size_t n) {
   return chunk_operator(n);
}
}
}

#endif

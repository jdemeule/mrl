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

template <typename... Rs>
struct zip_operator : public pipeable_operator {

   typedef std::tuple<Rs...> ranges;

   explicit zip_operator(const Rs&... rs)
      : m_ranges(rs...) {}

   template <typename Rg>
   auto operator()(const Rg& r) const {
      //      return make_zip_range(r, m_ranges);
      return impl(r, details::tuple_indices_t<ranges>{});
   }

private:
   template <typename Rg, std::size_t... Is>
   auto impl(const Rg& r, std::index_sequence<Is...>) const {
      return make_zip_range(r, std::get<Is>(m_ranges)...);
   }

   ranges m_ranges;
};

namespace {
// could take more than 1 range
template <typename... Rs>
auto zip(const Rs&... r) {
   return zip_operator<Rs...>(r...);
}
}
}

#endif /* zip_operator_h */

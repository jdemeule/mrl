//
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef range_h
#define range_h

#include <mrl/details/basic_range.hpp>
#include <mrl/details/chunk_range.hpp>
#include <mrl/details/concat_range.hpp>
#include <mrl/details/filter_range.hpp>
#include <mrl/details/flatten_range.hpp>
#include <mrl/details/iterator_range.hpp>
#include <mrl/details/join_range.hpp>
#include <mrl/details/num_range.hpp>
#include <mrl/details/owner_range.hpp>
#include <mrl/details/ref_range.hpp>
#include <mrl/details/repeat_range.hpp>
#include <mrl/details/skip_range.hpp>
#include <mrl/details/take_n_range.hpp>
#include <mrl/details/transform_range.hpp>
#include <mrl/details/zip_range.hpp>

#include <list>
#include <map>
#include <vector>

namespace mrl {

template <typename Rg>
auto to_vector(const Rg& rg) {
   return std::vector<typename Rg::value_type>(rg.begin(), rg.end());
}

template <typename Rg>
auto to_list(const Rg& rg) {
   return std::list<typename Rg::value_type>(rg.begin(), rg.end());
}

// template <typename Rg, typename KeySelector, typename ValueSelector>
// std::map<typename KeySelector::value_type, typename ValueSelector::value_type> to_dictionary(
//   const Rg& rg, KeySelector keyselector, ValueSelector valueselector) {
//   std::map<typename KeySelector::value_type, typename ValueSelector::value_type> dict;
//   return dict;
//}
}



#endif /* range_h */

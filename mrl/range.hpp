//
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef range_h
#define range_h

#include "details/basic_range.hpp"
#include "details/concat_range.hpp"
#include "details/filter_range.hpp"
#include "details/flatten_range.hpp"
#include "details/iterator_range.hpp"
#include "details/join_range.hpp"
#include "details/num_range.hpp"
#include "details/owner_range.hpp"
#include "details/ref_range.hpp"
#include "details/repeat_range.hpp"
#include "details/skip_range.hpp"
#include "details/take_n_range.hpp"
#include "details/transform_range.hpp"
#include "details/zip_range.hpp"

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

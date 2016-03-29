//
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef range_h
#define range_h

#include "basic_range.hpp"
#include "concat_range.hpp"
#include "filter_range.hpp"
#include "iterator_range.hpp"
#include "num_range.hpp"
#include "owner_range.hpp"
#include "ref_range.hpp"
#include "repeat_range.hpp"
#include "take_n_range.hpp"
#include "transform_range.hpp"
#include "zip_range.hpp"

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

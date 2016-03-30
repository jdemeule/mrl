//
//  basic_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef basic_range_h
#define basic_range_h

namespace mrl {

struct basic_range {};

struct finite_range_tag {};
struct infinite_range_tag {};

//   struct range_category\

template <typename range_category>
struct range : public basic_range {
   typedef range_category category;
};
}

#endif /* basic_range_h */

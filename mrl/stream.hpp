//
//  stream.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef stream_h
#define stream_h

#include <mrl/range.hpp>

namespace mrl_stream {
using namespace ::mrl;

template <typename R>
struct select_builder {
   explicit select_builder(const R& range)
      : m_range(range) {}

   R to_range() const {
      return m_range;
   }

   auto to_vector() const {
      return to_vector(m_range);
   }

   R m_range;
};

template <typename R>
select_builder<R> make_select_builder(const R& range) {
   return select_builder<R>(range);
}

template <typename R>
struct where_builder {
   explicit where_builder(const R& range)
      : m_range(range) {}

   template <typename F>
   auto select(F selector) const {
      return make_select_builder(make_transform_range(m_range, selector));
   }

   R m_range;
};

template <typename R>
where_builder<R> make_where_builder(const R& range) {
   return where_builder<R>(range);
}

template <typename R>
struct from_builder {
   explicit from_builder(const R& range)
      : m_range(range) {}

   template <typename Predicate>
   auto where(Predicate p) const {
      return make_where_builder(make_filter_range(m_range, p));
   }

   R m_range;
};

template <typename R>
from_builder<R> make_from_builder(const R& range) {
   return from_builder<R>(range);
}

template <typename Rg>
auto from(const Rg& rg) {
   return make_from_builder(make_ref_range(rg));
}
}


#endif /* stream_h */

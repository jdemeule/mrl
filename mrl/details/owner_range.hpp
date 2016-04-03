//
//  owner_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef owner_range_h
#define owner_range_h

#include <mrl/details/basic_range.hpp>

namespace mrl {

template <typename Ctn>
struct owner_range : public range<finite_range_tag> {
public:
   typedef typename Ctn::const_iterator const_iterator;
   typedef const_iterator               iterator;
   typedef typename Ctn::value_type     value_type;

   explicit owner_range(Ctn&& ctn)
      : m_ctn(std::move(ctn)) {}

   iterator begin() const {
      return m_ctn.begin();
   }

   iterator end() const {
      return m_ctn.end();
   }

private:
   Ctn m_ctn;
};

template <typename R>
auto make_range(R&& r) {
   return owner_range<R>(std::move(r));
}
}


#endif /* owner_range_h */

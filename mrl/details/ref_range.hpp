//
//  ref_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef ref_range_h
#define ref_range_h

#include <mrl/details/basic_range.hpp>

namespace mrl {
template <typename Ctn>
struct ref_range : public range<finite_range_tag> {
public:
   typedef typename Ctn::const_iterator const_iterator;
   typedef const_iterator               iterator;
   typedef typename Ctn::value_type     value_type;

   explicit ref_range(const Ctn& ctn)
      : m_ctn(ctn) {}

   iterator begin() const {
      return m_ctn.begin();
   }

   iterator end() const {
      return m_ctn.end();
   }

private:
   const Ctn& m_ctn;
};



template <typename R>
auto make_ref_range(const R& r) {
   return ref_range<R>(r);
};
}

#endif /* ref_range_h */

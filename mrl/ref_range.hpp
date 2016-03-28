//
//  ref_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef ref_range_h
#define ref_range_h

#include "basic_range.hpp"

namespace mrl {
template <typename Ctn>
struct ref_range : public basic_range {
public:
   typedef typename Ctn::const_iterator iterator;
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



template <typename Rg>
ref_range<Rg> make_ref_range(const Rg& rg) {
   return ref_range<Rg>(rg);
};
}

#endif /* ref_range_h */

//
//  linq.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef linq_h
#define linq_h

#include "range.hpp"

namespace mrl_linq {
using namespace ::mrl;

// template <typename Rg, typename Predicate>
// struct where_builder {
//
// private:
//   Rg        m_range;
//   Predicate m_p;
//};
//
// template <typename Rg>
// struct from_builder {
//   template <typename Predicate>
//   where_builder<Rg, Predicate> where(Predicate p) {
//      return where_builder<Rg, Predicate>(m_range, p);
//   }
//
// private:
//   Rg m_range;
//};
//
// template <typename Rg>
// from_builder<Rg> from(Rg r) {
//   return from_builder<Rg>(r);
//}

//   void from(Rg) -> from_range_builder()
//

struct pipeable_operator {};

template <typename Predicate>
struct filter_predicate : public pipeable_operator {
   explicit filter_predicate(Predicate pred)
      : p(pred){};


   template <typename Rg>
   auto operator()(const Rg& r) const {
      return make_filter_range(r, p);
   }

   Predicate p;
};

template <typename Predicate>
filter_predicate<Predicate> where(Predicate p) {
   return filter_predicate<Predicate>(p);
}

template <typename F>
struct transform_operator : public pipeable_operator {
   explicit transform_operator(F op)
      : m_op(op){};
   F operator()() const {
      return m_op;
   }
   template <typename Rg>
   auto operator()(const Rg& r) const {
      return make_transform_range(r, m_op);
   }

   F m_op;
};

template <typename F>
transform_operator<F> select(F op) {
   return transform_operator<F>(op);
}


struct take_n_operator : public pipeable_operator {
   explicit take_n_operator(std::size_t count)
      : n(count) {}
   template <typename Rg>
   auto operator()(const Rg& r) const {
      return make_take_n_range(r, n);
   }
   std::size_t n;
};

take_n_operator take(std::size_t n) {
   return take_n_operator(n);
}


template <typename Rg,
          typename Op,
          typename std::enable_if<std::is_base_of<basic_range, Rg>::value>::type*       = nullptr,
          typename std::enable_if<std::is_base_of<pipeable_operator, Op>::value>::type* = nullptr>
auto operator|(const Rg& r, Op op) {
   return op(r);
}


template <typename Rg>
auto from(const Rg& rg) {
   return make_ref_range(rg);
}
}



#endif /* linq_h */

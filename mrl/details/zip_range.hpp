//
//  zip_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef zip_range_h
#define zip_range_h


#include <iterator>

#include <mrl/details/basic_range.hpp>

namespace mrl {


namespace details {



template <typename Tup>
using tuple_indices_t = std::make_index_sequence<std::tuple_size<typename std::remove_reference<Tup>::type>::value>;


struct tuple_transform_fn {
private:
   template <typename Tup, typename Fun, std::size_t... Is>
   static auto impl1(Tup&& tup, Fun fun, std::index_sequence<Is...>) {
      return std::tuple<decltype(fun(std::get<Is>(std::forward<Tup>(tup))))...>{
         fun(std::get<Is>(std::forward<Tup>(tup)))...};
   }

   template <typename Tup, typename Fun, std::size_t... Is>
   static auto impl2(Tup&& tup0, Tup&& tup1, Fun fun, std::index_sequence<Is...>) {
      return std::tuple<decltype(fun(std::get<Is>(std::forward<Tup>(tup0)), std::get<Is>(std::forward<Tup>(tup1))))...>{
         fun(std::get<Is>(std::forward<Tup>(tup0)), std::get<Is>(std::forward<Tup>(tup1)))...};
   }

public:
   template <typename Tup, typename Fun>
   auto operator()(Tup&& tup, Fun fun) const {
      return tuple_transform_fn::impl1(std::forward<Tup>(tup), std::move(fun), tuple_indices_t<Tup>{});
   }

   template <typename Tup, typename Fun>
   auto operator()(Tup&& tup0, Tup&& tup1, Fun fun) const {
      return tuple_transform_fn::impl2(
         std::forward<Tup>(tup0), std::forward<Tup>(tup1), std::move(fun), tuple_indices_t<Tup>{});
   }
};

constexpr auto tuple_transform = tuple_transform_fn{};

struct tuple_for_each_fn {
private:
   template <typename Tup, typename Fun, std::size_t... Is>
   static void impl1(Tup&& tup, Fun fun, std::index_sequence<Is...>) {
      (void)std::initializer_list<int>{((void)fun(std::get<Is>(std::forward<Tup>(tup))), 42)...};
   }

public:
   template <typename Tup, typename Fun>
   auto operator()(Tup&& tup, Fun fun) const {
      tuple_for_each_fn::impl1(std::forward<Tup>(tup), std::move(fun), tuple_indices_t<Tup>{});
      return fun;
   }
};

constexpr auto tuple_for_each = tuple_for_each_fn{};

struct tuple_any_of_t {
private:
   template <typename Tup, typename Fun, std::size_t... Is>
   static bool impl(Tup&& tup, Fun fun, std::index_sequence<Is...>) {
      return (... || fun(std::get<Is>(std::forward<Tup>(tup))));
   }

public:
   template <typename Tup, typename Fun>
   bool operator()(Tup&& tup, Fun fun) const {
      return tuple_any_of_t::impl(tup, fun, tuple_indices_t<Tup>{});
   }
};
constexpr auto tuple_any_of = tuple_any_of_t{};

struct tuple_all_of_t {
private:
   template <typename Tup, typename Fun, std::size_t... Is>
   static bool impl(Tup&& tup, Fun fun, std::index_sequence<Is...>) {
      return (... && fun(std::get<Is>(std::forward<Tup>(tup))));
   }

public:
   template <typename Tup, typename Fun>
   bool operator()(Tup&& tup, Fun fun) const {
      return tuple_all_of_t::impl(tup, fun, tuple_indices_t<Tup>{});
   }
};
constexpr auto tuple_all_of = tuple_all_of_t{};


struct cursor_advance_t {
   template <typename Cursor>
   void operator()(Cursor& c) const {
      c.next();
   }
};
constexpr auto cursor_advance = cursor_advance_t{};

struct cursor_value_t {
   template <typename Cursor>
   auto operator()(Cursor& c) const {
      return c.value();
   }
};
constexpr auto cursor_value = cursor_value_t{};

struct cursor_done_t {
   template <typename Cursor>
   bool operator()(const Cursor& c) const {
      return c.done();
   }
};
constexpr auto cursor_done = cursor_done_t{};

struct cursor_eq_t {
   template <typename Cursor>
   bool operator()(const Cursor& c0, const Cursor& c1) const {
      return c0 == c1;
   }
};
constexpr auto cursor_eq = cursor_eq_t{};

template <typename R>
auto make_cursor_2(R&& r) {
   return make_cursor(std::begin(r), std::end(r));
}

template <typename... Cursors>
struct zip_iterator : public std::iterator<std::input_iterator_tag, std::tuple<typename Cursors::value_type...> > {

   typedef std::tuple<typename Cursors::value_type...> value_type;

   zip_iterator(Cursors&&... cursors)
      : m_cursors(cursors...)
      , m_sentinel(false) {}

   static zip_iterator sentinel() {
      return zip_iterator(true);
   }

   zip_iterator& operator++() {
      tuple_for_each(m_cursors, cursor_advance);
      return *this;
   }

   zip_iterator operator++(int) {
      auto current(*this);
      tuple_for_each(m_cursors, cursor_advance);
      return current;
   }

   value_type operator*() const {
      return tuple_transform(m_cursors, cursor_value);
   }

   friend bool operator==(const zip_iterator& a, const zip_iterator& b) {
      if (a.m_sentinel)
         return tuple_any_of(b.m_cursors, cursor_done);
      if (b.m_sentinel)
         return tuple_any_of(a.m_cursors, cursor_done);

      return tuple_all_of(tuple_transform(a.m_cursors, b.m_cursors, cursor_eq), [](bool b) { return b; });
   }

   friend bool operator!=(const zip_iterator& a, const zip_iterator& b) {
      return !(a == b);
   }

private:
   explicit zip_iterator(bool sentinel)
      : m_sentinel(true) {}


private:
   std::tuple<Cursors...> m_cursors;
   bool                   m_sentinel;
};
}


template <typename... Rngs>
struct zip_range : public basic_range {

   typedef std::tuple<Rngs...>                                                     ranges;
   typedef details::zip_iterator<cursor<typename std::decay_t<Rngs>::iterator>...> const_iterator;
   typedef const_iterator                                                          iterator;
   typedef std::tuple<typename std::decay_t<Rngs>::value_type...>                  value_type;

   zip_range(const Rngs&... rngs)
      : m_ranges(rngs...) {}

   iterator begin() const {
      constexpr auto Size = std::tuple_size<std::decay_t<ranges> >::value;
      return make_zip_iterator(m_ranges, std::make_index_sequence<Size>{});
   }

   template <typename Tup, std::size_t... Is>
   iterator make_zip_iterator(const Tup& tup, std::index_sequence<Is...>) const {
      return iterator(details::make_cursor_2(std::get<Is>(tup))...);
   }

   iterator end() const {
      return iterator::sentinel();
   }

private:
   ranges m_ranges;
};

// Rngs must respect is_range concept
// (inherits from base_range)
template <typename... Rngs>
auto make_zip_range(const Rngs&... rngs) {
   return zip_range<Rngs...>(rngs...);
}
}

#endif /* zip_range_h */

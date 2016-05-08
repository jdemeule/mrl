//
//  main.cpp
//  mrl
//
//  Created by Jérémy Demeule on 20/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <type_traits>
#include <vector>

#include <mrl/linq.hpp>
#include <mrl/range.hpp>
#include <mrl/stream.hpp>

#include <gtest/gtest.h>

template <typename R>
void print_all(const R& r) {
   for (auto x : r)
      std::cout << x << ", ";
   std::cout << std::endl;
}

TEST(range, filter) {
   using namespace mrl;

   std::vector<int> expected{0, 2, 4, 6, 8};

   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   make_filter_range(vs.begin(), vs.end(), [](auto x) { return true; });

   auto evens = make_filter_range(make_ref_range(vs), [](int x) { return x % 2 == 0; });
   ASSERT_EQ(expected.size(), std::distance(evens.begin(), evens.end()));
   ASSERT_EQ(expected, to_vector(evens));
}

TEST(range, transform) {
   using namespace mrl;

   std::vector<int> expected{0, 4, 16, 36, 64};

   std::vector<int> vs{0, 2, 4, 6, 8};

   auto even_squares = make_transform_range(make_ref_range(vs), [](int x) { return x * x; });

   ASSERT_EQ(expected.size(), std::distance(even_squares.begin(), even_squares.end()));
   ASSERT_EQ(expected, to_vector(even_squares));
}

TEST(range, filter_linq) {
   using namespace mrl_linq;

   std::vector<int> expected{0, 2, 4, 6, 8};

   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   auto evens = from(vs) | where([](int x) { return x % 2 == 0; });
   ASSERT_EQ(expected.size(), std::distance(evens.begin(), evens.end()));
   ASSERT_EQ(expected, evens | to_vector());
}

TEST(range, transform_linq) {
   using namespace mrl_linq;

   std::vector<int> expected{0, 4, 16, 36, 64};

   std::vector<int> vs{0, 2, 4, 6, 8};

   auto even_squares = from(vs) | select([](int x) { return x * x; });

   ASSERT_EQ(expected.size(), std::distance(even_squares.begin(), even_squares.end()));
   ASSERT_EQ(expected, even_squares | to_vector());
}

std::vector<int> make_vs() {
   return std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
}

TEST(range, api_ctn_liveness) {
   using namespace mrl;

   std::vector<int> expected{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   auto r = make_range(make_vs());

   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, api_ints_take) {
   using namespace mrl;

   std::vector<int> expected{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

   auto values = make_take_n_range(ints(), 15);

   ASSERT_EQ(15, std::distance(values.begin(), values.end()));
   ASSERT_EQ(expected, to_vector(values));
}

TEST(range, linq_api_ints_take) {
   using namespace mrl_linq;

   std::vector<int> expected{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

   auto values = from(ints()) | take(15);


   ASSERT_EQ(15, std::distance(values.begin(), values.end()));
   ASSERT_EQ(expected, values | to_vector());
}

void range_linq_pythagorean_triples() {
   using namespace mrl_linq;
   // clang-format off
//   auto triples =
//     from(ints(1))
//   | select([](int z) {
//      auto xs =
//        from(ints(1, z))
//      | select([=](int x) {
//         auto ys =
//           from(ints(1, x))
//         | where([=](int y) { return x * x + y * y == z * z; })
//         | select([=](int y) { return std::make_tuple(x, y, z); });
//      });
//   });
   // auto triples =
   //   from(ints(1))
   // | from(ints(1
   // clang-format on
   //   for (auto x : triples)
   //      std::cout << x << " ";

   //   auto triples = view::for_each(view::ints(1), [](int z) {
   //      return view::for_each(view::ints(1, z + 1), [=](int x) {
   //         return view::for_each(view::ints(x, z + 1),
   //                               [=](int y) { return yield_if(x * x + y * y ==
   //                               z * z, std::make_tuple(x, y, z)); });
   //      });
   //   });

   //   auto zzzz = make_concat_range(ints(1, 4),)

   //   auto triple2 = mrl::make_transform_range(ints(1), [](int z) {
   //      return mrl::make_transform_range(ints(1, z + 1), [=](int x) {
   //         return mrl::make_transform_range(ints(x, z + 1), [=](int y) {
   //            if (x * x + y * y == z * z)
   //               std::cout << "Found" << std::endl;
   //         });
   //      });
   //   });
   //
   //   auto triple = triple2.begin();
   //   for (int n = 0; n < 10; ++n, ++triple)
   //      *triple;

   //   auto triple3 = from(ints(1)) | select([](int z) {
   //                     return from(ints(1, z + 1)) | select([=](int x) {
   //                               return from(ints(x, z + 1)) | where([=](int
   //                               y) { return x * x + y * y == z * z; }) |
   //                                      select([=](int y) { return
   //                                      std::make_tuple(x, y, z); });
   //                            });
   //                  });

   //   for (int z : ints(1, 5)) {
   //      for (int y : ints(1, z + 1)) {
   //         for (int x : ints(1, y + 1)) {
   //            std::cout << x << y << z << std::endl;
   //         }
   //      }
   //   }
   std::vector<std::tuple<int, int, int> > tx;

   int found = 0;
   for (int z = 1;; ++z) {
      for (int x = 1; x <= z; ++x) {
         for (int y = x; y <= z; ++y) {
            if (x * x + y * y == z * z) {
               tx.push_back(std::make_tuple(x, y, z));
               ++found;
               if (found == 10)
                  goto fdone;
            }
         }
      }
   }
fdone:

   tx.clear();
   for (int z : ints(1, 6)) {
      for (int x : ints(1, z + 1)) {
         for (int y : from(ints(x, z + 1)) | where([=](auto y) {
                         bool accept = x * x + y * y == z * z;
                         std::cout << x << y << z << " " << accept << std::endl;

                         return accept;
                      })) {
            // x, y, z;
            tx.emplace_back(std::make_tuple(x, y, z));
            if (tx.size() == 10)
               goto done;
         }
      }
   }
done:

   std::cout << "range_linq_pythagorean_triples" << std::endl;
   for (auto triple : tx) {
      std::cout << "{ " << std::get<0>(triple) << ", " << std::get<1>(triple) << ", " << std::get<2>(triple) << " }"
                << std::endl;
   }

   auto xys = from(ints(1)) | select([](auto y) { return ints(1, y); }) | take(10);
   for (auto xy : xys) {
      for (auto x : xy)
         std::cout << x << " ";
      std::cout << std::endl;
   }
   std::cout << std::endl;
}

TEST(range, stream_api) {
   using namespace mrl_stream;

   std::vector<int> expected{0, 4, 16, 36, 64};

   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
   // clang-format off
   auto r = from(vs)
      .where([](int x) { return x % 2 == 0; })
      .select([](int x) { return x * x; } )
      .to_range();
   // clang-format on

   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, filter_non_1st) {
   using namespace mrl;

   std::vector<int> expected{3};
   std::vector<int> vs{1, 2, 3};

   auto r = make_filter_range(make_ref_range(vs), [](int x) { return x > 2; });
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, filter_1st) {
   using namespace mrl;

   std::vector<int> expected{1};
   std::vector<int> vs{1, 2, 3};

   auto r = make_filter_range(make_ref_range(vs), [](int x) { return x < 2; });
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, repeat_value) {
   using namespace mrl;

   std::vector<int> expected(10, 42);

   auto r = make_take_n_range(make_repeat_range(42), 10);
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, repeat_value_linq) {
   using namespace mrl_linq;

   std::vector<int> expected(10, 42);

   auto r = repeat(42) | take(10);
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, r | to_vector());
}

TEST(range, zip_api) {
   using namespace mrl;

   std::vector<int> v1 = {0, 1, 2, 3};
   std::vector<int> v2 = {4, 5, 6, 7};

   auto r = make_zip_range(make_ref_range(v1), make_ref_range(v2));

   std::vector<std::tuple<int, int> > expected{{0, 4}, {1, 5}, {2, 6}, {3, 7}};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, zip_api_2) {
   // not supported for now.
   using namespace mrl;

   std::vector<int> v1 = {0, 1, 2};
   std::vector<int> v2 = {4, 5, 6, 7};

   auto r = make_zip_range(make_ref_range(v1), make_ref_range(v2));

   std::vector<std::tuple<int, int> > expected{{0, 4}, {1, 5}, {2, 6}};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, zip_api_3) {
   using namespace mrl;

   std::vector<int> v1 = {0, 1, 2};

   auto r = make_zip_range(make_ref_range(v1), make_ref_range(v1), make_ref_range(v1));

   std::vector<std::tuple<int, int, int> > expected{{0, 0, 0}, {1, 1, 1}, {2, 2, 2}};
   ASSERT_EQ(expected.size(), std::distance(std::begin(r), std::end(r)));
   ASSERT_EQ(expected, to_vector(r));
   ASSERT_EQ(r.begin(), r.begin());

   // this should not compile
   //   auto r2 = make_zip_range_2(v1, v1, v1);
}


namespace bar {
struct as_function_fn {
private:
   template <typename R, typename... Args>
   struct ptr_fn_ {
   private:
      R (*pfn_)(Args...);

   public:
      ptr_fn_() = default;
      constexpr explicit ptr_fn_(R (*pfn)(Args...))
         : pfn_(pfn) {}
      R operator()(Args... args) const {
         return (*pfn_)(std::forward<Args>(args)...);
      }
   };

public:
   template <typename R, typename... Args>
   constexpr ptr_fn_<R, Args...> operator()(R (*p)(Args...)) const {
      return ptr_fn_<R, Args...>(p);
   }
   template <typename R, typename T>
   auto operator()(R T::*p) const -> decltype(std::mem_fn(p)) {
      return std::mem_fn(p);
   }
   //      template<typename T, typename U = detail::decay_t<T>>
   //      constexpr auto operator()(T && t) const ->
   //      meta::if_c<!std::is_pointer<U>::value && !std::is_member_pointer<U>::value, T>
   //      {
   //         return detail::forward<T>(t);
   //      }
};
}

TEST(range, zip_on_transform_api) {
   using namespace mrl;

   std::vector<int> v1 = {0, 1, 2, 3};

   auto r = make_zip_range(make_ref_range(v1), make_transform_range(make_ref_range(v1), [](int x) { return x * x; }));

   std::vector<std::tuple<int, int> > expected{{0, 0}, {1, 1}, {2, 4}, {3, 9}};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, zip_linq) {
   using namespace mrl_linq;

   std::vector<int> v1 = {0, 1, 2, 3};
   std::vector<int> v2 = {4, 5, 6, 7};

   auto r = from(v1) | zip(from(v2));

   std::vector<std::tuple<int, int> > expected{{0, 4}, {1, 5}, {2, 6}, {3, 7}};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, r | to_vector());
}

TEST(range, zip_linq_2) {
   using namespace mrl_linq;

   std::vector<int> v1 = {0, 1, 2};
   std::vector<int> v2 = {4, 5, 6, 7};

   auto r = from(v1) | zip(from(v2));

   std::vector<std::tuple<int, int> > expected{{0, 4}, {1, 5}, {2, 6}};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, r | to_vector());
}

TEST(range, zip_linq_3) {
   using namespace mrl_linq;

   std::vector<int> v1 = {0, 1, 2};

   auto r = from(v1) | zip(from(v1), from(v1));

   std::vector<std::tuple<int, int, int> > expected{{0, 0, 0}, {1, 1, 1}, {2, 2, 2}};
   ASSERT_EQ(expected.size(), std::distance(std::begin(r), std::end(r)));
   ASSERT_EQ(expected, r | to_vector());
   ASSERT_EQ(r.begin(), r.begin());

   // this should not compile
   //   auto r2 = make_zip_range_2(v1, v1, v1);
}

TEST(range, zip_on_transform_linq) {
   using namespace mrl_linq;

   std::vector<int> v1 = {0, 1, 2, 3};

   auto r = from(v1) | zip(from(v1) | select([](int x) { return x * x; }));

   std::vector<std::tuple<int, int> > expected{{0, 0}, {1, 1}, {2, 4}, {3, 9}};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, r | to_vector());
}

TEST(range, zip_with) {
   using namespace mrl;

   std::vector<std::string> v0{"a", "b", "c"};
   std::vector<std::string> v1{"x", "y", "z"};

   auto r = make_transform_range(make_zip_range(make_ref_range(v0), make_ref_range(v1)),
                                 [](auto p) { return std::get<0>(p) + std::get<1>(p); });

   std::vector<std::string> expected{"ax", "by", "cz"};
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, zip_with_linq) {
   using namespace mrl_linq;

   std::vector<std::string> v0{"a", "b", "c"};
   std::vector<std::string> v1{"x", "y", "z"};

   auto r = from(v0) | zip(from(v1)) | select([](auto p) { return std::get<0>(p) + std::get<1>(p); });

   std::vector<std::string> expected{"ax", "by", "cz"};
   ASSERT_EQ(expected, r | to_vector());
}

TEST(range, concat_api) {
   using namespace mrl;

   std::vector<int> v1 = {0, 1, 2, 3};
   std::list<int>   v2 = {4, 5, 6, 7};

   auto r = make_concat_range(make_ref_range(v1), make_ref_range(v2));

   std::vector<int> expected{0, 1, 2, 3, 4, 5, 6, 7};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, concat_linq) {
   using namespace mrl_linq;

   std::vector<int> v1 = {0, 1, 2, 3};
   std::list<int>   v2 = {4, 5, 6, 7};

   auto r = from(v1) | concat(from(v2));

   std::vector<int> expected{0, 1, 2, 3, 4, 5, 6, 7};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, r | to_vector());
}

TEST(range, join_api) {
   using namespace mrl;

   std::vector<int> v1 = {0, 1, 2, 3};
   std::list<int>   v2 = {4, 5, 6, 7};

   auto r = make_join_range(make_ref_range(v1), make_ref_range(v2));

   std::vector<std::tuple<int, int> > expected{{0, 4},
                                               {0, 5},
                                               {0, 6},
                                               {0, 7},
                                               {1, 4},
                                               {1, 5},
                                               {1, 6},
                                               {1, 7},
                                               {2, 4},
                                               {2, 5},
                                               {2, 6},
                                               {2, 7},
                                               {3, 4},
                                               {3, 5},
                                               {3, 6},
                                               {3, 7}};

   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}



TEST(range, join_linq_api) {
   using namespace mrl_linq;

   std::vector<int> v1 = {0, 1, 2, 3};
   std::list<int>   v2 = {4, 5, 6, 7};

   auto r = from(v1) | join(from(v2));

   std::vector<std::tuple<int, int> > expected{{0, 4},
                                               {0, 5},
                                               {0, 6},
                                               {0, 7},
                                               {1, 4},
                                               {1, 5},
                                               {1, 6},
                                               {1, 7},
                                               {2, 4},
                                               {2, 5},
                                               {2, 6},
                                               {2, 7},
                                               {3, 4},
                                               {3, 5},
                                               {3, 6},
                                               {3, 7}};

   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, r | to_vector());
}

TEST(range, flatten_api) {
   using namespace mrl;

   std::vector<std::vector<int> > vvs = {{1}, {1, 2}, {1, 2, 3}};

   auto r = make_flatten_range(make_ref_range(vvs));

   std::vector<int> expected{1, 1, 2, 1, 2, 3};

   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, flatten_linq_api) {
   using namespace mrl_linq;

   std::vector<std::vector<int> > vvs = {{1}, {1, 2}, {1, 2, 3}};

   auto r = from(vvs) | flatten();

   std::vector<int> expected{1, 1, 2, 1, 2, 3};

   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, r | to_vector());
}

void flatten_api_2() {
   using namespace mrl;

   std::cout << "flatten_api_2" << std::endl;

   auto ps = mrl::make_transform_range(ints(1), [](int z) { return ints(1, z + 1); });

   auto x = make_take_n_range(make_flatten_range(ps), 6);
   print_all(x);
}

TEST(range, flatten_on_generator) {
   using namespace mrl;

   std::vector<std::vector<int> > vvs = {{1}, {1, 2}, {1, 2, 3}};

   auto ps = make_transform_range(ints(1), [](int z) { return ints(1, z + 1); });
   auto r  = make_take_n_range(make_flatten_range(ps), 6);

   std::vector<int> expected{1, 1, 2, 1, 2, 3};

   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, flatten_on_generator_linq) {
   using namespace mrl_linq;

   std::vector<std::vector<int> > vvs = {{1}, {1, 2}, {1, 2, 3}};

   // clang-format off
   auto r = from(ints(1))
      | select([](int z) { return ints(1, z + 1); })
      | flatten()
      | take(6);
   // clang-format on

   std::vector<int> expected{1, 1, 2, 1, 2, 3};

   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, r | to_vector());
}


TEST(range, filter_1st_on_flatten) {
   using namespace mrl;

   std::vector<std::vector<int> > vvs = {{1}, {1, 2}, {1, 2, 3}};

   auto r = make_filter_range(make_flatten_range(make_ref_range(vvs)), [](int x) { return x > 2; });

   std::vector<int> expected{3};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, filter_non_1st_on_flatten) {
   using namespace mrl;

   std::vector<std::vector<int> > vvs = {{1}, {1, 2}, {1, 2, 3}};

   auto r = make_filter_range(make_flatten_range(make_ref_range(vvs)), [](int x) { return x < 2; });

   std::vector<int> expected{1, 1, 1};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}


TEST(range, filter_1st_on_flatten_linq) {
   using namespace mrl_linq;

   std::vector<std::vector<int> > vvs = {{1}, {1, 2}, {1, 2, 3}};

   auto r = from(vvs) | flatten() | where([](int x) { return x > 2; });

   std::vector<int> expected{3};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, r | to_vector());
}

TEST(range, filter_non_1st_on_flatten_linq) {
   using namespace mrl_linq;

   std::vector<std::vector<int> > vvs = {{1}, {1, 2}, {1, 2, 3}};

   auto r = from(vvs) | flatten() | where([](int x) { return x < 2; });

   std::vector<int> expected{1, 1, 1};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, r | to_vector());
}


TEST(range, filter_on_empty_on_flatten_1) {
   using namespace mrl;

   std::vector<std::vector<int> > vvs = {{}, {1, 2}, {}, {1, 2, 3}};

   auto r = make_filter_range(make_flatten_range(make_ref_range(vvs)), [](int x) { return x > 2; });

   std::vector<int> expected{3};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, filter_on_empty_on_flatten_2) {
   using namespace mrl;

   std::vector<std::vector<int> > vvs = {{}, {1, 2}, {}, {1, 2, 3}};

   auto r = make_filter_range(make_flatten_range(make_ref_range(vvs)), [](int x) { return x < 2; });

   std::vector<int> expected{1, 1};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, filter_on_empty_on_flatten_linq_1) {
   using namespace mrl_linq;

   std::vector<std::vector<int> > vvs = {{}, {1, 2}, {}, {1, 2, 3}};

   auto r = from(vvs) | flatten() | where([](int x) { return x > 2; });

   std::vector<int> expected{3};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, r | to_vector());
}

TEST(range, filter_on_empty_on_flatten_linq_2) {
   using namespace mrl_linq;

   std::vector<std::vector<int> > vvs = {{}, {1, 2}, {}, {1, 2, 3}};

   auto r = from(vvs) | flatten() | where([](int x) { return x < 2; });

   std::vector<int> expected{1, 1};
   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, r | to_vector());
}

TEST(range, pythagoreans_2) {
   using namespace mrl;

   // clang-format off
   auto zs = make_filter_range(make_flatten_range(make_transform_range(ints(1, 6), [](int z) {
      auto zxs = make_transform_range(ints(1, z + 1), [=](int x) {
         auto zyxs = make_transform_range(ints(x, z + 1), [=](int y) {
            return std::make_tuple(x, y, z);
         });
         return zyxs;
      });
      return make_flatten_range(zxs);
   })), [](auto xyz) {
      auto x = std::get<0>(xyz);
      auto y = std::get<1>(xyz);
      auto z = std::get<2>(xyz);
      return x * x + y * y == z * z;
   });
   // clang-format on

   std::vector<std::tuple<int, int, int> > expected{{3, 4, 5}};

   ASSERT_EQ(expected.size(), std::distance(zs.begin(), zs.end()));
   ASSERT_EQ(expected, to_vector(zs));
}

TEST(range, pythagoreans_3) {
   using namespace mrl;

   // clang-format off
   auto triples = make_flatten_range(make_transform_range(ints(1, 6), [](int z) {
      auto zxs = make_transform_range(ints(1, z + 1), [=](int x) {
         auto zyxs = make_transform_range(ints(x, z + 1), [=](int y) {
            return std::make_tuple(x, y, z);
         });
         return make_filter_range(zyxs, [](auto xyz) {
            auto x = std::get<0>(xyz);
            auto y = std::get<1>(xyz);
            auto z = std::get<2>(xyz);
            return x * x + y * y == z * z;
         });
      });
      return make_flatten_range(zxs);
   }));
   // clang-format on

   std::vector<std::tuple<int, int, int> > expected{{3, 4, 5}};

   ASSERT_EQ(expected.size(), std::distance(triples.begin(), triples.end()));
   ASSERT_EQ(expected, to_vector(triples));
}

TEST(range, pythagoreans_linq) {
   using namespace mrl_linq;

   // clang-format off
   auto triples = from(ints(1))
      | select([](int z) {
         return from(ints(1, z + 1))
            | select([=](int x) {
               return from(ints(x, z + 1))
                  | select([=](int y) { return std::make_tuple(x, y, z); })
                  | where([](auto xyz) {
                       auto x = std::get<0>(xyz);
                       auto y = std::get<1>(xyz);
                       auto z = std::get<2>(xyz);
                       return x * x + y * y == z * z;
                    });
              })
            | flatten();
        })
      | flatten() | take(1);
   // clang-format on

   std::vector<std::tuple<int, int, int> > expected{{3, 4, 5}};

   ASSERT_EQ(expected.size(), std::distance(triples.begin(), triples.end()));
   ASSERT_EQ(expected, triples | to_vector());
}

TEST(range, pythagoreans_linq_2) {
   using namespace mrl_linq;

   // clang-format off
   auto triples = from(ints(1))
   | mbind([](int z) {
      return from(ints(1, z + 1))
      | mbind([=](int x) {
         return from(ints(x, z + 1))
         | select([=](int y) { return std::make_tuple(x, y, z); } )
         | where([](auto xyz) {
            auto x = std::get<0>(xyz);
            auto y = std::get<1>(xyz);
            auto z = std::get<2>(xyz);
            return x * x + y * y == z * z;
         } );
      });
   }) | take(1);
   // clang-format on

   std::vector<std::tuple<int, int, int> > expected{{3, 4, 5}};

   ASSERT_EQ(expected.size(), std::distance(triples.begin(), triples.end()));
   ASSERT_EQ(expected, triples | to_vector());
}

TEST(range, skip_api) {
   using namespace mrl;

   auto r = make_skip_range(ints(0, 10), 2);

   std::vector<int> expected{2, 3, 4, 5, 6, 7, 8, 9};

   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, to_vector(r));
}

TEST(range, skip_linq_api) {
   using namespace mrl_linq;

   auto r = from(ints(0, 10)) | skip(2);

   std::vector<int> expected{2, 3, 4, 5, 6, 7, 8, 9};

   ASSERT_EQ(expected.size(), std::distance(r.begin(), r.end()));
   ASSERT_EQ(expected, r | to_vector());
}

template <typename It, typename Cat = mrl::range_iterator_category_t<It> >
void foo_bar(It x) {}

TEST(range, on_stream) {
   using namespace mrl;

   std::istringstream str("0.1 0.2 0.3 0.4");

   auto r        = make_iterator_range(std::istream_iterator<double>(str), std::istream_iterator<double>());
   auto filtered = make_filter_range(r, [](auto v) { return v > 0.2; });
   auto vs       = to_vector(filtered);

   EXPECT_EQ(2, vs.size());
}

TEST(range, on_stream_linq) {
   using namespace mrl_linq;

   std::istringstream str("0.1 0.2 0.3 0.4");

   auto vs = from(std::istream_iterator<double>(str), std::istream_iterator<double>()) |
             where([](auto v) { return v > 0.2; }) | to_vector();

   EXPECT_EQ(2, vs.size());
}

TEST(range, chunk) {
   using namespace mrl;

   auto r = make_chunk_range(ints(0, 10), 2);

   std::vector<std::vector<int> > expected{{0, 1}, {2, 3}, {4, 5}, {6, 7}, {8, 9}};
   EXPECT_EQ(expected.size(), std::distance(r.begin(), r.end()));

   auto fl = make_flatten_range(r);

   std::vector<int> expected_flat{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
   EXPECT_EQ(expected_flat.size(), std::distance(fl.begin(), fl.end()));
   EXPECT_EQ(expected_flat, to_vector(fl));
}

TEST(range, chunk_linq) {
   using namespace mrl_linq;

   auto r = from(ints(0, 10)) | chunk(2);

   std::vector<std::vector<int> > expected{{0, 1}, {2, 3}, {4, 5}, {6, 7}, {8, 9}};
   EXPECT_EQ(expected.size(), std::distance(r.begin(), r.end()));

   auto fl = r | flatten();

   std::vector<int> expected_flat{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
   EXPECT_EQ(expected_flat.size(), std::distance(fl.begin(), fl.end()));
   EXPECT_EQ(expected_flat, fl | to_vector());
}



template <typename InputIterator>
struct count_cursor {
   typedef typename InputIterator::value_type value_type;

   count_cursor(InputIterator first, std::size_t count)
      : m_first(first)
      , m_count(count) {}

   bool done() const {
      return m_count > 0;
   }

   void next() {
      ++m_first;
      --m_count;
   }

   value_type value() {
      return *m_first;
   }

   InputIterator m_first;
   std::size_t   m_count;
};

// int main(int argc, const char* argv[]) {
//
//
//   range_api();
//   range_linq_api();
//   //   range_api_ctn_liveness();
//   //   range_api_ints_take();
//   //   range_linq_api_ints_take();
//   //   range_stream_api();
//   filter_api();
//   repeat_api();
//   repeat_linq_api();
//   zip_api();
//   zip_linq_api();
//   concat_api();
//   concat_linq_api();
//   join_api();
//   join_linq_api();
//   range_linq_pythagorean_triples();
//
//
//   flatten_api();
//   flatten_linq_api();
//   flatten_api_2();
//   flatten_linq_api_2();
//   flatten_api_3();
//   flatten_linq_api_3();
//   flatten_api_4();
//   flatten_linq_api_4();
//
//   pythagoreans_2();
//   pythagoreans_3();
//   pythagoreans_linq();
//   pythagoreans_linq_2();
//
//   skip_api();
//   skip_linq_api();
//
//
//   //   mrl_linq::from(vs).where([](int x) -> bool { return x % 2 == 0; });
//
//   return 0;
//}

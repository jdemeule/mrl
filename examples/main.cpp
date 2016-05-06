//
//  main.cpp
//  mrl
//
//  Created by Jérémy Demeule on 20/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#include <iostream>
#include <iterator>
#include <list>
#include <type_traits>
#include <vector>

#include <mrl/linq.hpp>
#include <mrl/range.hpp>
#include <mrl/stream.hpp>

template <typename R>
void print_all(const R& r) {
   for (auto x : r)
      std::cout << x << ", ";

   std::cout << std::endl;
}

void range_api() {
   using namespace mrl;

   std::cout << "range_api" << std::endl;

   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   auto odds = make_filter_range(make_ref_range(vs), [](int x) { return x % 2 == 0; });
   print_all(odds);

   auto odd_squares = make_transform_range(odds, [](int x) { return x * x; });

   std::copy(odd_squares.begin(), odd_squares.end(), std::ostream_iterator<int>(std::cout, " "));
   std::cout << std::endl;

   std::vector<int> square_vs = to_vector(odd_squares);
}

void range_linq_api() {
   using namespace mrl_linq;

   std::cout << "range_linq_api" << std::endl;

   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   auto odds_lq = from(vs) | where([](int x) { return x % 2 == 0; });
   print_all(odds_lq);

   auto odd_squares = odds_lq | select([](int x) { return x * x; });
   std::copy(odd_squares.begin(), odd_squares.end(), std::ostream_iterator<int>(std::cout, " "));
   std::cout << std::endl;

   auto square_vs = odd_squares | to_vector();
   square_vs.empty();
}

std::vector<int> make_vs() {
   return std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
}

void range_api_ctn_liveness() {
   using namespace mrl;

   std::cout << "range_api_ctn_liveness" << std::endl;

   auto r = make_range(make_vs());

   print_all(r);
}

void range_api_ints_take() {
   using namespace mrl;

   std::cout << "range_api_ints_take" << std::endl;

   auto values = make_take_n_range(ints(), 15);

   print_all(values);
}

void range_linq_api_ints_take() {
   using namespace mrl_linq;

   std::cout << "range_linq_api_ints_take" << std::endl;

   auto values = from(ints()) | take(15);

   print_all(values);
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
   //                               [=](int y) { return yield_if(x * x + y * y == z * z, std::make_tuple(x, y, z)); });
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
   //                               return from(ints(x, z + 1)) | where([=](int y) { return x * x + y * y == z * z; }) |
   //                                      select([=](int y) { return std::make_tuple(x, y, z); });
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

void range_stream_api() {
   using namespace mrl_stream;

   std::cout << "range_stream_api" << std::endl;

   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
   // clang-format off
   auto r = from(vs)
      .where([](int x) { return x % 2 == 0; })
      .select([](int x) { return x * x; } )
      .to_range();
   // clang-format on
   print_all(r);
}

void filter_api() {
   using namespace mrl;

   std::cout << "filter_api" << std::endl;

   std::vector<int> vs{1, 2, 3};
   {
      auto r = make_filter_range(make_ref_range(vs), [](int x) { return x > 2; });
      print_all(r);
   }
   {
      auto r = make_filter_range(make_ref_range(vs), [](int x) { return x < 2; });
      print_all(r);
   }
}

void repeat_api() {
   using namespace mrl;

   std::cout << "repeat_api" << std::endl;

   auto r  = make_repeat_range(42);
   auto vs = to_vector(make_take_n_range(r, 10));

   print_all(vs);
}

void repeat_linq_api() {
   using namespace mrl_linq;

   std::cout << "repeat_linq_api" << std::endl;

   auto vs = repeat(42) | take(10) | to_vector();

   print_all(vs);
}

void zip_api() {
   using namespace mrl;

   std::cout << "zip_api" << std::endl;

   std::vector<int> v1 = {0, 1, 2, 3};
   std::vector<int> v2 = {4, 5, 6, 7};

   auto r = make_zip_range(make_ref_range(v1), make_ref_range(v2));
   for (auto x : r)
      std::cout << "{ " << std::get<0>(x) << ", " << std::get<1>(x) << " }, ";
   std::cout << std::endl;
}

void zip_linq_api() {
   using namespace mrl_linq;

   std::cout << "zip_linq_api" << std::endl;

   std::vector<int> v1 = {0, 1, 2, 3};
   std::vector<int> v2 = {4, 5, 6, 7};

   auto r = from(v1) | zip(from(v2));
   for (auto x : r)
      std::cout << "{ " << std::get<0>(x) << ", " << std::get<1>(x) << " }, ";
   std::cout << std::endl;
}

void concat_api() {
   using namespace mrl;

   std::cout << "concat_api" << std::endl;

   std::vector<int> v1 = {0, 1, 2, 3};
   std::list<int>   v2 = {4, 5, 6, 7};

   auto r = make_concat_range(make_ref_range(v1), make_ref_range(v2));
   print_all(r);
}

void concat_linq_api() {
   using namespace mrl_linq;

   std::cout << "concat_linq_api" << std::endl;

   std::vector<int> v1 = {0, 1, 2, 3};
   std::list<int>   v2 = {4, 5, 6, 7};

   auto r = from(v1) | concat(from(v2));
   print_all(r);
}

void join_api() {
   using namespace mrl;
   std::cout << "join_api" << std::endl;

   std::vector<int> v1 = {0, 1, 2, 3};
   std::list<int>   v2 = {4, 5, 6, 7};

   auto r = make_join_range(make_ref_range(v1), make_ref_range(v2));
   for (auto x : r)
      std::cout << "{ " << std::get<0>(x) << ", " << std::get<1>(x) << " }, ";
   std::cout << std::endl;
}

void join_linq_api() {
   using namespace mrl_linq;

   std::cout << "join_linq_api" << std::endl;

   std::vector<int> v1 = {0, 1, 2, 3};
   std::list<int>   v2 = {4, 5, 6, 7};

   auto r = from(v1) | join(from(v2));
   for (auto x : r)
      std::cout << "{ " << std::get<0>(x) << ", " << std::get<1>(x) << " }, ";
   std::cout << std::endl;
}


void flatten_api() {
   using namespace mrl;

   std::cout << "flatten_api" << std::endl;

   std::vector<std::vector<int> > vvs = {{1}, {1, 2}, {1, 2, 3}};

   auto x = make_flatten_range(make_ref_range(vvs));
   print_all(x);
}

void flatten_linq_api() {
   using namespace mrl_linq;

   std::cout << "flatten_linq_api" << std::endl;

   std::vector<std::vector<int> > vvs = {{1}, {1, 2}, {1, 2, 3}};

   auto x = from(vvs) | flatten();
   print_all(x);
}

void flatten_api_2() {
   using namespace mrl;

   std::cout << "flatten_api_2" << std::endl;

   auto ps = mrl::make_transform_range(ints(1), [](int z) { return ints(1, z + 1); });

   auto x = make_take_n_range(make_flatten_range(ps), 6);
   print_all(x);
}

void flatten_linq_api_2() {
   using namespace mrl_linq;

   std::cout << "flatten_linq_api_2" << std::endl;

   // clang-format off
   auto ps = from(ints(1))
      | select([](int z) { return ints(1, z + 1); })
      | flatten()
      | take(6);
   // clang-format on
   print_all(ps);
}

void flatten_api_3() {
   using namespace mrl;

   std::cout << "flatten_api_3" << std::endl;

   std::vector<std::vector<int> > vvs = {{1}, {1, 2}, {1, 2, 3}};

   {
      auto x = make_filter_range(make_flatten_range(make_ref_range(vvs)), [](int x) { return x > 2; });
      print_all(x);
   }
   {
      auto x = make_filter_range(make_flatten_range(make_ref_range(vvs)), [](int x) { return x < 2; });
      print_all(x);
   }
}

void flatten_linq_api_3() {
   using namespace mrl_linq;

   std::cout << "flatten_linq_api_3" << std::endl;

   std::vector<std::vector<int> > vvs = {{1}, {1, 2}, {1, 2, 3}};

   {
      auto x = from(vvs) | flatten() | where([](int x) { return x > 2; });
      print_all(x);
   }
   {
      auto x = from(vvs) | flatten() | where([](int x) { return x < 2; });
      print_all(x);
   }
}

void flatten_api_4() {
   using namespace mrl;

   std::cout << "flatten_api_4" << std::endl;

   std::vector<std::vector<int> > vvs = {{}, {1, 2}, {}, {1, 2, 3}};

   {
      auto x = make_filter_range(make_flatten_range(make_ref_range(vvs)), [](int x) { return x > 2; });
      print_all(x);
   }
   {
      auto x = make_filter_range(make_flatten_range(make_ref_range(vvs)), [](int x) { return x < 2; });
      print_all(x);
   }
}

void flatten_linq_api_4() {
   using namespace mrl_linq;

   std::cout << "flatten_linq_api_4" << std::endl;

   std::vector<std::vector<int> > vvs = {{}, {1, 2}, {}, {1, 2, 3}};

   {
      auto x = from(vvs) | flatten() | where([](int x) { return x > 2; });
      print_all(x);
   }
   {
      auto x = from(vvs) | flatten() | where([](int x) { return x < 2; });
      print_all(x);
   }
}

void pythagoreans_2() {
   using namespace mrl;

   std::cout << "pythagoreans_2" << std::endl;

   // clang-format off
   auto zs = make_transform_range(ints(1, 6), [](int z) {
      auto zxs = make_transform_range(ints(1, z + 1), [=](int x) {
         auto zyxs = make_transform_range(ints(x, z + 1), [=](int y) {
            return std::make_tuple(x, y, z);
         });
         return zyxs;
//         return make_filter_range(zyxs, [](auto xyz) {
//            auto x = std::get<0>(xyz);
//            auto y = std::get<1>(xyz);
//            auto z = std::get<2>(xyz);
//            return x * x + y * y == z * z;
//         });
      });
      return make_flatten_range(zxs);
   });
   // clang-format on

   auto bflat = to_vector(make_transform_range(zs, [](auto r) { return to_vector(r); }));

   auto flat    = make_flatten_range(zs);
   auto s       = std::distance(flat.begin(), flat.end());
   auto flat_vs = to_vector(flat);

   auto firsts = make_filter_range(flat, [](auto xyz) {
      auto x = std::get<0>(xyz);
      auto y = std::get<1>(xyz);
      auto z = std::get<2>(xyz);
      return x * x + y * y == z * z;
   });
   //   auto firsts = make_flatten_range(zs) | mrl_linq::where([](auto xyz) { return false; });
   for (auto triple : firsts) {
      std::cout << "{ " << std::get<0>(triple) << ", " << std::get<1>(triple) << ", " << std::get<2>(triple) << " }"
                << std::endl;
   }
   //   for (auto x : firsts)
   //      std::cout << "{ " << std::get<0>(x) << ", " << std::get<1>(x) << " }, ";
   std::cout << std::endl;
}

void pythagoreans_3() {
   using namespace mrl;

   std::cout << "pythagoreans_3" << std::endl;

   // clang-format off
   auto triples = make_transform_range(ints(1, 6), [](int z) {
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
   });
   // clang-format on

   auto bflat = to_vector(make_transform_range(triples, [](auto r) { return to_vector(r); }));


   for (auto triple : make_flatten_range(triples)) {
      std::cout << "{ " << std::get<0>(triple) << ", " << std::get<1>(triple) << ", " << std::get<2>(triple) << " }"
                << std::endl;
   }
}

void pythagoreans_linq() {
   using namespace mrl_linq;
   std::cout << "pythagoreans_linq" << std::endl;

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
      | flatten();
   // clang-format on

   for (auto triple : triples | take(10)) {
      std::cout << "{ " << std::get<0>(triple) << ", " << std::get<1>(triple) << ", " << std::get<2>(triple) << " }"
                << std::endl;
   }
}


void pythagoreans_linq_2() {
   using namespace mrl_linq;
   std::cout << "pythagoreans_linq_2" << std::endl;

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
   });
   // clang-format on

   for (auto triple : triples | take(10)) {
      std::cout << "{ " << std::get<0>(triple) << ", " << std::get<1>(triple) << ", " << std::get<2>(triple) << " }"
                << std::endl;
   }
}

void skip_api() {
   using namespace mrl;

   std::cout << "skip_api" << std::endl;

   auto values = make_skip_range(ints(1, 10), 2);

   print_all(values);
}

void skip_linq_api() {
   using namespace mrl_linq;

   std::cout << "skip_linq_api" << std::endl;

   auto values = from(ints(1, 10)) | skip(2);

   print_all(values);
}


template <typename InputIterator>
struct cursor {
   typedef typename InputIterator::value_type value_type;

   cursor(InputIterator first, InputIterator last)
      : m_first(first)
      , m_last(last) {}

   bool done() const {
      return m_first == m_last;
   }

   void next() {
      ++m_first;
   }

   value_type value() {
      return *m_first;
   }

   InputIterator m_first;
   InputIterator m_last;
};


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

int main(int argc, const char* argv[]) {


   range_api();
   range_linq_api();
   //   range_api_ctn_liveness();
   //   range_api_ints_take();
   //   range_linq_api_ints_take();
   //   range_stream_api();
   filter_api();
   repeat_api();
   repeat_linq_api();
   zip_api();
   zip_linq_api();
   concat_api();
   concat_linq_api();
   join_api();
   join_linq_api();
   range_linq_pythagorean_triples();


   flatten_api();
   flatten_linq_api();
   flatten_api_2();
   flatten_linq_api_2();
   flatten_api_3();
   flatten_linq_api_3();
   flatten_api_4();
   flatten_linq_api_4();

   pythagoreans_2();
   pythagoreans_3();
   pythagoreans_linq();
   pythagoreans_linq_2();

   skip_api();
   skip_linq_api();


   //   mrl_linq::from(vs).where([](int x) -> bool { return x % 2 == 0; });

   return 0;
}

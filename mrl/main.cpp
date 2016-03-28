//
//  main.cpp
//  mrl
//
//  Created by Jérémy Demeule on 20/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

#include "linq.hpp"
#include "range.hpp"

void range_api() {
   using namespace mrl;
   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   auto odds = make_filter_range(make_ref_range(vs), [](int x) { return x % 2 == 0; });

   for (auto x : odds)
      std::cout << x << ", ";
   std::cout << std::endl;

   auto odd_squares = make_transform_range(odds, [](int x) { return x * x; });

   std::copy(odd_squares.begin(), odd_squares.end(), std::ostream_iterator<int>(std::cout, " "));
   std::cout << std::endl;

   std::vector<int> square_vs = to_vector(odd_squares);
}

void range_linq_api() {
   using namespace mrl_linq;

   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   auto odds_lq = from(vs) | where([](int x) { return x % 2 == 0; });
   for (auto x : odds_lq)
      std::cout << x << ", ";
   std::cout << std::endl;

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
   auto r = make_range(make_vs());

   for (auto x : r)
      std::cout << x << ", ";
   std::cout << std::endl;
}

void range_api_ints_take() {
   using namespace mrl;
   auto values = make_take_n_range(ints(), 15);

   for (auto x : values)
      std::cout << x << " ";
   std::cout << std::endl;
}

void range_linq_api_ints_take() {
   using namespace mrl_linq;
   auto values = from(ints()) | take(15);

   for (auto x : values)
      std::cout << x << " ";
   std::cout << std::endl;
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

   //   for (auto z : ints(1)) {
   //      for (auto x : ints(1, z)) {
   //         for (auto y : from(ints(1, x)) | where([=](auto y) { return x * x + y * y == z * z; })) {
   //            // x, y, z;
   //         }
   //      }
   //   }

   auto xys = from(ints(1)) | select([](auto y) { return ints(1, y); });
   for (auto xy : xys) {
      for (auto x : xy)
         std::cout << x << " ";
      std::cout << std::endl;
   }
   std::cout << std::endl;
}

int main(int argc, const char* argv[]) {


   range_api();
   range_linq_api();
   range_api_ctn_liveness();
   range_api_ints_take();
   range_linq_api_ints_take();
   //   range_linq_pythagorean_triples();

   //   mrl_linq::from(vs).where([](int x) -> bool { return x % 2 == 0; });

   return 0;
}

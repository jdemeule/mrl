//
//  build_range_test.cpp
//  test
//
//  Created by Jérémy Demeule on 07/05/16.
//
//

#include <vector>

#include <mrl/linq.hpp>
#include <mrl/range.hpp>

#include <gtest/gtest.h>

TEST(BuildRange, iterator) {
   using namespace mrl;

   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   auto r = make_iterator_range(std::begin(vs), std::end(vs));

   ASSERT_EQ(vs.size(), std::distance(std::begin(r), std::end(r)));
   ASSERT_TRUE(std::equal(std::begin(vs), std::end(vs), std::begin(r)));
}


TEST(BuildRange, ref) {
   using namespace mrl;

   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   auto r = make_ref_range(vs);

   ASSERT_EQ(vs.size(), std::distance(std::begin(r), std::end(r)));
   ASSERT_TRUE(std::equal(std::begin(vs), std::end(vs), std::begin(r)));
}


TEST(BuildRange, copy) {
   using namespace mrl;

   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   auto r = make_range(std::vector<int>(vs));

   ASSERT_EQ(vs.size(), std::distance(std::begin(r), std::end(r)));
   ASSERT_TRUE(std::equal(std::begin(vs), std::end(vs), std::begin(r)));
}


TEST(BuildRangeLinq, iterator) {
   using namespace mrl_linq;

   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   auto r = from(std::begin(vs), std::end(vs));

   ASSERT_EQ(vs.size(), std::distance(std::begin(r), std::end(r)));
   ASSERT_TRUE(std::equal(std::begin(vs), std::end(vs), std::begin(r)));
}


TEST(BuildRangeLinq, ref) {
   using namespace mrl_linq;

   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   auto r = from(vs);

   ASSERT_EQ(vs.size(), std::distance(std::begin(r), std::end(r)));
   ASSERT_TRUE(std::equal(std::begin(vs), std::end(vs), std::begin(r)));
}


TEST(BuildRangeLinq, copy) {
   using namespace mrl_linq;

   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   auto r = with(std::vector<int>(vs));

   ASSERT_EQ(vs.size(), std::distance(std::begin(r), std::end(r)));
   ASSERT_TRUE(std::equal(std::begin(vs), std::end(vs), std::begin(r)));
}

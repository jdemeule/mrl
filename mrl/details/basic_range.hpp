//
//  basic_range.hpp
//  mrl
//
//  Created by Jérémy Demeule on 28/03/16.
//  Copyright © 2016 Jérémy Demeule. All rights reserved.
//

#ifndef basic_range_h
#define basic_range_h

#include <iterator>

namespace mrl {

template <typename Iterator>
using IteratorCategory = typename std::iterator_traits<Iterator>::iterator_category;

template <typename Iterator, typename Category = typename std::iterator_traits<Iterator>::iterator_category>
struct range_iterator_category {
   typedef Category iterator_category;
};

template <typename Iterator>
struct range_iterator_category<Iterator, std::bidirectional_iterator_tag> {
   typedef std::forward_iterator_tag iterator_category;
};

template <typename Iterator>
struct range_iterator_category<Iterator, std::random_access_iterator_tag> {
   typedef std::forward_iterator_tag iterator_category;
};

template <typename Iterator1,
          typename Iterator2,
          typename Cat1 = IteratorCategory<Iterator1>,
          typename Cat2 = IteratorCategory<Iterator2> >
struct max_capacity_range_iterator_category {
   typedef Cat1 iterator_category;
};


// template <typename Iterator1, typename Iterator2>
// struct max_capacity_range_iterator_category<Iterator1,
//                                            Iterator2,
//                                            std::bidirectional_iterator_tag,
//                                            std::input_iterator_tag> {
//   typedef std::input_iterator_tag iterator_category;
//};
//
//
// template <typename Iterator1, typename Iterator2>
// struct max_capacity_range_iterator_category<Iterator1,
//                                            Iterator2,
//                                            std::bidirectional_iterator_tag,
//                                            std::forward_iterator_tag> {
//   typedef std::forward_iterator_tag iterator_category;
//};
//
// template <typename Iterator1, typename Iterator2>
// struct max_capacity_range_iterator_category<Iterator1,
//                                            Iterator2,
//                                            std::bidirectional_iterator_tag,
//                                            std::bidirectional_iterator_tag> {
//   typedef std::forward_iterator_tag iterator_category;
//};
//
//
//
// template <typename Iterator1, typename Iterator2>
// struct max_capacity_range_iterator_category<Iterator1,
//                                            Iterator2,
//                                            std::bidirectional_iterator_tag,
//                                            std::random_access_iterator_tag> {
//   typedef std::forward_iterator_tag iterator_category;
//};
//
// template <typename Iterator1, typename Iterator2>
// struct max_capacity_range_iterator_category<Iterator1,
//                                            Iterator2,
//                                            std::input_iterator_tag,
//                                            std::bidirectional_iterator_tag> {
//   typedef std::input_iterator_tag iterator_category;
//};



template <typename Iterator>
using range_iterator_category_t = typename range_iterator_category<Iterator>::iterator_category;


struct basic_range {};

struct finite_range_tag {};
struct infinite_range_tag {};

//   struct range_category

template <typename range_category>
struct range : public basic_range {
   typedef range_category category;
};


template <typename R>
struct is_range : public std::is_base_of<basic_range, R> {};
}

#endif /* basic_range_h */

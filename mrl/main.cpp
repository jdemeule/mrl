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

namespace mrl {

struct basic_range {};

template <typename ForwardIt>
struct iterator_range : public basic_range {
public:
   iterator_range(ForwardIt first, ForwardIt last)
      : m_first(first)
      , m_last(last) {}

   ForwardIt begin() const {
      return m_first;
   }

   ForwardIt end() const {
      return m_last;
   }

private:
   ForwardIt m_first;
   ForwardIt m_last;
};

template <typename ForwardIt>
iterator_range<ForwardIt> make_range(ForwardIt first, ForwardIt last) {
   return iterator_range<ForwardIt>(first, last);
}


template <typename Ctn>
struct ctn_ref_range : public basic_range {
public:
   typedef typename Ctn::const_iterator iterator;

   explicit ctn_ref_range(const Ctn& ctn)
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
ctn_ref_range<Rg> make_ref_range(const Rg& rg) {
   return ctn_ref_range<Rg>(rg);
};

template <typename Ctn>
struct ctn_range : public basic_range {
public:
   typedef typename Ctn::const_iterator iterator;

   explicit ctn_range(Ctn&& ctn)
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

template <typename Rg>
ctn_range<Rg> make_range(Rg&& r) {
   return ctn_range<Rg>(std::move(r));
}



template <typename ForwardIt, typename Predicate>
struct filter_iterator : public std::iterator<std::input_iterator_tag, typename ForwardIt::value_type> {

   typedef typename ForwardIt::value_type value_type;

   filter_iterator(ForwardIt first, ForwardIt last, Predicate pred)
      : m_first(first)
      , m_last(last)
      , m_pred(pred) {}

   filter_iterator& operator++() {
      advance();
      return *this;
   }

   filter_iterator operator++(int) {
      advance();
      return filter_iterator(m_first, m_last, m_pred);
   }

   value_type operator*() const {
      return *m_first;
   }

   bool operator==(const filter_iterator& rhs) const {
      return m_first == rhs.m_first;
   }

   bool operator!=(const filter_iterator& rhs) const {
      return !(*this == rhs);
   }

private:
   void advance() {
      do {
         ++m_first;
      } while (m_first != m_last && !m_pred(*m_first));
   }

   ForwardIt m_first;
   ForwardIt m_last;
   Predicate m_pred;
};

template <typename ForwardIt, typename Predicate>
struct filter_range : public basic_range {

   typedef filter_iterator<ForwardIt, Predicate> iterator;

   filter_range(ForwardIt first, ForwardIt last, Predicate pred)
      : m_first(first)
      , m_last(last)
      , m_pred(pred) {}

   iterator begin() const {
      return iterator(m_first, m_last, m_pred);
   }

   iterator end() const {
      return iterator(m_last, m_last, m_pred);
   }

private:
   ForwardIt m_first;
   ForwardIt m_last;
   Predicate m_pred;
};

template <typename ForwardIt, typename Predicate>
filter_range<ForwardIt, Predicate> make_filter_range(ForwardIt first, ForwardIt last, Predicate pred) {
   return filter_range<ForwardIt, Predicate>(first, last, pred);
}

template <typename Rg,
          typename Predicate,
          typename std::enable_if<std::is_base_of<basic_range, Rg>::value>::type* = nullptr>
filter_range<typename Rg::iterator, Predicate> make_filter_range(const Rg& rg, Predicate pred) {
   return filter_range<typename Rg::iterator, Predicate>(rg.begin(), rg.end(), pred);
};



template <typename ForwardIt, typename F>
struct transform_iterator : public std::iterator<std::input_iterator_tag, typename ForwardIt::value_type> {

   typedef typename ForwardIt::value_type value_type;

   transform_iterator(ForwardIt first, ForwardIt last, F apply)
      : m_first(first)
      , m_last(last)
      , m_apply(apply) {}

   transform_iterator& operator++() {
      ++m_first;
      return *this;
   }

   transform_iterator operator++(int) {
      ++m_first;
      return transform_iterator(m_first, m_last, m_apply);
   }

   value_type operator*() const {
      return m_apply(*m_first);
   }

   bool operator==(const transform_iterator& rhs) const {
      return m_first == rhs.m_first;
   }

   bool operator!=(const transform_iterator& rhs) const {
      return !(*this == rhs);
   }

private:
   ForwardIt m_first;
   ForwardIt m_last;
   F         m_apply;
};

template <typename ForwardIt, typename F>
struct transform_range : public basic_range {

   typedef transform_iterator<ForwardIt, F> iterator;

   transform_range(ForwardIt first, ForwardIt last, F apply)
      : m_first(first)
      , m_last(last)
      , m_apply(apply) {}

   iterator begin() const {
      return iterator(m_first, m_last, m_apply);
   }

   iterator end() const {
      return iterator(m_last, m_last, m_apply);
   }

private:
   ForwardIt m_first;
   ForwardIt m_last;
   F         m_apply;
};

template <typename ForwardIt, typename F>
transform_range<ForwardIt, F> make_transform_range(ForwardIt first, ForwardIt last, F apply) {
   return transform_range<ForwardIt, F>(first, last, apply);
}

template <typename Rg, typename F, typename std::enable_if<std::is_base_of<basic_range, Rg>::value>::type* = nullptr>
transform_range<typename Rg::iterator, F> make_transform_range(const Rg& rg, F apply) {
   return transform_range<typename Rg::iterator, F>(rg.begin(), rg.end(), apply);
};



template <typename T, typename Generator>
struct nums_iterator : public std::iterator<std::input_iterator_tag, T> {

   typedef T value_type;

   nums_iterator(T first)
      : m_first(first) {}

   nums_iterator& operator++() {
      m_first = m_gen(m_first);
      return *this;
   }

   nums_iterator operator++(int) {
      m_first = m_gen(m_first);
      return nums_iterator(m_first);
   }

   value_type operator*() const {
      return m_apply(*m_first);
   }

   bool operator==(const nums_iterator& rhs) const {
      return m_first == rhs.m_first;
   }

   bool operator!=(const nums_iterator& rhs) const {
      return !(*this == rhs);
   }

private:
   T         m_first;
   Generator m_gen;
};

// + generator
template <typename T, typename Generator>
struct nums_range : public basic_range {
   typedef nums_iterator<T, Generator> iterator;

   explicit nums_range(T first, T last, Generator gen)
      : m_first(first)
      , m_last(last)
      , m_generator(gen) {}

   iterator begin() const {
      return iterator(m_first, m_generator);
   }

   iterator end() const {
      return iterator(m_last, m_generator);
   }

private:
   T         m_first;
   T         m_last;
   Generator m_generator;
};

template <typename T, typename Generator>
auto make_nums_range(T first, T last, Generator g) {
   return nums_range<T, Generator>(first, last, g);
}

auto ints(int initial_value = 0, int last_value = INT_MAX) {
   return make_nums_range(initial_value, last_value, [](int x) { return ++x; });
}
}

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


void range_api() {
   using namespace mrl;
   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   auto odds = make_filter_range(make_ref_range(vs), [](int x) -> bool { return x % 2 == 0; });

   for (auto x : odds)
      std::cout << x << ", ";
   std::cout << std::endl;

   auto odd_squares = make_transform_range(odds, [](int x) { return x * x; });

   std::copy(odd_squares.begin(), odd_squares.end(), std::ostream_iterator<int>(std::cout, " "));
   std::cout << std::endl;
}

void range_linq_api() {
   using namespace mrl_linq;

   std::vector<int> vs{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

   auto odds_lq = from(vs) | where([](int x) -> bool { return x % 2 == 0; });
   for (auto x : odds_lq)
      std::cout << x << ", ";
   std::cout << std::endl;

   auto odd_squares = odds_lq | select([](int x) { return x * x; });
   std::copy(odd_squares.begin(), odd_squares.end(), std::ostream_iterator<int>(std::cout, " "));
   std::cout << std::endl;
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

int main(int argc, const char* argv[]) {


   range_api();
   range_linq_api();
   range_api_ctn_liveness();

   //   mrl_linq::from(vs).where([](int x) -> bool { return x % 2 == 0; });

   return 0;
}

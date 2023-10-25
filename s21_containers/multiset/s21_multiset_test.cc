#include "s21_multiset.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <set>

TEST(Multiset, test_1) {
  s21::multiset<int> ms;
  std::multiset<int> mt;
  EXPECT_EQ(ms.empty(), true);
  EXPECT_EQ(mt.empty(), true);
  EXPECT_EQ(ms.size(), 0UL);
  EXPECT_EQ(mt.size(), 0UL);
  ms.insert(1);
  ms.insert(1);
  mt.insert(1);
  mt.insert(1);
  EXPECT_EQ(ms.empty(), false);
  EXPECT_EQ(mt.empty(), false);
  EXPECT_EQ(ms.contains(1), true);
  EXPECT_EQ(*ms.begin(), 1);
  EXPECT_EQ(*mt.begin(), 1);
  EXPECT_EQ(ms.size(), 2UL);
  EXPECT_EQ(mt.size(), 2UL);
  for (int i = 0; i < 100; ++i) {
    ms.insert(i);
    mt.insert(i);
  }
  EXPECT_EQ(ms.size(), 102UL);
  EXPECT_EQ(mt.size(), 102UL);
  EXPECT_EQ(*ms.begin(), 0);
  EXPECT_EQ(*mt.begin(), 0);
  EXPECT_EQ(ms.max_size(), 18446744073709551615UL);

  ms.erase(ms.find(1));
  mt.erase(mt.find(1));

  EXPECT_EQ(ms.size(), 101UL);
  EXPECT_EQ(mt.size(), 101UL);

  EXPECT_EQ(*(--ms.end()), 99);
  EXPECT_EQ(*(--mt.end()), 99);
}

TEST(Multiset, test_2) {
  s21::multiset<int> ms{1, 23, -8, 16, 123};
  std::multiset<int> mt{1, 23, -8, 16, 123};
  EXPECT_EQ(ms.size(), mt.size());
}

TEST(Multiset, test_3) {
  s21::multiset<int> ms{1, 23, -8, 16, 123};
  s21::multiset<int> mt{ms};
  EXPECT_EQ(ms.size(), mt.size());
  for (auto& item : ms) {
    mt.contains(item);
  }
  mt.clear();
  EXPECT_EQ(0UL, mt.size());
}

TEST(Multiset, test_4) {
  s21::multiset<int> mt{1, 23, -8, 16, 123};
  s21::multiset<int> ms(std::move(mt));

  EXPECT_EQ(ms.contains(1), true);
  EXPECT_EQ(ms.contains(23), true);
  EXPECT_EQ(ms.contains(-8), true);
  EXPECT_EQ(ms.contains(16), true);
  EXPECT_EQ(ms.contains(123), true);
  EXPECT_EQ(ms.size(), 5UL);
}

TEST(Multiset, test_5) {
  s21::multiset<int> mt{1, 23, -8, 16, 123};
  s21::multiset<int> ms = std::move(mt);

  EXPECT_EQ(ms.contains(1), true);
  EXPECT_EQ(ms.contains(23), true);
  EXPECT_EQ(ms.contains(-8), true);
  EXPECT_EQ(ms.contains(16), true);
  EXPECT_EQ(ms.contains(123), true);
  EXPECT_EQ(ms.size(), 5UL);
}

TEST(Multiset, test_6) {
  s21::multiset<int> mt{1, 23, -8, 16, 123};
  s21::multiset<int> ms{2, 49, 16, -36, -49};
  mt.swap(ms);
  EXPECT_EQ(ms.contains(1), true);
  EXPECT_EQ(ms.contains(23), true);
  EXPECT_EQ(ms.contains(-8), true);
  EXPECT_EQ(ms.contains(123), true);
  EXPECT_EQ(ms.contains(2), false);
  EXPECT_EQ(ms.contains(49), false);
  EXPECT_EQ(ms.contains(-36), false);
  EXPECT_EQ(ms.contains(-49), false);

  EXPECT_EQ(mt.contains(1), false);
  EXPECT_EQ(mt.contains(23), false);
  EXPECT_EQ(mt.contains(-8), false);
  EXPECT_EQ(mt.contains(123), false);
  EXPECT_EQ(mt.contains(2), true);
  EXPECT_EQ(mt.contains(49), true);
  EXPECT_EQ(mt.contains(-36), true);
  EXPECT_EQ(mt.contains(-49), true);

  EXPECT_EQ(mt.size(), 5UL);
  EXPECT_EQ(ms.size(), 5UL);
}

TEST(Multiset, test_7) {
  s21::multiset<int> mt{1, 23, -8, 16, 123};
  s21::multiset<int> ms{2, 49, 16, -36, -49};
  ms.merge(mt);
  EXPECT_EQ(ms.contains(1), true);
  EXPECT_EQ(ms.contains(23), true);
  EXPECT_EQ(ms.contains(-8), true);
  EXPECT_EQ(ms.contains(123), true);
  EXPECT_EQ(ms.contains(2), true);
  EXPECT_EQ(ms.contains(49), true);
  EXPECT_EQ(ms.contains(-36), true);
  EXPECT_EQ(ms.contains(-49), true);
  EXPECT_EQ(ms.count(16), 2UL);

  EXPECT_EQ(ms.size(), 10UL);
}

TEST(Multiset, test_8) {
  s21::multiset<int> mt{1, 23, -8, 16, 123};
  EXPECT_EQ(*mt.lower_bound({23}), 23);
}

TEST(Multiset, test_9) {
  s21::multiset<int> mt{1, 23, 23, 23, 123};
  EXPECT_EQ(mt.size(), 5UL);
  EXPECT_EQ(*(--mt.lower_bound({23})), 1);
  EXPECT_EQ(*mt.lower_bound({23}), 23);
  EXPECT_EQ(*(++mt.lower_bound({23})), 23);
  EXPECT_EQ(*(++(++mt.lower_bound({23}))), 23);
}

TEST(Multiset, test_10) {
  s21::multiset<int> mt{1, 23, 23, 23, 123};
  EXPECT_EQ(mt.size(), 5UL);
  EXPECT_EQ(*mt.upper_bound({23}), 123);
  EXPECT_EQ(*(--mt.upper_bound({23})), 23);
}

TEST(Multiset, test_11) {
  s21::multiset<int> mt{1, 23, 23, 23, 123};
  mt.insert_many(5, 6, 7, 5);
  EXPECT_EQ(mt.size(), 9UL);
  EXPECT_EQ(*mt.upper_bound({23}), 123);
  EXPECT_EQ(*(--mt.upper_bound({23})), 23);
  EXPECT_EQ(mt.contains(5), 1);
  EXPECT_EQ(mt.count(5), 2UL);
}

TEST(Multiset, MoveAssignmentOperator) {
  s21::multiset<int> set1{1, 2, 3};
  s21::multiset<int> set2{4, 5, 6};

  set1 = std::move(set2);  // Выполняем перемещение

  // Проверяем, что set1 содержит элементы из set2, а set2 пустой
  EXPECT_EQ(set1.size(), 3UL);
  EXPECT_EQ(set2.size(), 0UL);
  EXPECT_TRUE(set1.count(4) > 0);
  EXPECT_TRUE(set1.count(5) > 0);
  EXPECT_TRUE(set1.count(6) > 0);
}

TEST(Multiset, EqualRange) {
  s21::multiset<int> set{1, 2, 2, 3, 4, 4, 4};

  // Ищем диапазон элементов со значением 4
  auto range = set.equal_range(4);

  // Проверяем, что найденный диапазон содержит все элементы 4
  EXPECT_EQ(*(range.first), 4);
}

TEST(Multiset, EqualRangeNonexistent) {
  s21::multiset<int> set{1, 2, 2, 3, 4, 4, 4};

  // Ищем диапазон элементов со значением 5 (которого нет в множестве)
  auto range = set.equal_range(5);

  // Проверяем, что найденный диапазон пустой (нет элементов)
  EXPECT_EQ(range.first, range.second);
}

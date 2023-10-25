#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(SetTest, CompareWithStdSet) {
  std::set<int> stdSet = {1, 2, 3, 4};
  s21::set<int> mySet = {1, 2, 3, 4};

  // Сравнение размеров
  EXPECT_EQ(mySet.size(), stdSet.size());

  auto stdIt = stdSet.begin();
  for (auto it = mySet.begin(); it != mySet.end(); ++it, ++stdIt) {
    EXPECT_EQ(*it, *stdIt);
  }

  // Проверка на наличие элемента
  EXPECT_EQ(stdSet.find(3) != stdSet.end(), mySet.contains(3));

  // Проверка на отсутствие элемента
  EXPECT_EQ(stdSet.find(5) == stdSet.end(), !mySet.contains(5));

  // Вставка нового элемента
  stdSet.insert(5);
  mySet.insert(5);
  EXPECT_EQ(mySet.size(), stdSet.size());

  // Удаление элемента
  stdSet.erase(1);
  auto it = mySet.find(1);
  mySet.erase(it);
  EXPECT_EQ(stdSet.size(), mySet.size());

  // Очистка
  stdSet.clear();
  mySet.clear();
  EXPECT_EQ(stdSet.empty(), mySet.empty());
}

TEST(S21SetTest, TestErase) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> custom_set = {1, 2, 3};

  std_set.erase(2);
  custom_set.erase(custom_set.find(2));

  ASSERT_EQ(std_set.size(), custom_set.size());
}

TEST(S21SetTest, TestFind) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> custom_set = {1, 2, 3};

  ASSERT_EQ(std_set.find(2) != std_set.end(),
            custom_set.find(2) != custom_set.end());
}

TEST(S21SetTest, TestContains) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> custom_set = {1, 2, 3};

  ASSERT_EQ(std_set.find(2) != std_set.end(), custom_set.contains(2));
}

TEST(S21SetTest, TestSwap) {
  std::set<int> std_set1 = {1, 2, 3};
  std::set<int> std_set2 = {4, 5, 6};
  s21::set<int> custom_set1 = {1, 2, 3};
  s21::set<int> custom_set2 = {4, 5, 6};

  std_set1.swap(std_set2);
  custom_set1.swap(custom_set2);

  ASSERT_EQ(std_set1.size(), custom_set1.size());
  ASSERT_EQ(std_set2.size(), custom_set2.size());
}

TEST(S21SetTest, TestClear) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> custom_set = {1, 2, 3};

  std_set.clear();
  custom_set.clear();

  ASSERT_EQ(std_set.size(), custom_set.size());
}

TEST(S21SetTest, TestMerge) {
  std::set<int> std_set1 = {1, 2, 3};
  std::set<int> std_set2 = {4, 5, 6};
  s21::set<int> custom_set1 = {1, 2, 3};
  s21::set<int> custom_set2 = {4, 5, 6};

  std_set1.merge(std_set2);
  custom_set1.merge(custom_set2);

  ASSERT_EQ(std_set1.size(), custom_set1.size());
  ASSERT_EQ(std_set2.size(), custom_set2.size());
}

TEST(S21SetTest, TestEmpty) {
  std::set<int> std_set;
  s21::set<int> custom_set;

  ASSERT_EQ(std_set.empty(), custom_set.empty());
}

TEST(S21SetTest, TestInitializerList) {
  std::set<int> std_set = {1, 2, 3};
  s21::set<int> custom_set = {1, 2, 3};

  ASSERT_EQ(std_set.size(), custom_set.size());
}

TEST(CustomSetTest, TestInsertMany) {
  std::set<int> std_set;
  s21::set<int> custom_set;

  for (int i = 0; i < 100; ++i) {
    std_set.insert(i);
    custom_set.insert(i);
  }

  ASSERT_EQ(std_set.size(), custom_set.size());
}

TEST(CustomSetTest, TestEraseMany) {
  std::set<int> std_set;
  s21::set<int> custom_set;

  for (int i = 0; i < 100; ++i) {
    std_set.insert(i);
    custom_set.insert(i);
  }

  for (int i = 0; i < 50; ++i) {
    std_set.erase(i);
    custom_set.erase(custom_set.find(i));
  }

  ASSERT_EQ(std_set.size(), custom_set.size());
}

TEST(CustomSetTest, TestFindMany) {
  std::set<int> std_set;
  s21::set<int> custom_set;

  for (int i = 0; i < 100; ++i) {
    std_set.insert(i);
    custom_set.insert(i);
  }

  for (int i = 0; i < 100; ++i) {
    ASSERT_EQ(std_set.find(i) != std_set.end(),
              custom_set.find(i) != custom_set.end());
  }
}

TEST(CustomSetTest, TestMergeMany) {
  std::set<int> std_set1, std_set2;
  s21::set<int> custom_set1, custom_set2;

  for (int i = 0; i < 5; ++i) {
    std_set1.insert(i);
    custom_set1.insert(i);
  }

  for (int i = 25; i < 30; ++i) {
    std_set2.insert(i);
    custom_set2.insert(i);
  }

  std_set1.merge(std_set2);
  custom_set1.merge(custom_set2);

  ASSERT_EQ(std_set1.size(), custom_set1.size());
  ASSERT_EQ(std_set2.size(), custom_set2.size());
}

TEST(CustomSetTest, TestSwapMany) {
  std::set<int> std_set1, std_set2;
  s21::set<int> custom_set1, custom_set2;

  for (int i = 0; i < 50; ++i) {
    std_set1.insert(i);
    custom_set1.insert(i);
  }

  for (int i = 50; i < 100; ++i) {
    std_set2.insert(i);
    custom_set2.insert(i);
  }

  std_set1.swap(std_set2);
  custom_set1.swap(custom_set2);

  ASSERT_EQ(std_set1.size(), custom_set1.size());
  ASSERT_EQ(std_set2.size(), custom_set2.size());
}

TEST(CustomSetTest, TestClearMany) {
  std::set<int> std_set;
  s21::set<int> custom_set;

  for (int i = 0; i < 100; ++i) {
    std_set.insert(i);
    custom_set.insert(i);
  }

  std_set.clear();
  custom_set.clear();

  ASSERT_EQ(std_set.size(), custom_set.size());
}

TEST(CustomSetTest, TestDuplicateInsertMany) {
  std::set<int> std_set;
  s21::set<int> custom_set;

  for (int i = 0; i < 50; ++i) {
    std_set.insert(i);
    custom_set.insert(i);
  }

  for (int i = 25; i < 75; ++i) {
    std_set.insert(i);
    custom_set.insert(i);
  }

  ASSERT_EQ(std_set.size(), custom_set.size());
}

TEST(CustomSetTest, TestIterateMany) {
  std::set<int> std_set;
  s21::set<int> custom_set;

  for (int i = 0; i < 100; ++i) {
    std_set.insert(i);
    custom_set.insert(i);
  }

  auto std_it = std_set.begin();
  auto custom_it = custom_set.begin();

  while (std_it != std_set.end() && custom_it != custom_set.end()) {
    ASSERT_EQ(*std_it, *custom_it);
    ++std_it;
    ++custom_it;
  }

  ASSERT_EQ(std_it, std_set.end());
  ASSERT_EQ(custom_it, custom_set.end());
}

TEST(CustomSetTest, TestEmptyMany) {
  std::set<int> std_set;
  s21::set<int> custom_set;

  ASSERT_EQ(std_set.empty(), custom_set.empty());

  for (int i = 0; i < 100; ++i) {
    std_set.insert(i);
    custom_set.insert(i);
  }

  ASSERT_EQ(std_set.empty(), custom_set.empty());

  std_set.clear();
  custom_set.clear();

  ASSERT_EQ(std_set.empty(), custom_set.empty());
}

TEST(SetTest, InsertMany_MultipleValues) {
  s21::set<int> s21_set;
  std::set<int> std_set;

  auto s21_results = s21_set.insert_many(1, 2, 3, 4, 5);
  std_set.insert({1, 2, 3, 4, 5});

  ASSERT_EQ(s21_set.size(), std_set.size());
  for (const auto& [it, success] : s21_results) {
    ASSERT_TRUE(success);
    ASSERT_TRUE(std_set.count(*it));
  }
}

TEST(SetTest, InsertMany_DuplicateValues) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  auto s21_results = s21_set.insert_many(1, 2);

  // ASSERT_EQ(s21_set.size(), 2);
  ASSERT_FALSE(s21_results[0].second);  // First insertion should fail
  ASSERT_TRUE(s21_results[1].second);   // Second insertion should succeed
}

TEST(SetTest, InsertMany_EmptySet) {
  s21::set<int> s21_set;
  auto s21_results = s21_set.insert_many();

  // ASSERT_EQ(s21_set.size(), 0);
  ASSERT_TRUE(s21_results.empty());
}

TEST(SetTest, InsertMany_SingleValue) {
  s21::set<int> s21_set;
  auto s21_results = s21_set.insert_many(1);

  // ASSERT_EQ(s21_set.size(), 1);
  ASSERT_TRUE(s21_results[0].second);
  ASSERT_EQ(*s21_results[0].first, 1);
}

TEST(SetTest, InsertMany_LargeNumber) {
  s21::set<int> s21_set;
  auto s21_results = s21_set.insert_many(1, 2, 3, 4, 5, 6, 7, 8, 9);

  // ASSERT_EQ(s21_set.size(), 9);
  for (const auto& [it, success] : s21_results) {
    ASSERT_TRUE(success);
  }
}

TEST(SetTest, EraseExistingKeyTest) {
  s21::set<int> test_set;
  test_set.insert(1);
  test_set.insert(2);
  test_set.insert(3);

  // Проверяем, что ключи существуют
  EXPECT_TRUE(test_set.contains(1));
  EXPECT_TRUE(test_set.contains(2));
  EXPECT_TRUE(test_set.contains(3));

  // Удаляем ключ и проверяем, что его больше нет в set
  test_set.erase(2);
  EXPECT_TRUE(test_set.contains(1));
  EXPECT_FALSE(test_set.contains(2));
  EXPECT_TRUE(test_set.contains(3));
}

TEST(SetTest, MoveAssignmentOperator) {
  s21::set<int> original_set;
  original_set.insert(1);
  original_set.insert(2);

  s21::set<int> assigned_set;
  assigned_set = std::move(original_set);

  EXPECT_TRUE(assigned_set.contains(1));
  EXPECT_TRUE(assigned_set.contains(2));
  // Предположим, что у вас есть метод size или empty для проверки размера или
  // пустоты
  EXPECT_EQ(original_set.size(), 0UL);
}

TEST(SetTest, MoveConstructor) {
  s21::set<int> original_set;
  original_set.insert(1);
  original_set.insert(2);

  s21::set<int> moved_set(std::move(original_set));

  EXPECT_TRUE(moved_set.contains(1));
  EXPECT_TRUE(moved_set.contains(2));
  // Предположим, что у вас есть метод size или empty для проверки размера или
  // пустоты
  EXPECT_EQ(original_set.size(), 0UL);  // original should now be empty
}

TEST(SetTest, CopyConstructor) {
  s21::set<int> original_set;
  original_set.insert(1);
  original_set.insert(2);

  s21::set<int> copied_set(original_set);

  EXPECT_TRUE(copied_set.contains(1));
  EXPECT_TRUE(copied_set.contains(2));
  EXPECT_TRUE(original_set.contains(1));  // original should be unaffected
}
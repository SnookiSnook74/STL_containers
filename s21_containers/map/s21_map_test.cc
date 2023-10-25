#include <gtest/gtest.h>

#include "../../s21_containers.h"

TEST(MapTest, InsertionTest) {
  std::map<int, std::string> std_map;
  s21::map<int, std::string> custom_map;

  std_map.insert({1, "one"});
  custom_map.insert({1, "one"});

  ASSERT_EQ(std_map[1], custom_map[1]);
}

TEST(MapTest, EraseTest) {
  std::map<int, std::string> std_map;
  s21::map<int, std::string> custom_map;

  std_map.insert({1, "one"});
  custom_map.insert({1, "one"});

  std_map.erase(1);
  custom_map.erase(custom_map.begin());

  ASSERT_TRUE(std_map.find(1) == std_map.end());
  ASSERT_TRUE(custom_map.cend() == custom_map.cend());
}

TEST(MapTest, SizeTest) {
  std::map<int, std::string> std_map;
  s21::map<int, std::string> custom_map;

  std_map.insert({1, "one"});
  custom_map.insert({1, "one"});

  ASSERT_EQ(std_map.size(), custom_map.size());
}

TEST(MapTest, ClearTest) {
  std::map<int, std::string> std_map;
  s21::map<int, std::string> custom_map;

  std_map.insert({1, "one"});
  custom_map.insert({1, "one"});

  std_map.clear();
  custom_map.clear();

  ASSERT_TRUE(std_map.empty());
  ASSERT_TRUE(custom_map.empty());
}

TEST(MapTest, IteratorTest) {
  std::map<int, std::string> std_map;
  s21::map<int, std::string> custom_map;

  std_map.insert({1, "one"});
  custom_map.insert({1, "one"});

  auto std_it = std_map.begin();
  auto custom_it = custom_map.begin();

  ASSERT_EQ(std_it->first, custom_it->first);
  ASSERT_EQ(std_it->second, custom_it->second);
}

TEST(MapTest, ConstIteratorTest) {
  std::map<int, std::string> std_map;
  s21::map<int, std::string> custom_map;

  std_map.insert({1, "one"});
  custom_map.insert({1, "one"});

  auto std_it = std_map.cbegin();
  auto custom_it = custom_map.cbegin();

  ASSERT_EQ(std_it->first, custom_it->first);
  ASSERT_EQ(std_it->second, custom_it->second);
}

TEST(MapTest, SwapTest) {
  std::map<int, std::string> std_map1, std_map2;
  s21::map<int, std::string> custom_map1, custom_map2;

  std_map1.insert({1, "one"});
  custom_map1.insert({1, "one"});

  std_map2.insert({2, "two"});
  custom_map2.insert({2, "two"});

  std_map1.swap(std_map2);
  custom_map1.swap(custom_map2);

  ASSERT_EQ(std_map1[2], custom_map1[2]);
  ASSERT_EQ(std_map2[1], custom_map2[1]);
}

TEST(MapTest, MergeTest) {
  std::map<int, std::string> std_map1, std_map2;
  s21::map<int, std::string> custom_map1, custom_map2;

  std_map1.insert({1, "one"});
  custom_map1.insert({1, "one"});

  std_map2.insert({2, "two"});
  custom_map2.insert({2, "two"});

  std_map1.merge(std_map2);
  custom_map1.merge(custom_map2);

  ASSERT_EQ(std_map1[2], custom_map1[2]);
  ASSERT_TRUE(std_map2.empty());
  ASSERT_TRUE(custom_map2.empty());
}

TEST(MapTest, AtTest) {
  std::map<int, std::string> std_map;
  s21::map<int, std::string> custom_map;

  std_map.insert({1, "one"});
  custom_map.insert({1, "one"});

  ASSERT_EQ(std_map.at(1), custom_map.at(1));
}

TEST(MapTest, CopyTest) {
  std::map<int, std::string> std_map;
  s21::map<int, std::string> custom_map;

  for (int i = 1; i <= 5; ++i) {
    std_map.insert({i, "value" + std::to_string(i)});
    custom_map.insert({i, "value" + std::to_string(i)});
  }

  auto std_map_copy = std_map;
  auto custom_map_copy = custom_map;

  for (int i = 1; i <= 5; ++i) {
    ASSERT_EQ(std_map_copy[i], custom_map_copy[i]);
  }
}

TEST(MapTest, MoveTest) {
  std::map<int, std::string> std_map;
  s21::map<int, std::string> custom_map;

  for (int i = 1; i <= 5; ++i) {
    std_map.insert({i, "value" + std::to_string(i)});
    custom_map.insert({i, "value" + std::to_string(i)});
  }

  auto std_map_moved = std::move(std_map);
  auto custom_map_moved = std::move(custom_map);

  for (int i = 1; i <= 5; ++i) {
    ASSERT_EQ(std_map_moved[i], custom_map_moved[i]);
  }
}

TEST(MapTest, IteratorTest2) {
  std::map<int, std::string> std_map;
  s21::map<int, std::string> custom_map;

  for (int i = 1; i <= 5; ++i) {
    std_map.insert({i, "value" + std::to_string(i)});
    custom_map.insert({i, "value" + std::to_string(i)});
  }

  auto std_it = std_map.begin();
  auto custom_it = custom_map.begin();

  for (int i = 1; i <= 5; ++i) {
    ASSERT_EQ(std_it->first, custom_it->first);
    ASSERT_EQ(std_it->second, custom_it->second);
    ++std_it;
    ++custom_it;
  }
}

TEST(MapTest, EraseTest2) {
  std::map<int, std::string> std_map;
  s21::map<int, std::string> custom_map;

  for (int i = 1; i <= 5; ++i) {
    std_map.insert({i, "value" + std::to_string(i)});
    custom_map.insert({i, "value" + std::to_string(i)});
  }

  std_map.erase(3);
  custom_map.erase(custom_map.begin());

  ASSERT_TRUE(std_map.find(3) == std_map.end());
  ASSERT_TRUE(custom_map.cend() == custom_map.cend());
}

TEST(MapTest, InsertionTest2) {
  std::map<int, std::string> std_map;
  s21::map<int, std::string> custom_map;

  for (int i = 1; i <= 5; ++i) {
    std_map.insert({i, "value" + std::to_string(i)});
    custom_map.insert({i, "value" + std::to_string(i)});
  }

  for (int i = 1; i <= 5; ++i) {
    ASSERT_EQ(std_map[i], custom_map[i]);
  }
}

TEST(MapTest, MergeTest2) {
  // Инициализация двух map объектов для std и s21 реализаций
  std::map<int, std::string> std_map1;
  s21::map<int, std::string> custom_map1;

  std::map<int, std::string> std_map2;
  s21::map<int, std::string> custom_map2;

  // Заполнение данных
  for (int i = 1; i <= 5; ++i) {
    std_map1.insert({i, "map1_value" + std::to_string(i)});
    custom_map1.insert({i, "map1_value" + std::to_string(i)});
  }

  for (int i = 6; i <= 10; ++i) {
    std_map2.insert({i, "map2_value" + std::to_string(i)});
    custom_map2.insert({i, "map2_value" + std::to_string(i)});
  }

  // Слияние двух map объектов
  std_map1.merge(std_map2);
  custom_map1.merge(custom_map2);

  // Проверка размера после слияния
  ASSERT_EQ(std_map1.size(), custom_map1.size());

  // Проверка, что все элементы были перенесены корректно
  for (int i = 1; i <= 10; ++i) {
    std::string expected_value = i <= 5 ? "map1_value" + std::to_string(i)
                                        : "map2_value" + std::to_string(i);
    ASSERT_EQ(std_map1[i], custom_map1.at(i));
    ASSERT_EQ(std_map1[i], expected_value);
  }

  // Проверка, что исходные map объекты были очищены после слияния
  ASSERT_TRUE(std_map2.empty());
  ASSERT_TRUE(custom_map2.empty());
}

TEST(MapTest, InsertMany_MultiplePairs) {
  s21::map<int, std::string> s21_map;
  std::map<int, std::string> std_map;

  auto s21_results =
      s21_map.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"),
                          std::make_pair(3, "three"));
  std_map.insert({1, "one"});
  std_map.insert({2, "two"});
  std_map.insert({3, "three"});

  ASSERT_EQ(s21_map.size(), std_map.size());
  for (const auto& [it, success] : s21_results) {
    ASSERT_TRUE(success);
    ASSERT_EQ(it->second, std_map[it->first]);
  }
}

TEST(MapTest, InsertMany_DuplicatePairs) {
  s21::map<int, std::string> s21_map;
  s21_map.insert(std::make_pair(1, "one"));

  auto s21_results =
      s21_map.insert_many(std::make_pair(1, "uno"), std::make_pair(2, "two"));

  ASSERT_FALSE(s21_results[0].second);  // The first insertion should fail
  ASSERT_TRUE(s21_results[1].second);   // The second insertion should succeed
}

TEST(MapTest, InsertMany_EmptyMap) {
  s21::map<int, std::string> s21_map;
  auto s21_results = s21_map.insert_many();
  ASSERT_TRUE(s21_results.empty());
}

TEST(MapTest, InsertMany_SinglePair) {
  s21::map<int, std::string> s21_map;
  auto s21_results = s21_map.insert_many(std::make_pair(1, "one"));

  ASSERT_TRUE(s21_results[0].second);
  ASSERT_EQ(s21_results[0].first->second, "one");
}

TEST(MapTest, InsertMany_LargeNumber) {
  s21::map<int, std::string> s21_map;
  auto s21_results = s21_map.insert_many(
      std::make_pair(1, "one"), std::make_pair(2, "two"),
      std::make_pair(3, "three"), std::make_pair(4, "four"),
      std::make_pair(5, "five"), std::make_pair(6, "six"),
      std::make_pair(7, "seven"), std::make_pair(8, "eight"),
      std::make_pair(9, "nine"));

  int i = s21_map.size();
  ASSERT_EQ(i, 9);
  for (const auto& [it, success] : s21_results) {
    ASSERT_TRUE(success);
  }
}

TEST(ConstMapIteratorTest, DereferenceOperator) {
  s21::map<int, std::string> test_map;
  test_map.insert({1, "one"});
  test_map.insert({2, "two"});
  test_map.insert({3, "three"});

  s21::ConstMapIterator<int, std::string> it(test_map.cbegin());
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ((*it).first, 1);

  ++it;
  EXPECT_EQ(it->first, 2);
  EXPECT_EQ((*it).first, 2);
}

TEST(ConstMapIterator, DereferenceInvalidIterator) {
  s21::map<int, std::string> test_map;
  test_map.insert({1, "one"});
  test_map.insert({2, "two"});

  s21::ConstMapIterator<int, std::string> it = test_map.cend();
  EXPECT_THROW(it.operator->(), std::runtime_error);
}

TEST(MapIterator, DecrementOperator) {
  s21::map<int, std::string> test_map;
  test_map.insert({1, "one"});
  test_map.insert({2, "two"});
  test_map.insert({3, "three"});

  s21::MapIterator<int, std::string> it =
      test_map.end();  // установите итератор на конец
  --it;                // уменьшаем его на один

  EXPECT_EQ(
      it->first,
      3);  // после декремента, итератор должен указывать на элемент с ключом 3
}

TEST(MapIterator, EqualityOperator) {
  s21::map<int, std::string> test_map;
  test_map.insert({1, "one"});
  test_map.insert({2, "two"});

  s21::MapIterator<int, std::string> it1 = test_map.begin();
  s21::MapIterator<int, std::string> it2 = test_map.begin();

  EXPECT_TRUE(it1 ==
              it2);  // оба итератора указывают на начало, поэтому они равны

  ++it2;                     // увеличиваем it2 на один
  EXPECT_FALSE(it1 == it2);  // теперь итераторы указывают на разные элементы,
                             // поэтому они не равны
}

TEST(Map, InsertOrAssign_NewPair) {
  s21::map<int, std::string> test_map;

  // Пытаемся добавить новую пару ключ-значение
  auto result = test_map.insert_or_assign(1, "one");

  // Проверяем, что вставка прошла успешно
  EXPECT_TRUE(result.second);
  EXPECT_EQ(result.first->first, 1);
  EXPECT_EQ(result.first->second, "one");
}

TEST(Map, InsertOrAssign_ReplaceValue) {
  s21::map<int, std::string> test_map;

  test_map.insert({1, "one"});

  // Пытаемся заменить значение для существующего ключа
  auto result = test_map.insert_or_assign(1, "uno");

  // Проверяем, что вставка прошла успешно, но значение было заменено
  EXPECT_FALSE(result.second);
  EXPECT_EQ(result.first->first, 1);
  EXPECT_EQ(result.first->second, "uno");
}

TEST(Map, Contains_ExistingKey) {
  s21::map<int, std::string> test_map;

  test_map.insert({1, "one"});

  // Проверяем, что ключ присутствует в map
  EXPECT_TRUE(test_map.contains(1));
}

TEST(Map, Contains_NonExistingKey) {
  s21::map<int, std::string> test_map;

  test_map.insert({1, "one"});

  // Проверяем, что ключа нет в map
  EXPECT_FALSE(test_map.contains(2));
}

TEST(Map, MoveAssignment_Operator) {
  s21::map<int, std::string> source_map;
  source_map.insert({1, "one"});
  source_map.insert({2, "two"});

  s21::map<int, std::string> dest_map;

  dest_map = std::move(source_map);

  // Проверяем, что значения были правильно перемещены
  EXPECT_EQ(dest_map.size(), 2UL);
  EXPECT_TRUE(dest_map.contains(1));
  EXPECT_TRUE(dest_map.contains(2));

  // Проверяем, что исходная карта теперь пуста
  EXPECT_TRUE(source_map.empty());
}

TEST(MapTest, InitializerListConstructorTest) {
  s21::map<int, std::string> myMap{{1, "one"}, {2, "two"}, {3, "three"}};

  // Проверка размера
  EXPECT_EQ(myMap.size(), 3UL);

  // Проверка элементов
  EXPECT_EQ(myMap[1], "one");
  EXPECT_EQ(myMap[2], "two");
  EXPECT_EQ(myMap[3], "three");

  // Проверка, что элементы действительно были добавлены
  EXPECT_TRUE(myMap.contains(1));
  EXPECT_TRUE(myMap.contains(2));
  EXPECT_TRUE(myMap.contains(3));

  // Проверка отсутствующего ключа
  EXPECT_FALSE(myMap.contains(4));
}

TEST(MapTest, InsertKeyValueTest) {
  s21::map<int, std::string> myMap;

  // Вставка элемента
  auto [it, inserted] = myMap.insert(1, "one");

  // Проверка успешной вставки
  EXPECT_TRUE(inserted);

  // Проверка значения вставленного элемента
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, "one");

  // Повторная вставка с тем же ключом
  auto [it2, inserted2] = myMap.insert(1, "duplicate");

  // Проверка неуспешной вставки
  EXPECT_FALSE(inserted2);

  // Значение не должно было измениться после попытки повторной вставки
  EXPECT_EQ(myMap[1], "one");
}

TEST(MapTest, ConstMapIteratorDecrementTest) {
  s21::map<int, std::string> myMap;

  myMap.insert(1, "one");
  myMap.insert(2, "two");
  myMap.insert(3, "three");

  // Получение константного итератора к концу map
  s21::ConstMapIterator<int, std::string> it = myMap.cend();
  --it;  // Декремент до последнего элемента

  // Проверка значения последнего элемента
  EXPECT_EQ(it->first, 3);
  EXPECT_EQ(it->second, "three");

  --it;  // Декремент к предыдущему элементу

  // Проверка значения предыдущего элемента
  EXPECT_EQ(it->first, 2);
  EXPECT_EQ(it->second, "two");

  --it;  // Декремент к первому элементу

  // Проверка значения первого элемента
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, "one");
}

TEST(ConstMapIteratorTest, NotEqualOperatorTest) {
  s21::map<int, std::string> test_map;
  test_map.insert({1, "one"});
  test_map.insert({2, "two"});
  test_map.insert({3, "three"});

  auto it1 = test_map.cbegin();
  auto it2 = test_map.cbegin();
  ++it2;  // Перемещаем итератор на следующий элемент

  // Проверка, что разные итераторы действительно различны
  EXPECT_TRUE(it1 != it2);

  // Проверка, что итераторы, указывающие на один и тот же элемент, не различны
  ++it1;
  EXPECT_FALSE(it1 != it2);
}
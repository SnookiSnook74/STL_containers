#include "s21_array.h"

#include <gtest/gtest.h>

#include <array>
TEST(Array, test_1) {
  s21::array<int, 5> arr_s21;
  std::array<int, 5> arr_std;
  EXPECT_EQ(arr_s21.size(), arr_std.size());
  EXPECT_EQ(arr_s21.max_size(), arr_std.max_size());
  EXPECT_EQ(arr_s21.empty(), arr_std.empty());
}

TEST(Array, test_2) {
  s21::array<int, 5> arr_s21{1, 2, 3, 4, 5};
  std::array<int, 5> arr_std{1, 2, 3, 4, 5};
  EXPECT_EQ(arr_s21.size(), arr_std.size());
  EXPECT_EQ(arr_s21.max_size(), arr_std.max_size());
  EXPECT_EQ(arr_s21.empty(), arr_std.empty());
  for (size_t i = 0; i < arr_s21.size(); i++) {
    EXPECT_EQ(arr_s21.at(i), arr_std.at(i));
  }
  // проверяем что метод at() выбрасывает ошибку при обращении за пределы
  // массива
  EXPECT_THROW(
      try { arr_s21.at(1000); } catch (const std::out_of_range& e) { throw; },
      std::out_of_range);
  EXPECT_THROW(
      try { arr_std.at(1000); } catch (const std::out_of_range& e) { throw; },
      std::out_of_range);
}

TEST(Array, test_3) {
  s21::array<int, 5> arr_1{1, 2, 3, 4, 5};
  s21::array<int, 5> arr_2(arr_1);
  for (size_t i = 0; i < arr_1.size(); i++) {
    EXPECT_EQ(arr_1.at(i), arr_2.at(i));
  }
}

TEST(Array, test_4) {
  s21::array<int, 5> arr_1{1, 2, 3, 4, 5};
  s21::array<int, 5> arr_2{6, 7, 8, 9, 10};
  arr_2 = std::move(arr_1);
  for (size_t i = 0; i < arr_1.size(); i++) {
    EXPECT_EQ(arr_1.at(i), arr_2.at(i));
  }
}

TEST(Array, test_5) {
  s21::array<int, 5> arr_1{1, 2, 3, 4, 5};
  s21::array<int, 5> arr_2(std::move(arr_1));
  for (size_t i = 0; i < arr_1.size(); i++) {
    EXPECT_EQ(arr_1.at(i), arr_2.at(i));
  }
}

TEST(Array, test_6) {
  s21::array<int, 5> arr_1{1, 2, 3, 4, 5};
  s21::array<int, 5> arr_2{1, 2, 3, 4, 5};
  for (size_t i = 0; i < arr_1.size(); i++) {
    EXPECT_EQ(arr_1[i], arr_2[i]);
  }
}

TEST(Array, test_7) {
  s21::array<int, 5> arr_1{1, 2, 3, 4, 5};
  std::array<int, 5> arr_2{1, 2, 3, 4, 5};
  EXPECT_EQ(arr_1.front(), arr_2.front());
}

TEST(Array, test_8) {
  s21::array<int, 5> arr_1{1, 2, 3, 4, 5};
  std::array<int, 5> arr_2{1, 2, 3, 4, 5};
  EXPECT_EQ(arr_1.back(), arr_2.back());
}

TEST(Array, test_9) {
  s21::array<int, 5> arr_1{1, 2, 3, 4, 5};
  std::array<int, 5> arr_2{1, 2, 3, 4, 5};
  for (size_t i = 0; i < arr_1.size(); i++) {
    EXPECT_EQ(arr_1.data()[i], arr_2.data()[i]);
  }
}

TEST(Array, test_10) {
  s21::array<int, 5> arr_1{1, 2, 3, 4, 5};
  std::array<int, 5> arr_2{1, 2, 3, 4, 5};
  for (size_t i = 0; i < arr_1.size(); i++) {
    EXPECT_EQ(*(arr_1.begin() + i), *(arr_2.begin() + i));
  }
}

TEST(Array, test_11) {
  s21::array<int, 5> arr_1{1, 2, 3, 4, 5};
  std::array<int, 5> arr_2{1, 2, 3, 4, 5};
  for (size_t i = 1; i <= arr_1.size(); i++) {
    EXPECT_EQ(*(arr_1.end() - i), *(arr_2.end() - i));
  }
}

TEST(Array, test_12) {
  s21::array<int, 5> arr_1;
  arr_1.fill(123);
  for (size_t i = 0; i < arr_1.size(); i++) {
    EXPECT_EQ(arr_1[i], 123);
  }
}

TEST(Array, test_13) {
  s21::array<int, 5> arr_1{1, 2, 3, 4, 5};
  s21::array<int, 5> arr_2{6, 7, 8, 9, 10};
  arr_2.swap(arr_1);
  EXPECT_EQ(arr_1[0], 6);
  EXPECT_EQ(arr_1[1], 7);
  EXPECT_EQ(arr_1[2], 8);
  EXPECT_EQ(arr_1[3], 9);
  EXPECT_EQ(arr_1[4], 10);

  EXPECT_EQ(arr_2[0], 1);
  EXPECT_EQ(arr_2[1], 2);
  EXPECT_EQ(arr_2[2], 3);
  EXPECT_EQ(arr_2[3], 4);
  EXPECT_EQ(arr_2[4], 5);
}
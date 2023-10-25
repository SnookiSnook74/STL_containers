#include "s21_vector.h"

#include <gtest/gtest.h>

TEST(vector, Constructor_Default) {
  //создаем два объекта конструктором по умолчанию
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;
  // проверяем что данные объектов идентичны
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  EXPECT_EQ(s21_vector.max_size(), 4611686018427387903UL);
  //добавляем по одному значению
  s21_vector.push_back(1);
  std_vector.push_back(1);
  // проверяем что данные объектов идентичны
  EXPECT_EQ(s21_vector[0], std_vector[0]);
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  //добавляем по сто значений
  for (int i = 0; i < 100; ++i) {
    s21_vector.push_back(i);
    std_vector.push_back(i);
  }
  // проверяем что данные объектов идентичны
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector.at(i), std_vector.at(i));
  }
  //проверка работы метода shrink_to_fit
  s21_vector.shrink_to_fit();
  std_vector.shrink_to_fit();
  // проверяем что данные объектов идентичны
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  // проверяем что метод at() выбрасывает ошибку при обращении за пределы
  // массива
  EXPECT_THROW(
      try { s21_vector.at(1000); } catch (const std::out_of_range& e) {
        throw;
      },
      std::out_of_range);
  EXPECT_THROW(
      try { std_vector.at(1000); } catch (const std::out_of_range& e) {
        throw;
      },
      std::out_of_range);
  //проверяем что методы front back работают аналогично оригиналу.
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());
}

TEST(vector, Constructor_size) {
  // вызываем коснтруктора с одним параметром - размер
  s21::vector<int> s21_vector(5);
  std::vector<int> std_vector(5);
  // проверяем что данные объектов идентичны
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  //добавляем по 15 значений
  for (int i = 0; i < 15; ++i) {
    s21_vector.push_back(i);
    std_vector.push_back(i);
  }
  // проверяем что данные объектов идентичны
  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector.data()[i], std_vector.data()[i]);
  }
  //вставляем данные в середину списков
  s21_vector.insert(s21_vector.begin() + 1, 12);
  std_vector.insert(std_vector.begin() + 1, 12);

  s21_vector.insert(s21_vector.begin() + 8, 14);
  std_vector.insert(std_vector.begin() + 8, 14);

  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector.data()[i], std_vector.data()[i]);
  }
  // проверяем что данные объектов идентичны
  EXPECT_EQ(*s21_vector.begin(), *std_vector.begin());
  EXPECT_EQ(*(s21_vector.end() - 1), *(std_vector.end() - 1));
  //удаляем по одному элементу с конца списков
  s21_vector.pop_back();
  std_vector.pop_back();
  // проверяем что данные объектов идентичны
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector.data()[i], std_vector.data()[i]);
  }
  //удаляем по одному элементу из середины списков
  s21_vector.erase(s21_vector.begin() + 1);
  std_vector.erase(std_vector.begin() + 1);
  // проверяем что данные объектов идентичны
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector.data()[i], std_vector.data()[i]);
  }
  //удаляем все данные списков
  s21_vector.clear();
  std_vector.clear();
  // проверяем что данные объектов идентичны
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
}

TEST(vector, Constructor_initializer) {
  //конструктор с использованием initializer_list
  s21::vector<int> s21_vector{1, 2, 3, 4, 5};
  std::vector<int> std_vector{1, 2, 3, 4, 5};
  // проверяем что данные объектов идентичны
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
  EXPECT_EQ(s21_vector.capacity(), std_vector.capacity());
  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector.data()[i], std_vector.data()[i]);
  }
}

TEST(vector, Constructor_copy) {
  //проверка конструктора копирования
  s21::vector<int> s21_vector{1, 2, 3, 4, 5};
  std::vector<int> std_vector{1, 2, 3, 4, 5};
  //копируем
  s21::vector<int> s21_vector_copy(s21_vector);
  std::vector<int> std_vector_copy(std_vector);
  // проверяем что данные объектов идентичны
  EXPECT_EQ(s21_vector_copy.size(), std_vector_copy.size());
  EXPECT_EQ(s21_vector_copy.empty(), std_vector_copy.empty());
  EXPECT_EQ(s21_vector_copy.capacity(), std_vector_copy.capacity());
  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector_copy.data()[i], std_vector_copy.data()[i]);
  }
}

TEST(vector, Constructor_move) {
  //проверка конструктора перемещения
  s21::vector<int> s21_vector{1, 2, 3, 4, 5};
  std::vector<int> std_vector{1, 2, 3, 4, 5};
  s21::vector<int> s21_vector_copy(std::move(s21_vector));
  std::vector<int> std_vector_copy(std::move(std_vector));
  // проверяем что данные объектов идентичны
  EXPECT_EQ(s21_vector_copy.size(), std_vector_copy.size());
  EXPECT_EQ(s21_vector_copy.empty(), std_vector_copy.empty());
  EXPECT_EQ(s21_vector_copy.capacity(), std_vector_copy.capacity());
  for (size_t i = 0; i < s21_vector.size(); ++i) {
    EXPECT_EQ(s21_vector_copy.data()[i], std_vector_copy.data()[i]);
  }
}

TEST(vector, Constructor_operator_overload) {
  // Создаем два объекта vector
  s21::vector<int> vector1{1, 2, 3};
  s21::vector<int> vector2{4, 5, 6};

  // Используем оператор перемещения для присваивания vector2 объекту vector1
  vector1 = std::move(vector2);

  //присваивание самого себя(покрытие)
  // vector1 = std::move(vector1);

  // Проверяем, что vector1 теперь содержит данные из vector2
  EXPECT_EQ(vector1.size(), 3UL);
  EXPECT_EQ(vector1[0], 4);
  EXPECT_EQ(vector1[1], 5);
  EXPECT_EQ(vector1[2], 6);

  // Проверяем, что vector2 больше не содержит данных
  EXPECT_EQ(vector2.size(), 0UL);
  EXPECT_EQ(vector2.empty(), true);
}

TEST(vector, Constructor_swap) {
  // Создаем два объекта vector
  s21::vector<int> vector1{1, 2, 3};
  s21::vector<int> vector2{4, 5, 6};
  //проверяем работу функции swap
  vector1.swap(vector2);

  EXPECT_EQ(vector1[0], 4);
  EXPECT_EQ(vector1[1], 5);
  EXPECT_EQ(vector1[2], 6);

  EXPECT_EQ(vector2[0], 1);
  EXPECT_EQ(vector2[1], 2);
  EXPECT_EQ(vector2[2], 3);
}

TEST(vector, insert_many) {
  s21::vector<int> v1{1, 2, 3};
  v1.insert_many(v1.cbegin() + 2, 6, 7, 8);
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(v1[2], 6);
  EXPECT_EQ(v1[3], 7);
  EXPECT_EQ(v1[4], 8);
  EXPECT_EQ(v1[5], 3);
}

TEST(vector, insert_many_back) {
  s21::vector<int> v1{1, 2, 3};
  v1.insert_many_back(6, 7, 8);
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(v1[2], 3);
  EXPECT_EQ(v1[3], 6);
  EXPECT_EQ(v1[4], 7);
  EXPECT_EQ(v1[5], 8);
}
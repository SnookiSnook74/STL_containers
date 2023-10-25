#include <gtest/gtest.h>

#include <queue>

#include "../../s21_containers.h"

TEST(QueueTest, PushPop) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;

  s21_queue.push(1);
  std_queue.push(1);

  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.size(), std_queue.size());

  s21_queue.pop();
  std_queue.pop();

  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(QueueTest, InitializerListConstructor) {
  s21::queue<int> s21_queue{1, 2, 3};
  std::queue<int> std_queue({1, 2, 3});

  EXPECT_EQ(s21_queue.size(), std_queue.size());
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> s21_original{1, 2, 3};
  std::queue<int> std_original({1, 2, 3});

  s21::queue<int> s21_copy(s21_original);
  std::queue<int> std_copy(std_original);

  EXPECT_EQ(s21_copy.size(), std_copy.size());
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> s21_original{1, 2, 3};
  s21::queue<int> s21_moved(std::move(s21_original));

  EXPECT_EQ(s21_moved.size(), 3u);
  EXPECT_EQ(s21_original.empty(), true);
}

TEST(QueueTest, FrontBack) {
  s21::queue<int> s21_queue{1, 2, 3};
  std::queue<int> std_queue({1, 2, 3});

  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
}

TEST(QueueTest, Empty) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;

  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(QueueTest, Size) {
  s21::queue<int> s21_queue{1, 2, 3};
  std::queue<int> std_queue({1, 2, 3});

  EXPECT_EQ(s21_queue.size(), std_queue.size());
}

TEST(QueueTest, AssignmentOperator) {
  s21::queue<int> s21_queue1{1, 2, 3};
  s21::queue<int> s21_queue2;

  s21_queue2 = s21_queue1;

  EXPECT_EQ(s21_queue1.size(), s21_queue2.size());
}

TEST(QueueTest, MoveAssignmentOperator) {
  s21::queue<int> s21_queue1{1, 2, 3};
  s21::queue<int> s21_queue2;

  s21_queue2 = std::move(s21_queue1);

  EXPECT_EQ(s21_queue2.size(), 3u);
  EXPECT_EQ(s21_queue1.empty(), true);
}

TEST(QueueTest, Swap) {
  s21::queue<int> s21_queue1{1, 2, 3};
  s21::queue<int> s21_queue2{4, 5};

  s21_queue1.swap(s21_queue2);

  EXPECT_EQ(s21_queue1.size(), 2u);
  EXPECT_EQ(s21_queue2.size(), 3u);
}

TEST(QueueTest, PopEmptyQueue) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;

  EXPECT_THROW(s21_queue.pop(), std::out_of_range);
  // Для std::queue не нужно тестировать, так как поведение не определено
}

TEST(QueueTest, FrontAfterPush) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;

  s21_queue.push(42);
  std_queue.push(42);

  EXPECT_EQ(s21_queue.front(), std_queue.front());
}

TEST(QueueTest, BackAfterPush) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;

  s21_queue.push(42);
  std_queue.push(42);

  EXPECT_EQ(s21_queue.back(), std_queue.back());
}

TEST(QueueTest, FrontAfterMultiplePush) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;

  s21_queue.push(1);
  s21_queue.push(2);
  std_queue.push(1);
  std_queue.push(2);

  EXPECT_EQ(s21_queue.front(), std_queue.front());
}

TEST(QueueTest, BackAfterMultiplePush) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;

  s21_queue.push(1);
  s21_queue.push(2);
  std_queue.push(1);
  std_queue.push(2);

  EXPECT_EQ(s21_queue.back(), std_queue.back());
}

TEST(QueueTest, FrontAfterPop) {
  s21::queue<int> s21_queue{1, 2, 3};
  std::queue<int> std_queue({1, 2, 3});

  s21_queue.pop();
  std_queue.pop();

  EXPECT_EQ(s21_queue.front(), std_queue.front());
}

TEST(QueueTest, BackAfterPop) {
  s21::queue<int> s21_queue{1, 2, 3};
  std::queue<int> std_queue({1, 2, 3});

  s21_queue.pop();
  std_queue.pop();

  EXPECT_EQ(s21_queue.back(), std_queue.back());
}

TEST(QueueTest, SizeAfterClear) {
  s21::queue<int> s21_queue{1, 2, 3};
  std::queue<int> std_queue({1, 2, 3});

  while (!s21_queue.empty()) {
    s21_queue.pop();
  }
  while (!std_queue.empty()) {
    std_queue.pop();
  }

  EXPECT_EQ(s21_queue.size(), std_queue.size());
}

TEST(QueueTest, FrontAfterSwap) {
  s21::queue<int> s21_queue1{1, 2, 3};
  s21::queue<int> s21_queue2{4, 5, 6};
  std::queue<int> std_queue1({1, 2, 3});
  std::queue<int> std_queue2({4, 5, 6});

  s21_queue1.swap(s21_queue2);
  std::swap(std_queue1, std_queue2);

  EXPECT_EQ(s21_queue1.front(), std_queue1.front());
  EXPECT_EQ(s21_queue2.front(), std_queue2.front());
}

TEST(QueueTest, BackAfterSwap) {
  s21::queue<int> s21_queue1{1, 2, 3};
  s21::queue<int> s21_queue2{4, 5, 6};
  std::queue<int> std_queue1({1, 2, 3});
  std::queue<int> std_queue2({4, 5, 6});

  s21_queue1.swap(s21_queue2);
  std::swap(std_queue1, std_queue2);

  EXPECT_EQ(s21_queue1.back(), std_queue1.back());
  EXPECT_EQ(s21_queue2.back(), std_queue2.back());
}

TEST(QueueTest, InsertManyBack_Single) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;

  s21_queue.insert_many_back(5);
  std_queue.push(5);

  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue.size(), std_queue.size());
}

TEST(QueueTest, InsertManyBack_Multiple) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;

  s21_queue.insert_many_back(1, 2, 3, 4);
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std_queue.push(4);

  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue.size(), std_queue.size());
}

TEST(QueueTest, InsertManyBack_Mix) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;

  s21_queue.push(0);
  std_queue.push(0);

  s21_queue.insert_many_back(1, 2);
  std_queue.push(1);
  std_queue.push(2);

  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue.size(), std_queue.size());
}

TEST(QueueTest, InsertManyBack_Empty) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;

  s21_queue.insert_many_back();
  // для std_queue ничего не делаем, так как добавлять нечего

  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(QueueTest, InsertManyBack_Large) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;

  s21_queue.insert_many_back(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  for (int i = 1; i <= 10; ++i) {
    std_queue.push(i);
  }

  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
  EXPECT_EQ(s21_queue.size(), std_queue.size());
}

TEST(QueueTest, FrontTest) {
  s21::queue<int> myQueue;

  // Добавление элементов в очередь
  myQueue.push(1);
  myQueue.push(2);
  myQueue.push(3);

  // Проверка значения первого элемента
  EXPECT_EQ(myQueue.front(), 1);

  // Удаление элемента из очереди и проверка нового первого элемента
  myQueue.pop();
  EXPECT_EQ(myQueue.front(), 2);
}

TEST(QueueTest, FrontTest3) {
  s21::queue<int> test_queue;
  test_queue.push(1);
  test_queue.push(2);
  test_queue.push(3);

  EXPECT_EQ(test_queue.front(), 1);
  test_queue.pop();
  EXPECT_EQ(test_queue.front(), 2);
}

TEST(QueueTest, BackTest3) {
  s21::queue<int> test_queue;
  test_queue.push(1);
  EXPECT_EQ(test_queue.back(), 1);

  test_queue.push(2);
  EXPECT_EQ(test_queue.back(), 2);

  test_queue.push(3);
  EXPECT_EQ(test_queue.back(), 3);
}
#include <gtest/gtest.h>

#include <stack>

#include "../../s21_containers.h"

TEST(StackTest, PushPop) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  s21_stack.push(1);
  std_stack.push(1);

  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());

  s21_stack.pop();
  std_stack.pop();

  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(StackTest, InitializerListConstructor) {
  s21::stack<int> s21_stack{1, 2, 3};
  std::stack<int> std_stack({1, 2, 3});

  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(StackTest, CopyConstructor) {
  s21::stack<int> s21_original{1, 2, 3};
  std::stack<int> std_original({1, 2, 3});

  s21::stack<int> s21_copy(s21_original);
  std::stack<int> std_copy(std_original);

  EXPECT_EQ(s21_copy.size(), std_copy.size());
}

TEST(StackTest, MoveConstructor) {
  s21::stack<int> s21_stack{1, 2, 3};
  std::stack<int> std_stack({1, 2, 3});

  s21::stack<int> s21_moved(std::move(s21_stack));
  std::stack<int> std_moved(std::move(std_stack));

  EXPECT_EQ(s21_moved.size(), std_moved.size());
}

TEST(StackTest, Top) {
  s21::stack<int> s21_stack{1, 2, 3};
  std::stack<int> std_stack({1, 2, 3});

  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(StackTest, Empty) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  EXPECT_EQ(s21_stack.empty(), std_stack.empty());

  s21_stack.push(1);
  std_stack.push(1);

  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(StackTest, Size) {
  s21::stack<int> s21_stack{1, 2, 3};
  std::stack<int> std_stack({1, 2, 3});

  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(StackTest, Swap) {
  s21::stack<int> s21_stack1{1, 2, 3};
  s21::stack<int> s21_stack2{4, 5};
  std::stack<int> std_stack1({1, 2, 3});
  std::stack<int> std_stack2({4, 5});

  s21_stack1.swap(s21_stack2);
  std::swap(std_stack1, std_stack2);

  EXPECT_EQ(s21_stack1.size(), std_stack1.size());
  EXPECT_EQ(s21_stack2.size(), std_stack2.size());
}

TEST(StackTest, PushMultipleElements) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  for (int i = 0; i < 10; ++i) {
    s21_stack.push(i);
    std_stack.push(i);
  }

  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(StackTest, PopMultipleElements) {
  s21::stack<int> s21_stack{1, 2, 3, 4, 5};
  std::stack<int> std_stack({1, 2, 3, 4, 5});

  for (int i = 0; i < 3; ++i) {
    s21_stack.pop();
    std_stack.pop();
  }

  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(StackTest, CheckTopAfterPop) {
  s21::stack<int> s21_stack{1, 2, 3, 4, 5};
  std::stack<int> std_stack({1, 2, 3, 4, 5});

  s21_stack.pop();
  std_stack.pop();

  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(StackTest, MoveAssignment) {
  s21::stack<int> s21_stack1{1, 2, 3};
  s21::stack<int> s21_stack2;

  std::stack<int> std_stack1({1, 2, 3});
  std::stack<int> std_stack2;

  s21_stack2 = std::move(s21_stack1);
  std_stack2 = std::move(std_stack1);

  EXPECT_EQ(s21_stack2.size(), std_stack2.size());
}

TEST(StackTest, PopEmptyStack) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  EXPECT_THROW(s21_stack.pop(), std::out_of_range);
}

TEST(StackTest, TopEmptyStack) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  EXPECT_THROW(s21_stack.top(), std::out_of_range);
}

TEST(StackTest, SwapEmptyStacks) {
  s21::stack<int> s21_stack1;
  s21::stack<int> s21_stack2;

  std::stack<int> std_stack1;
  std::stack<int> std_stack2;

  s21_stack1.swap(s21_stack2);
  std::swap(std_stack1, std_stack2);

  EXPECT_EQ(s21_stack1.empty(), std_stack1.empty());
  EXPECT_EQ(s21_stack2.empty(), std_stack2.empty());
}

TEST(StackTest, SwapMixedStacks) {
  s21::stack<int> s21_stack1{1, 2, 3};
  s21::stack<int> s21_stack2;

  std::stack<int> std_stack1({1, 2, 3});
  std::stack<int> std_stack2;

  s21_stack1.swap(s21_stack2);
  std::swap(std_stack1, std_stack2);

  EXPECT_EQ(s21_stack1.size(), std_stack1.size());
  EXPECT_EQ(s21_stack2.size(), std_stack2.size());
}

TEST(StackTest, CopyEmptyStack) {
  s21::stack<int> s21_stack1;
  std::stack<int> std_stack1;

  s21::stack<int> s21_stack2(s21_stack1);
  std::stack<int> std_stack2(std_stack1);

  EXPECT_EQ(s21_stack2.empty(), std_stack2.empty());
}

TEST(StackTest, CopyAssignment) {
  s21::stack<int> s21_stack1{1, 2, 3};
  s21::stack<int> s21_stack2;

  std::stack<int> std_stack1({1, 2, 3});
  std::stack<int> std_stack2;

  s21_stack2 = s21_stack1;
  std_stack2 = std_stack1;

  EXPECT_EQ(s21_stack2.size(), std_stack2.size());
}

TEST(StackTest, InsertManyFront_OneElement) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  s21_stack.insert_many_front(5);
  std_stack.push(5);

  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(StackTest, InsertManyFront_MultipleElements) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  s21_stack.insert_many_front(1, 2, 3);
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);

  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(StackTest, InsertManyFront_AfterPush) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  s21_stack.push(10);
  std_stack.push(10);

  s21_stack.insert_many_front(5, 6, 7);
  std_stack.push(5);
  std_stack.push(6);
  std_stack.push(7);

  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

TEST(StackTest, InsertManyFront_EmptyStack) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  s21_stack.insert_many_front();
  // Ничего не добавляем в std_stack, так как insert_many_front вызывается без
  // аргументов.

  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(StackTest, InsertManyFront_ComplexSequence) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;

  s21_stack.push(10);
  std_stack.push(10);

  s21_stack.insert_many_front(5, 6);
  std_stack.push(5);
  std_stack.push(6);

  s21_stack.push(11);
  std_stack.push(11);

  s21_stack.insert_many_front(7, 8, 9);
  std_stack.push(7);
  std_stack.push(8);
  std_stack.push(9);

  EXPECT_EQ(s21_stack.top(), std_stack.top());
  EXPECT_EQ(s21_stack.size(), std_stack.size());
}

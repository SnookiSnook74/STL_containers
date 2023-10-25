#include <gtest/gtest.h>

#include "redblacktree.h"

// Функция для проверки свойст красно-черного дерева
bool checkRedBlackProperties(s21::RedBlackTree<int>::NodePtr node,
                             int& blackCount, const int pathBlackCount) {
  if (!node) {
    // Свойство 2 и 4 (Все листья (nullptr узлы) черные.
    //Каждый простой путь от данного узла до любого из его потомков-листьев
    //имеет одинаковое количество черных узлов.)
    if (blackCount == -1) {
      blackCount = pathBlackCount;
    } else if (blackCount != pathBlackCount) {
      return false;
    }
    return true;
  }
  // Свойство 1 (Корень дерева всегда черный.)
  if (!node->parent.lock() &&
      node->color != s21::RedBlackTree<int>::Color::BLACK) {
    return false;
  }
  // Свойство 3 (Если узел красный, то оба его потомка черные.)
  if (node->color == s21::RedBlackTree<int>::Color::RED) {
    if ((node->left &&
         node->left->color != s21::RedBlackTree<int>::Color::BLACK) ||
        (node->right &&
         node->right->color != s21::RedBlackTree<int>::Color::BLACK)) {
      return false;
    }
  }
  int newBlackCount =
      pathBlackCount +
      (node->color == s21::RedBlackTree<int>::Color::BLACK ? 1 : 0);
  return checkRedBlackProperties(node->left, blackCount, newBlackCount) &&
         checkRedBlackProperties(node->right, blackCount, newBlackCount);
}

TEST(RedBlackTreeTest, InsertSingleElement) {
  s21::RedBlackTree<int> tree;
  tree.insert(5);
  // Проверка наличия элемента
  ASSERT_NE(tree.find(5), nullptr);
}

// ВЫЛЕТАЕТ СЕГА!
TEST(RedBlackTreeTest, InsertMultipleElements) {
  s21::RedBlackTree<int> tree;
  tree.insert(40);
  tree.insert(1);
  tree.insert(2);
  // Проверки наличия элементов
  ASSERT_NE(tree.find(40), nullptr);
  ASSERT_NE(tree.find(1), nullptr);
  ASSERT_NE(tree.find(2), nullptr);
}

TEST(RedBlackTreeTest, EraseElement) {
  s21::RedBlackTree<int> tree;
  tree.insert(5);
  tree.erase(5);
  // Проверка отсутствия элемента
  ASSERT_EQ(tree.find(5), nullptr);
}

TEST(RedBlackTreeTest, EraseNonExistentElement) {
  s21::RedBlackTree<int> tree;
  tree.insert(5);
  tree.erase(3);
  // Проверка наличия элемента
  ASSERT_NE(tree.find(5), nullptr);
}

TEST(RedBlackTreeTest, FindElement) {
  s21::RedBlackTree<int> tree;
  tree.insert(5);
  // Проверка наличия элемента
  ASSERT_NE(tree.find(5), nullptr);
}

TEST(RedBlackTreeTest, FindNonExistentElement) {
  s21::RedBlackTree<int> tree;
  // Проверка отсутствия элемента
  ASSERT_EQ(tree.find(5), nullptr);
}

TEST(RedBlackTreeTest, TestStress) {
  s21::RedBlackTree<int> tree;
  for (int i = 0; i < 1000; ++i) {
    tree.insert(i);
  }
  int blackCount = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCount, 0));
}

TEST(RedBlackTreeTest_2, TestStress_2) {
  s21::RedBlackTree<int> tree;
  for (int i = 0; i < 1000; ++i) {
    tree.insert(i / 2);
  }
  int blackCount = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCount, 0));
}

TEST(RedBlackTreeTest, ValidateRedBlackProperties) {
  s21::RedBlackTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(7);
  tree.insert(2);
  tree.insert(4);
  tree.insert(6);
  tree.insert(8);

  int blackCount = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCount, 0));
}

TEST(RedBlackTreeTest, ValidateRedBlackPropertiesAfterDeletion) {
  s21::RedBlackTree<int> tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(7);
  tree.insert(2);
  tree.insert(4);
  tree.insert(6);
  tree.insert(8);

  // Проверка свойств после вставки
  int blackCountInsert = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCountInsert, 0));

  // Удаление элемента
  tree.erase(4);

  // Проверка свойств после удаления
  int blackCountErase = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCountErase, 0));
}

TEST(RedBlackTreeTest, DeleteLeafNode) {
  s21::RedBlackTree<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);

  int blackCountBefore = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCountBefore, 0));

  tree.erase(5);

  int blackCountAfter = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCountAfter, 0));
}

TEST(RedBlackTreeTest, DeleteNodeWithOneChild) {
  s21::RedBlackTree<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);

  int blackCountBefore = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCountBefore, 0));

  tree.erase(5);

  int blackCountAfter = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCountAfter, 0));
}

TEST(RedBlackTreeTest, DeleteNodeWithTwoChildren) {
  s21::RedBlackTree<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);

  int blackCountBefore = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCountBefore, 0));

  tree.erase(5);

  int blackCountAfter = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCountAfter, 0));
}

TEST(RedBlackTreeTest, DeleteRootNode) {
  s21::RedBlackTree<int> tree;
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);

  int blackCountBefore = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCountBefore, 0));

  tree.erase(10);

  int blackCountAfter = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCountAfter, 0));
}

TEST(RedBlackTreeTest, EraseFixup_RedSibling_RightChild) {
  s21::RedBlackTree<int> tree;
  // Создание сценария, где удаляемый узел - это правый потомок, а его брат
  // красный.
  tree.insert(5);
  tree.insert(1);
  tree.insert(15);
  tree.insert(7);
  tree.insert(20);

  // Удаление узла
  tree.erase(15);

  int blackCount = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCount, 0));
}

TEST(RedBlackTreeTest, EraseFixup_BlackSiblingAndChildren_LeftChild) {
  s21::RedBlackTree<int> tree;
  // Создание сценария, где удаляемый узел, его брат и оба потомка брата черные.
  tree.insert(5);
  tree.insert(2);
  tree.insert(8);
  tree.insert(1);
  tree.insert(4);
  tree.insert(7);
  tree.insert(10);

  // Удаление узла
  tree.erase(2);

  int blackCount = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCount, 0));
}

TEST(RedBlackTreeTest, EraseFixup_RightChild_BlackSibling_RedLeftChild) {
  s21::RedBlackTree<int> tree;
  // Создаем сценарий, где удаляемый узел с черным братом, у которого только
  // левый потомок красный.
  tree.insert(5);
  tree.insert(10);
  tree.insert(1);
  tree.insert(7);
  tree.insert(12);
  tree.insert(6);
  tree.insert(15);

  // Удаляем узел
  tree.erase(15);

  int blackCount = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCount, 0));
}

TEST(RedBlackTreeTest, EraseFixup_RightChildScenario) {
  s21::RedBlackTree<int> tree;

  tree.insert(10);
  tree.insert(5);
  tree.insert(20);
  tree.insert(15);
  tree.insert(25);
  tree.insert(12);
  tree.insert(18);

  // Здесь удаляем узел так, чтобы `x` стал правым потомком
  tree.erase(12);

  // Проверяем свойства красно-черного дерева
  int blackCount = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCount, 0));
}

TEST(RedBlackTreeTest, EraseFixup_RightChildScenario2) {
  s21::RedBlackTree<int> tree;

  tree.insert(50);
  tree.insert(30);
  tree.insert(70);
  tree.insert(90);
  tree.insert(65);
  tree.insert(75);

  tree.erase(90);

  // Проверяем свойства красно-черного дерева
  int blackCount = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCount, 0));
}

TEST(RedBlackTreeTest, EraseFixup_RightChildScenario3) {
  s21::RedBlackTree<int> tree;

  tree.insert(40);
  tree.insert(20);
  tree.insert(60);
  tree.insert(50);
  tree.insert(70);
  tree.insert(80);

  tree.erase(80);

  int blackCount = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCount, 0));
}

TEST(RedBlackTreeTest, EraseFixup_RightChildScenario4) {
  s21::RedBlackTree<int> tree;

  tree.insert(50);
  tree.insert(25);
  tree.insert(75);
  tree.insert(15);
  tree.insert(35);
  tree.insert(65);
  tree.insert(85);

  tree.erase(65);

  int blackCount = -1;
  ASSERT_TRUE(checkRedBlackProperties(tree.getRoot(), blackCount, 0));
}

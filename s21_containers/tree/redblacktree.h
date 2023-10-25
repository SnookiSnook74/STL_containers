/**
 * @file RedBlackTree.h
 * @author [emerosro]
 * @version [1.0]
 *
 * @brief Класс красно-черного дерева для реализации контейнеров set и map.
 *
 * Данный файл содержит объявление и реализацию класса RedBlackTree, который
 * представляет собой красно-черное дерево, используемое для реализации
 * контейнеров set и map, multiset.
 */

#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_TREE_S21_REDBLACKTREE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_TREE_S21_REDBLACKTREE_H_

#include <functional>
#include <iostream>
#include <memory>

namespace s21 {

/**
 * @class RedBlackTree
 * @brief Класс красно-черного дерева.
 *
 * RedBlackTree является классом, реализующим красно-черное дерево.
 * Он предоставляет базовые операции, такие как вставка, удаление и поиск,
 * с сохранением свойств красно-черного дерева.
 *
 * @tparam Key Тип ключа.
 * @tparam Compare Функция сравнения для ключей.
 */

template <typename Key, typename Compare = std::less<Key>>
class RedBlackTree {
 public:
  enum class Color { RED, BLACK };

  friend class Iterator;
  friend class ConstIterator;

  struct Node {
    Key key;
    Color color;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::weak_ptr<Node> parent;

    Node(const Key& key, Color color)
        : key(key), color(color), left(nullptr), right(nullptr), parent() {}
  };
  using NodePtr = std::shared_ptr<Node>;
  RedBlackTree(const RedBlackTree& other) {
    // Копируем узлы из `other` в текущий объект
    root_ = copyNodes(other.root_);
    // Копируем другие поля, если они есть
  }
  // Конструктор перемещения
  RedBlackTree(RedBlackTree&& other) {
    root_ = other.root_;
    size_ = other.size_;
    // Перемещаем другие поля, если они есть
    other.root_ = nullptr;
    // Обнуляем другие поля в `other`, если они есть
    other.size_ = 0;
  }

  /**
   * @brief Оператор присваивания с перемещением.
   *
   * Перемещает ресурсы из другого дерева в текущий объект, обеспечивая
   * эффективное присваивание без копирования данных. После перемещения исходное
   * дерево `other` становится пустым.
   *
   * @param other Дерево, ресурсы которого должны быть перемещены.
   * @return Ссылка на текущий объект после завершения операции присваивания.
   */

  RedBlackTree& operator=(RedBlackTree&& other) noexcept {
    if (this != &other) {
      // Освобождаем текущие ресурсы
      root_ = nullptr;
      // Перемещаем ресурсы из other
      root_ = std::move(other.root_);
      size_ = other.size_;
      // Обнуляем ресурсы в other
      other.root_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  /**
   * @class Iterator
   * @brief Итератор для красно-черного дерева.
   *
   * Класс Iterator предоставляет методы для итерации по элементам
   * красно-черного дерева и доступа к их значениям.
   */
  class Iterator {
   public:
    // typedef для работы со стандартными алгоритмами  по типу std::count_if
    // Разность между итераторами
    using difference_type = std::ptrdiff_t;
    using value_type = Key;
    using pointer = Key*;
    using reference = Key&;
    // Тип итератора: может двигаться как вперед, так и назад
    using iterator_category = std::bidirectional_iterator_tag;

    Iterator(NodePtr node, RedBlackTree* treePtr = nullptr)
        : current(node), tree(treePtr) {}

    Key& operator*() {
      if (!current) {
        throw std::runtime_error("Попытка разыменования nullptr");
      }
      return current->key;
    }

    const Key& operator*() const {
      if (!current) {
        throw std::runtime_error("Попытка разыменования nullptr");
      }
      return current->key;
    }

    Iterator& operator++() {
      if (!current) {
        throw std::runtime_error("Попытка инкремента end итератора");
      }
      // Если существует правый потомок
      if (current->right) {
        current = current->right;  // Переходим к правому потомку
        // Идем налево до упора
        while (current->left) {
          current = current->left;
        }
      } else {
        // Если правого потомка нет, идем вверх к родителю
        NodePtr parent = current->parent.lock();
        // Продолжаем двигаться вверх, пока текущий узел не станет левым
        // потомком родителя
        while (parent && current == parent->right) {
          current = parent;
          parent = current->parent.lock();
        }
        current = parent;  // Теперь текущий элемент - это родитель
      }
      return *this;
    }

    Iterator& operator--() {
      if (!current) {  // Если текущий узел nullptr (end())
        current = tree->root_;
        while (current && current->right) {  // Идите к самому правому элементу
          current = current->right;
        }
      } else if (current->left) {
        current = current->left;
        while (current->right) {
          current = current->right;
        }
      } else {
        NodePtr parent = current->parent.lock();
        while (parent && current == parent->left) {
          current = parent;
          parent = current->parent.lock();
        }
        current = parent;
      }
      return *this;
    }

    bool is_valid() const { return current != nullptr; }

    bool operator==(const Iterator& other) const {
      return current == other.current;
    }
    bool operator!=(const Iterator& other) const { return !(*this == other); }

   private:
    NodePtr current;
    RedBlackTree* tree;
  };

  class ConstIterator {
   public:
    using difference_type = std::ptrdiff_t;
    using value_type = Key;
    using pointer = Key*;
    using reference = Key&;
    using iterator_category = std::bidirectional_iterator_tag;

    ConstIterator(NodePtr node, const RedBlackTree* treePtr = nullptr)
        : current(node), tree(treePtr) {}

    const Key& operator*() const {
      if (!current) {
        throw std::runtime_error("Попытка разыменования nullptr");
      }
      return current->key;
    }
    ConstIterator& operator++() {
      if (!current) {
        throw std::runtime_error("Попытка инкремента nullptr итератора");
      }
      if (current->right) {
        current = current->right;
        while (current->left) {
          current = current->left;
        }
      } else {
        NodePtr parent = current->parent.lock();
        while (parent && current == parent->right) {
          current = parent;
          parent = current->parent.lock();
        }
        current = parent;
      }
      return *this;
    }
    ConstIterator& operator--() {
      if (!current) {
        current = tree->root_;
        while (current && current->right) {
          current = current->right;
        }
        return *this;
      }
      if (current->left) {
        current = current->left;
        while (current->right) {
          current = current->right;
        }
      } else {
        NodePtr parent = current->parent.lock();
        while (parent && current == parent->left) {
          current = parent;
          parent = current->parent.lock();
        }
        current = parent;
      }
      return *this;
    }

    bool is_valid() const { return current != nullptr; }
    bool operator==(const ConstIterator& other) const {
      return current == other.current;
    }
    bool operator!=(const ConstIterator& other) const {
      return !(*this == other);
    }

   private:
    NodePtr current;
    const RedBlackTree* tree;
  };

  /**
   * @brief Возвращает итератор, указывающий на первый элемент в дереве.
   *
   * Элемент с наименьшим ключом находится в самом левом узле дерева.
   *
   * @return Итератор, указывающий на первый элемент.
   */
  Iterator begin() {
    NodePtr min = root_;
    while (min->left) {
      min = min->left;
    }
    return Iterator(min);
  }

  /**
   * @brief Возвращает итератор, указывающий на элемент после последнего в
   * дереве.
   *
   * Используется как маркер окончания итерации.
   *
   * @return Итератор, указывающий на элемент после последнего.
   */
  Iterator end() { return Iterator(nullptr, this); }

  /**
   * @brief Возвращает константный итератор, указывающий на первый элемент в
   * дереве.
   *
   * Элемент с наименьшим ключом находится в самом левом узле дерева.
   *
   * @return Константный итератор, указывающий на первый элемент.
   */
  ConstIterator cbegin() const {
    NodePtr min = root_;
    while (min && min->left) {
      min = min->left;
    }
    return ConstIterator(min);
  }

  /**
   * @brief Возвращает константный итератор, указывающий на элемент после
   * последнего в дереве.
   *
   * Используется как маркер окончания итерации.
   *
   * @return Константный итератор, указывающий на элемент после последнего.
   */
  ConstIterator cend() const { return ConstIterator(nullptr, this); }

  /**
   * @brief Конструктор по умолчанию для красно-черного дерева.
   *
   * Создает пустое красно-черное дерево.
   */
  RedBlackTree() : root_(nullptr), comp_(Compare()), size_(0) {}

  /**
   * @brief Получает корневой узел дерева.
   *
   * @return Указатель на корневой узел дерева.
   */
  NodePtr getRoot() const { return root_; }

  /**
   * @brief Возвращает размер дерева (количество узлов).
   *
   * @return Размер дерева.
   */
  std::size_t size() const { return size_; }

  /**
   * @brief Сбрасывает дерево до начального состояния.
   *
   * Удаляет все узлы из дерева и устанавливает его размер равным нулю.
   */
  void reset() {
    root_ = nullptr;
    size_ = 0;
  }

  /**
   * @brief Обменивает содержимое текущего дерева с содержимым другого дерева.
   *
   * Метод обменивает корни деревьев и их размеры между текущим деревом и
   * предоставленным в качестве аргумента.
   *
   * @param other Дерево, с которым производится обмен.
   */
  void swap(RedBlackTree& other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }

  /**
   * @brief Вставляет ключ в красно-черное дерево.
   *
   * Если ключ уже существует в дереве, метод возвращает пару, состоящую из
   * указателя на существующий узел и значения `false`. Если ключа не
   * существует, он вставляется в дерево, и метод возвращает пару, состоящую из
   * указателя на новый узел и значения `true`.
   *
   * @param key Ключ, который нужно вставить в дерево.
   * @return Пара, состоящая из указателя на узел (новый или существующий) и
   * булева значения, указывающего на успешность вставки.
   */
  std::pair<NodePtr, bool> insert(const Key& key) {
    NodePtr y = nullptr;
    NodePtr x = root_;

    // Ищем место и проверяем, существует ли ключ
    while (x != nullptr) {
      y = x;
      if (comp_(key, x->key)) {
        x = x->left;
      } else if (comp_(x->key, key)) {
        x = x->right;
      } else {
        // Ключ уже существует; возвращаем указатель и false
        return {x, false};
      }
    }
    // Вставляем новый узел
    NodePtr newNode = std::make_shared<Node>(key, Color::RED);
    newNode->parent = y;
    if (y == nullptr) {
      root_ = newNode;
    } else if (comp_(key, y->key)) {
      y->left = newNode;
    } else {
      y->right = newNode;
    }
    ++size_;
    // Исправляем дерево
    insertFixup(newNode);
    // Возвращаем указатель и true
    return {newNode, true};
  }

  std::pair<NodePtr, bool> insert_mult(const Key& key) {
    NodePtr y = nullptr;
    NodePtr x = root_;

    // Ищем место и проверяем, существует ли ключ
    while (x != nullptr) {
      y = x;
      if (comp_(key, x->key)) {
        x = x->left;
      } else {
        x = x->right;
      }
    }
    // Вставляем новый узел
    NodePtr newNode = std::make_shared<Node>(key, Color::RED);
    newNode->parent = y;
    if (y == nullptr) {
      root_ = newNode;
    } else if (comp_(key, y->key)) {
      y->left = newNode;
    } else {
      y->right = newNode;
    }
    ++size_;
    // Исправляем дерево
    insertFixup(newNode);
    // Возвращаем указатель и true
    return {newNode, true};
  }

  /**
   * @brief Удаляет узел с указанным ключом из красно-черного дерева.
   *
   * Если ключ не найден в дереве, метод просто возвращает управление.
   * Если ключ найден, узел удаляется, и дерево, при необходимости,
   * корректируется, чтобы сохранить свойства красно-черного дерева. Размер
   * дерева уменьшается на один.
   *
   * @param key Ключ, который следует удалить из дерева.
   */
  void erase(const Key& key) {
    NodePtr z = find(key);
    if (z == nullptr) {
      return;
    }
    NodePtr y = (z->left && z->right) ? treeMinimum(z->right) : z;
    NodePtr x = y->left ? y->left : y->right;
    if (x) {
      x->parent = y->parent;
    }
    if (!y->parent.lock()) {
      root_ = x;
    } else {
      if (y == y->parent.lock()->left) {
        y->parent.lock()->left = x;
      } else {
        y->parent.lock()->right = x;
      }
    }
    if (y != z) {
      z->key = y->key;
    }
    if (y->color == Color::BLACK) {
      eraseFixup(x);
    }
    --size_;
  }

  /**
   * @brief Возвращает узел с минимальным ключом в поддереве, корнем которого
   * является данный узел.
   *
   * Этот метод ищет узел с минимальным ключом, двигаясь влево от указанного
   * узла, пока не достигнет листового узла.
   *
   * @param x Указатель на узел, откуда начинается поиск минимального значения.
   * @return Указатель на узел с минимальным ключом в поддереве.
   */
  NodePtr treeMinimum(NodePtr x) const {
    while (x->left) {
      x = x->left;
    }
    return x;
  }

  /**
   * @brief Ищет узел с указанным ключом в дереве.
   *
   * Метод проходит по дереву, ища узел с заданным ключом, и возвращает
   * указатель на этот узел, если он найден. В противном случае метод возвращает
   * `nullptr`.
   *
   * @param key Ключ, который нужно найти в дереве.
   * @return Указатель на узел с данным ключом или `nullptr`, если такой узел не
   * найден.
   */
  NodePtr find(const Key& key) const {
    NodePtr x = root_;
    while (x != nullptr) {
      if (comp_(key, x->key)) {
        x = x->left;
      } else if (comp_(x->key, key)) {
        x = x->right;
      } else {
        return x;  // Узел с заданным ключом найден
      }
    }
    return nullptr;  // Узел с заданным ключом не найден
  }

  /**
   * @brief Выполняет левое вращение дерева вокруг узла x.
   *
   * Левое вращение преобразует поддерево, корнем которого является x,
   * перераспределяя узлы, чтобы узел x был перемещен вниз и влево, а его правый
   * потомок стал бы новым корнем.
   *
   * @param x Указатель на узел, вокруг которого выполняется вращение.
   */
  void rotateLeft(NodePtr x) {
    NodePtr y = x->right;  // устанавливаем y
    x->right = y->left;  // делаем левого потомка y правым потомком x

    if (y->left != nullptr) {
      y->left->parent =
          x;  // Теперь левый потомок y указывает на x как на своего родителя
    }
    y->parent = x->parent.lock();  // обновляем родителя y
    if (x->parent.lock() == nullptr) {
      root_ = y;  // если x был корнем, делаем y новым корнем
    } else {
      if (x == x->parent.lock()->left) {
        x->parent.lock()->left = y;
      } else {
        x->parent.lock()->right = y;
      }
    }
    y->left = x;
    x->parent = y;
  }

  /**
   * @brief Выполняет правое вращение дерева вокруг узла y.
   *
   * Правое вращение преобразует поддерево, корнем которого является y,
   * перераспределяя узлы, чтобы узел y был перемещен вниз и вправо, а его левый
   * потомок стал бы новым корнем.
   *
   * @param y Указатель на узел, вокруг которого выполняется вращение.
   */
  void rotateRight(NodePtr y) {
    NodePtr x = y->left;  // устанавливаем x
    y->left = x->right;  // делаем правого потомка x левым потомком y

    if (x->right != nullptr) {
      x->right->parent =
          y;  // Теперь правый потомок x указывает на y как на своего родителя
    }
    x->parent = y->parent.lock();  // обновляем родителя x
    if (y->parent.lock() == nullptr) {
      root_ = x;  // если y был корнем, делаем x новым корнем
    } else {
      if (y == y->parent.lock()->left) {
        y->parent.lock()->left = x;
      } else {
        y->parent.lock()->right = x;
      }
    }
    x->right = y;   // делаем y правым потомком x
    y->parent = x;  // обновляем родителя y
  }

  /**
   * @brief Исправляет нарушения свойств красно-черного дерева после вставки.
   *
   * После вставки узла в красно-черное дерево, некоторые из следующих свойств
   * могут быть нарушены:
   * 1. Каждый узел или красный или черный.
   * 2. Корень дерева всегда черный.
   * 3. Если узел красный, оба его потомка черные.
   * 4. Для каждого узла, любой путь от этого узла к его листовым потомкам
   * содержит одинаковое количество черных узлов.
   *
   * Этот метод восстанавливает указанные свойства дерева, проводя ряд операций,
   * таких как вращения и изменения цветов узлов. Основной идеей метода является
   * гарантированное восстановление свойств дерева при любом распределении
   * узлов.
   *
   * @param z Указатель на вновь вставленный узел, начиная с которого
   * выполняются корректировки.
   */
  void insertFixup(NodePtr z) {
    // Проверка: родитель z красный (это может нарушить свойства красно-черного
    // дерева)
    while (z->parent.lock() && z->parent.lock()->color == Color::RED) {
      auto parent = z->parent.lock();
      auto grandParent = parent->parent.lock();
      // Если нет дедушки, выходим из цикла
      if (!grandParent) break;
      // Родитель z - левый потомок дедушки
      if (parent == grandParent->left) {
        auto y = grandParent->right;
        // Случай 1: дядя z (y) также красный
        if (y && y->color == Color::RED) {
          parent->color = Color::BLACK;  // Перекрашиваем родителя
          y->color = Color::BLACK;  // Перекрашиваем дядю
          grandParent->color = Color::RED;  // Перекрашиваем дедушку
          z = grandParent;  // Продолжаем проверку с дедушкой
        } else {
          // Случай 2: z - правый потомок, но его родитель - левый потомок
          // дедушки (треугольник)
          if (z == parent->right) {
            z = parent;
            rotateLeft(z);
          }
          // Случай 3: z - левый потомок и его родитель также левый потомок
          // дедушки (линия)
          parent->color = Color::BLACK;  // Перекрашиваем родителя
          grandParent->color = Color::RED;  // Перекрашиваем дедушку
          rotateRight(grandParent);
        }
      } else {
        // Аналогично предыдущему, но симметрично для правой стороны
        auto y = grandParent->left;
        if (y && y->color == Color::RED) {
          parent->color = Color::BLACK;
          y->color = Color::BLACK;
          grandParent->color = Color::RED;
          z = grandParent;
        } else {
          if (z == parent->left) {
            z = parent;
            rotateRight(z);
          }
          parent->color = Color::BLACK;
          grandParent->color = Color::RED;
          rotateLeft(grandParent);
        }
      }
    }
    // В конце корень дерева всегда должен быть черным
    root_->color = Color::BLACK;
  }

 private:
  NodePtr root_;
  Compare comp_;
  std::size_t size_;

  /**
   * @brief Исправляет нарушения свойств красно-черного дерева после удаления.
   *
   * Этот метод восстанавливает указанные свойства дерева после удаления узла.
   * Для этого он рассматривает различные случаи, основанные на положении и
   * цвете текущего узла, его родителя, брата и детей брата. В зависимости от
   * этих случаев применяются определенные операции, такие как вращения и
   * изменения цветов узлов, чтобы устранить нарушения и восстановить свойства
   * дерева.
   *
   * @param x Указатель на узел, начиная с которого выполняются корректировки.
   * Обычно это узел, который следовал за удаленным узлом в порядке обхода
   * дерева.
   */
  void eraseFixup(NodePtr x) {
    // Продолжаем, пока x не является корнем и x либо nullptr, либо черный узел
    while (x != root_ && (!x || x->color == Color::BLACK)) {
      if (x) {
        // Если x - левый потомок его родителя
        if (x == x->parent.lock()->left) {
          NodePtr w = x->parent.lock()->right;
          // Если брат x красный, преобразуем его в черный
          if (w->color == Color::RED) {
            w->color = Color::BLACK;
            x->parent.lock()->color = Color::RED;
            rotateLeft(x->parent.lock());
            w = x->parent.lock()->right;
          }
          // Если оба потомка w черные
          if ((!w->left || w->left->color == Color::BLACK) &&
              (!w->right || w->right->color == Color::BLACK)) {
            w->color = Color::RED;
            x = x->parent.lock();
          } else {
            // Если только правый потомок w черный
            if (!w->right || w->right->color == Color::BLACK) {
              w->left->color = Color::BLACK;
              w->color = Color::RED;
              rotateRight(w);
              w = x->parent.lock()->right;
            }
            // Перекрашиваем и выполняем левое вращение
            w->color = x->parent.lock()->color;
            x->parent.lock()->color = Color::BLACK;
            if (w->right) {
              w->right->color = Color::BLACK;
            }
            rotateLeft(x->parent.lock());
            x = root_;
          }
        } else {  // Если x - правый потомок его родителя
          NodePtr w = x->parent.lock()->left;
          // Если брат x красный, преобразуем его в черный
          if (w->color == Color::RED) {
            w->color = Color::BLACK;
            x->parent.lock()->color = Color::RED;
            rotateRight(x->parent.lock());
            w = x->parent.lock()->left;
          }
          // Если оба потомка w черные
          if ((!w->right || w->right->color == Color::BLACK) &&
              (!w->left || w->left->color == Color::BLACK)) {
            w->color = Color::RED;
            x = x->parent.lock();
          } else {
            // Если только левый потомок w черный
            if (!w->left || w->left->color == Color::BLACK) {
              w->right->color = Color::BLACK;
              w->color = Color::RED;
              rotateLeft(w);
              w = x->parent.lock()->left;
            }
            // Перекрашиваем и выполняем правое вращение
            w->color = x->parent.lock()->color;
            x->parent.lock()->color = Color::BLACK;
            if (w->left) {
              w->left->color = Color::BLACK;
            }
            rotateRight(x->parent.lock());
            x = root_;
          }
        }
      } else {
        // Если x является nullptr, просто устанавливаем его как корень
        x = root_;
      }
    }
    // Устанавливаем x как черный узел
    if (x) {
      x->color = Color::BLACK;
    }
  }
  /**
   * @brief Рекурсивно копирует узлы дерева.
   *
   * Этот метод создает глубокую копию узлов дерева, начиная с указанного узла.
   * При копировании сохраняются все связи между узлами, включая родительские
   * связи.
   *
   * @param node Указатель на узел, который нужно скопировать вместе с его
   * потомками.
   * @return Указатель на новый узел, являющийся копией указанного узла.
   */
  NodePtr copyNodes(NodePtr node) {
    if (!node) return nullptr;
    NodePtr newNode = std::make_shared<Node>(*node);
    newNode->left = copyNodes(node->left);
    newNode->right = copyNodes(node->right);
    if (newNode->left) newNode->left->parent = newNode;
    if (newNode->right) newNode->right->parent = newNode;

    return newNode;
  }
};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_TREE_S21_REDBLACKTREE_H_
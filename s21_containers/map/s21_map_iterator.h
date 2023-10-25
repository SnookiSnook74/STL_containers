/**
 * @file s21_map_iterators.h
 * @brief Итераторы для карты (map) на основе красно-черного дерева.
 *
 * Этот файл содержит определения итераторов для карты, реализованной на основе
 * красно-черного дерева. Предоставляются итератор и константный итератор,
 * позволяющие просматривать и изменять элементы карты. Для корректной работы
 * итераторов реализован специальный компаратор PairCompare, который позволяет
 * сравнивать пары ключ-значение только по ключу.
 *
 * @author emerosro
 * @version 1.0
 */

#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_MAP_S21_MAP_ITERATOR_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_MAP_S21_MAP_ITERATOR_H_

#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "../tree/redblacktree.h"

namespace s21 {

template <typename Key, typename Value, typename Compare = std::less<Key>>
struct PairCompare {
  Compare comp;
  bool operator()(const std::pair<Key, Value>& a,
                  const std::pair<Key, Value>& b) const {
    return comp(a.first, b.first);
  }
};

template <typename Key, typename Value, typename Compare = std::less<Key>>
class MapIterator {
  using KeyValuePair = std::pair<Key, Value>;
  using PairCompareType = PairCompare<Key, Value, Compare>;

 public:
  bool is_valid() const { return tree_iterator.is_valid(); }

  /**
   * @brief Конструктор итератора карты.
   *
   * Создает итератор для карты, инициализируя его итератором красно-черного
   * дерева.
   *
   * @param it Итератор красно-черного дерева, который будет использоваться для
   * инициализации.
   */
  MapIterator(
      const typename RedBlackTree<KeyValuePair, PairCompareType>::Iterator& it)
      : tree_iterator(it) {}

  /**
   * @brief Оператор разыменования.
   *
   * Возвращает ссылку на пару ключ-значение, на которую указывает итератор.
   * Для обеспечения неизменяемости ключа выполняется приведение типов.
   *
   * @return Ссылка на пару ключ-значение, на которую указывает итератор.
   */

  std::pair<const typename KeyValuePair::first_type,
            typename KeyValuePair::second_type>&
  operator*() {
    return *reinterpret_cast<std::pair<const typename KeyValuePair::first_type,
                                       typename KeyValuePair::second_type>*>(
        &(*tree_iterator));
  }

  /**
   * @brief Оператор "->".
   *
   * Возвращает указатель на пару ключ-значение, на которую указывает итератор.
   * Предоставляет доступ к членам пары через оператор ->.
   * Если итератор недействителен, будет вызвано исключение.
   *
   * @return Указатель на пару ключ-значение, на которую указывает итератор.
   * @throw std::runtime_error Если итератор недействителен.
   */
  const std::pair<const typename KeyValuePair::first_type,
                  typename KeyValuePair::second_type>*
  operator->() const {
    if (!is_valid()) {
      throw std::runtime_error("Attempt to dereference invalid iterator");
    }
    return reinterpret_cast<
        const std::pair<const typename KeyValuePair::first_type,
                        typename KeyValuePair::second_type>*>(
        &(*tree_iterator));
  }

  MapIterator& operator++() {
    ++tree_iterator;
    return *this;
  }

  MapIterator& operator--() {
    --tree_iterator;
    return *this;
  }

  bool operator==(const MapIterator& other) const {
    return tree_iterator == other.tree_iterator;
  }

  bool operator!=(const MapIterator& other) const {
    return tree_iterator != other.tree_iterator;
  }

 private:
  typename RedBlackTree<KeyValuePair, PairCompareType>::Iterator tree_iterator;
};

template <typename Key, typename Value, typename Compare = std::less<Key>>
class ConstMapIterator {
  using KeyValuePair = std::pair<Key, Value>;
  using PairCompareType = PairCompare<Key, Value, Compare>;

 public:
  bool is_valid() const { return tree_iterator.is_valid(); }

  ConstMapIterator(
      const typename RedBlackTree<KeyValuePair, PairCompareType>::ConstIterator&
          it)
      : tree_iterator(it) {}

  const std::pair<const typename KeyValuePair::first_type,
                  typename KeyValuePair::second_type>&
  operator*() const {
    return *reinterpret_cast<
        const std::pair<const typename KeyValuePair::first_type,
                        typename KeyValuePair::second_type>*>(
        &(*tree_iterator));
  }

  const std::pair<const typename KeyValuePair::first_type,
                  typename KeyValuePair::second_type>*
  operator->() const {
    if (!is_valid()) {
      throw std::runtime_error("Attempt to dereference invalid iterator");
    }
    return reinterpret_cast<
        const std::pair<const typename KeyValuePair::first_type,
                        typename KeyValuePair::second_type>*>(
        &(*tree_iterator));
  }

  ConstMapIterator& operator++() {
    ++tree_iterator;
    return *this;
  }

  ConstMapIterator& operator--() {
    --tree_iterator;
    return *this;
  }

  bool operator==(const ConstMapIterator& other) const {
    return tree_iterator == other.tree_iterator;
  }

  bool operator!=(const ConstMapIterator& other) const {
    return tree_iterator != other.tree_iterator;
  }

 private:
  typename RedBlackTree<KeyValuePair, PairCompareType>::ConstIterator
      tree_iterator;
};

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_MAP_S21_MAP_ITERATOR_H_
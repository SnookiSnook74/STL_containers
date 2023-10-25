/**
 * @file s21_set.h
 * @brief Контейнер Set на основе красно-черного дерева.
 *
 * Контейнер set предоставляет средства для хранения уникальных отсортированных
 * ключей. Для большинства своих операций он предлагает логарифмическую
 * временную сложность и использует красно-черное дерево для эффективного
 * хранения и выполнения операций. Все основные операции делаются из базового
 * класса RedBlackTree, Set в данном случае выступает оберткой.
 *
 * @author [emerosro]
 * @version 1.0
 */

#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_SET_S21_SET_H_

#include <cstddef>
#include <limits>

#include "../tree/redblacktree.h"

namespace s21 {
template <typename Key, typename Compare = std::less<Key>>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using iterator = typename RedBlackTree<Key, Compare>::Iterator;
  using const_iterator = typename RedBlackTree<Key, Compare>::ConstIterator;

  set() : tree_() {}
  set(std::initializer_list<value_type> const& items) : tree_() {
    for (const auto& item : items) {
      tree_.insert(item);
    }
  }
  set(const set& s) : tree_(s.tree_) {}
  set(set&& s) : tree_(std::move(s.tree_)) {}

  set& operator=(set&& other) {
    if (this != &other) {
      this->tree_ = std::move(other.tree_);
    }
    return *this;
  }

  ~set() {}

  iterator begin() {
    return tree_.begin();
  }  // напрямую используем методы дерева
  iterator end() { return tree_.end(); }

  const_iterator begin() const { return tree_.cbegin(); }
  const_iterator end() const { return tree_.cend(); }

  [[nodiscard]] size_type size() const { return tree_.size(); }
  [[nodiscard]] bool empty() const { return tree_.size() == 0; }
  [[nodiscard]] size_type max_size() const {
    return std::numeric_limits<size_type>::max();
  }

  void clear() {
    // Создаем новое пустое дерево, такая реализация возможно из-за
    // использования Умных указателей
    tree_ = RedBlackTree<Key, Compare>();
  }

  std::pair<iterator, bool> insert(const value_type& value) {
    auto result = tree_.insert(value);
    if (result.second) {
      // Вставка была успешной
      return {iterator(result.first), true};
    } else {
      // Элемент уже существует
      return {iterator(result.first), false};
    }
  }

  void erase(iterator pos) {
    // используем оператор разыменования итератора для доступа к ключу
    Key key_to_remove = *pos;
    tree_.erase(key_to_remove);
  }

  void erase(const Key& key) { tree_.erase(key); }

  void swap(set& other) { tree_.swap(other.tree_); }

  void merge(set& other) {
    for (const auto& value : other) {
      tree_.insert(value);
    }
    other.clear();
  }

  iterator find(const Key& key) {
    auto node_ptr = tree_.find(key);
    return iterator(node_ptr);
  }

  bool contains(const Key& key) {
    // Если find() не возвращает end(), элемент существует
    return find(key) != end();
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> results;
    (results.push_back(insert(std::forward<Args>(args))), ...);
    return results;
  }

 protected:
  RedBlackTree<Key, Compare> tree_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_SET_S21_SET_H_

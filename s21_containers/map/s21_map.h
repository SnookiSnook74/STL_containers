/**
 * @file s21_map.h
 * @brief Ассоциативный массив (map) на основе красно-черного дерева.
 *
 * Класс map предоставляет средства для управления структурой данных
 * "ассоциативный массив". Он позволяет сохранять пары "ключ-значение" и
 * обеспечивает быстрый доступ к значениям по ключам. Эта реализация map
 * основана на красно-черном дереве, что гарантирует логарифмическое время для
 * операций вставки, удаления и поиска.
 *
 * @author [emerosro]
 * @version 1.0
 */

#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_MAP_S21_MAP_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_MAP_S21_MAP_H_

#include <functional>
#include <iostream>
#include <utility>

#include "s21_map_iterator.h"

namespace s21 {
template <typename Key, typename Value, typename Compare = std::less<Key>>
class map {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using KeyValuePair = std::pair<key_type, mapped_type>;
  using PairCompareType = PairCompare<Key, Value, Compare>;
  using iterator = MapIterator<Key, Value, Compare>;
  using const_iterator = ConstMapIterator<Key, Value, Compare>;

  map() = default;
  map(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) {
      insert(item);
    }
  }
  map(const map &m) : tree(m.tree) {}
  map(map &&m) noexcept : tree(std::move(m.tree)) { m.tree.reset(); }
  map &operator=(map &&m) noexcept {
    if (this != &m) {
      tree = std::move(m.tree);
      m.tree.reset();
    }
    return *this;
  }
  mapped_type &at(const Key &key) {
    KeyValuePair kv{key, {}};
    auto node = tree.find(kv);  // Передача объекта std::pair в метод find
    if (node != nullptr) {
      return node->key.second;
    } else {
      throw std::out_of_range("Key not found");
    }
  }
  mapped_type &operator[](const key_type &key) {
    auto result = tree.insert({key, mapped_type()});
    return result.first->key.second;
  }
  iterator begin() { return iterator(tree.begin()); }
  iterator end() { return iterator(tree.end()); }
  const_iterator cbegin() const { return const_iterator(tree.cbegin()); }
  const_iterator cend() const { return const_iterator(tree.cend()); }

  std::pair<iterator, bool> insert(const value_type &value) {
    auto result = tree.insert(value);
    return {iterator(result.first), result.second};
  }

  std::pair<iterator, bool> insert(const Key &key, const Value &obj) {
    return insert({key, obj});
  }
  
  // Заменяет значение по ключу 
  std::pair<iterator, bool> insert_or_assign(const Key &key, const Value &obj) {
    auto result = tree.insert({key, obj});
    if (!result.second) {  // Если ключ уже существует
      auto newNode = std::make_shared<typename RedBlackTree<KeyValuePair, PairCompareType>::Node>(
          std::make_pair(key, obj),
          s21::RedBlackTree<KeyValuePair, PairCompareType>::Color::RED);
      // Сохранение ссылки на родительский узел перед заменой узла
      auto parent = result.first->parent.lock();
      newNode->parent = parent;
      if (!parent) {  // Если узел был корнем
        tree.getRoot() = newNode;
      } else if (parent->left == result.first) {
        parent->left = newNode;
      } else {
        parent->right = newNode;
      }
      tree.insertFixup(newNode);
      return {iterator(newNode), false};
    }
    return {iterator(result.first), true};
  }

  [[nodiscard]] size_type size() const { return tree.size(); }
  [[nodiscard]] bool empty() const { return tree.size() == 0; }
  [[nodiscard]] size_type max_size() const {
    return std::numeric_limits<size_type>::max();
  }

  void clear() { tree = RedBlackTree<KeyValuePair, PairCompareType>(); }

  void swap(map &other) { tree.swap(other.tree); }

  void erase(iterator pos) {
    if (pos != end()) {  // Проверяем, что итератор действителен
      const value_type &value =
          *pos;  // Извлекаем пару ключ/значение из итератора
      tree.erase(value);  // Удаляем узел с этим ключом из дерева
    }
  }

  void merge(map &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(*it);
    }
    other.clear();
  }

  bool contains(const Key &key) const {
    KeyValuePair kv{key, {}};
    return tree.find(kv) != nullptr;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> results = {
        insert(std::forward<Args>(args))...};
    return results;
  }

 private:
  RedBlackTree<KeyValuePair, PairCompareType> tree;
};

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_MAP_S21_MAP_H_
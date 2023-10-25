/**
 * @file s21_list.h
 * @brief Двусвязный список (list).
 *
 * Класс list предоставляет средства для управления двусвязным списком.
 * Он предлагает функциональность для вставки, удаления и доступа к элементам
 * списка с возможностью прохода в обе стороны с помощью итераторов.
 * Эта реализация list обеспечивает постоянное время для вставки и удаления
 * элементов на любой позиции, при условии, что у вас есть итератор на позицию.
 *
 * @author [emerosro]
 * @version 1.0
 */

#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_LIST_S21_LIST_H_

#include <cstddef>
#include <iostream>

namespace s21 {
template <typename T>
struct NodeStruct {
  T data;
  NodeStruct *next;
  NodeStruct *prev;
  explicit NodeStruct(const T &data)
      : data(data), next(nullptr), prev(nullptr) {}
};
// Базовый класс
template <typename T>
class ListIteratorBase {
 public:
  using Node = NodeStruct<T>;
  ListIteratorBase(Node *node, Node *tail) : node_(node), tail_(tail) {}
  Node *getNode() const { return node_; }
  Node *getTail() const { return tail_; }

 protected:
  T &getData() const {
    if (node_ == nullptr) {
      throw std::runtime_error("Попытка разыменования nullptr");
    }
    return node_->data;
  }
  void increment() { node_ = node_->next; }
  void decrement() {
    if (node_ == nullptr) {
      node_ = tail_;
    } else if (node_->prev == nullptr) {
      node_ = nullptr;
    } else {
      node_ = node_->prev;
    }
  }
  bool equals(const ListIteratorBase &other) const {
    return node_ == other.node_;
  }

 private:
  Node *node_;
  Node *tail_;
};

template <typename T>
class ListIterator : public ListIteratorBase<T> {
 public:
  using ListIteratorBase<T>::ListIteratorBase;
  T &operator*() const { return this->getData(); }
  ListIterator &operator++() {
    this->increment();
    return *this;
  }
  ListIterator &operator--() {
    this->decrement();
    return *this;
  }
  bool operator==(const ListIterator &other) const {
    return this->equals(other);
  }
  bool operator!=(const ListIterator &other) const { return !(*this == other); }
};

template <typename T>
class ListConstIterator : public ListIteratorBase<T> {
 public:
  using ListIteratorBase<T>::ListIteratorBase;

  ListConstIterator(const ListIterator<T> &other)
      : ListIteratorBase<T>(other.getNode(), other.getTail()) {}

  const T &operator*() const { return this->getData(); }
  ListConstIterator &operator++() {
    this->increment();
    return *this;
  }
  ListConstIterator &operator--() {
    this->decrement();
    return *this;
  }
  bool operator==(const ListConstIterator &other) const {
    return this->equals(other);
  }
  bool operator!=(const ListConstIterator &other) const {
    return !(*this == other);
  }
};

template <typename T>
class list {
 public:
  // -----List Member type----------------
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Node = NodeStruct<value_type>;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  // -----------END-----------------------

  // --------List Functions---------------
  list() : head_(nullptr), tail_(nullptr), size_(0) {}

  list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
    for (size_type i = 0; i < n; ++i) {
      push_back(value_type());
    }
  }

  list(std::initializer_list<value_type> const &items)
      : head_(nullptr), tail_(nullptr), size_(0) {
    for (const auto &item : items) {
      push_back(item);
    }
  }

  list(const list &l) : head_(nullptr), tail_(nullptr), size_(0) {
    Node *current = l.head_;
    while (current != nullptr) {
      push_back(current->data);
      current = current->next;
    }
  }

  list(list &&l) : head_(l.head_), tail_(l.tail_), size_(l.size_) {
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
  }

  ~list() { clear(); }

  list &operator=(list &&l) {
    if (this == &l) {
      return *this;
    }
    Node *current = head_;
    while (current != nullptr) {
      Node *next_node = current->next;
      delete current;
      current = next_node;
    }
    head_ = l.head_;
    tail_ = l.tail_;
    size_ = l.size_;

    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
    return *this;
  }

  list &operator=(const list &l) {
    if (this == &l) {
      return *this;
    }
    clear();
    Node *current = l.head_;
    while (current != nullptr) {
      push_back(current->data);
      current = current->next;
    }
    return *this;
  }

  //--------------END--------------------

  //--------List Element access----------
  const_reference front() const {
    if (head_ == nullptr) {
      throw std::out_of_range("Пустой лист");
    }
    return head_->data;
  }

  reference front() {
    if (head_ == nullptr) {
      throw std::out_of_range("Пустой лист");
    }
    return head_->data;
  }

  const_reference back() const {
    if (tail_ == nullptr) {
      throw std::out_of_range("Пустой лист");
    }
    return tail_->data;
  }

  reference back() {
    if (tail_ == nullptr) {
      throw std::out_of_range("Пустой лист");
    }
    return tail_->data;
  }

  //--------------END--------------------

  //--------List Iterators---------------

  iterator begin() { return iterator(head_, tail_); }

  iterator end() { return iterator(nullptr, tail_); }

  const_iterator cbegin() const { return const_iterator(head_, tail_); }
  const_iterator cend() const { return const_iterator(nullptr, tail_); }

  //--------------END--------------------

  //----------List Capacity--------------

  bool empty() const { return head_ == nullptr; }

  size_type size() const { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
  }
  //--------------END--------------------

  //----------List Modifiers-------------

  void clear() {
    Node *current = head_;
    while (current != nullptr) {
      Node *next_node = current->next;
      delete current;
      current = next_node;
    }
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    Node *curNode = pos.getNode();
    Node *newNode = new Node(value);

    if (head_ == nullptr) {
      // Вставка в пустой список
      head_ = tail_ = newNode;
    } else if (curNode == head_) {
      // Вставка в начало списка
      newNode->next = head_;
      head_->prev = newNode;
      head_ = newNode;
    } else if (curNode == nullptr) {
      // Вставка в конец списка
      newNode->prev = tail_;
      tail_->next = newNode;
      tail_ = newNode;
    } else {
      // Вставка в середину списка
      newNode->next = curNode;
      newNode->prev = curNode->prev;
      if (curNode->prev) {
        curNode->prev->next = newNode;
      }
      curNode->prev = newNode;
    }
    ++size_;
    return iterator(newNode, tail_);
  }

  iterator insert(const_iterator pos, const_reference value) {
    return insert(iterator(pos.getNode(), tail_), value);
  }

  void erase(iterator pos) {
    Node *curNode = pos.getNode();
    if (curNode == nullptr) {
      throw std::out_of_range("Попытка удаления несуществующего элемента");
    }
    // Обновляем указатели соседних узлов
    if (curNode->prev) {
      curNode->prev->next = curNode->next;
    }
    if (curNode->next) {
      curNode->next->prev = curNode->prev;
    }
    // Обновляем head и tail
    if (curNode == head_) {
      head_ = curNode->next;
    }
    if (curNode == tail_) {
      tail_ = curNode->prev;
    }
    if (head_ == nullptr) {
      tail_ = nullptr;
    }
    // Удаляем текущий узел
    delete curNode;
    // Уменьшаем размер списка
    --size_;
  }

  void push_back(const_reference value) {
    Node *new_node = new Node(value);
    if (head_ == nullptr) {
      head_ = tail_ = new_node;
    } else {
      tail_->next = new_node;
      new_node->prev = tail_;
      tail_ = new_node;
    }
    ++size_;
  }

  void pop_back() {
    if (tail_ == nullptr) {
      return;
    }
    // Создаем итератор, указывающий на последний элемент
    iterator it = --end();
    // Используем erase для удаления
    erase(it);
  }

  void push_front(const_reference value) { insert(begin(), value); }

  void pop_front() {
    if (head_ == nullptr) {
      return;
    }
    iterator it = begin();
    erase(it);
  }

  void swap(list &other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  void merge(list &other) {
    iterator it_this = this->begin();
    iterator it_other = other.begin();
    list<value_type> temp_list;
    // Слияние двух отсортированных списков
    while (it_this != this->end() && it_other != other.end()) {
      if (*it_this <= *it_other) {
        temp_list.push_back(*it_this);
        ++it_this;
      } else {
        temp_list.push_back(*it_other);
        ++it_other;
      }
    }
    // Если один из списков закончился, добавляем оставшиеся элементы
    while (it_this != this->end()) {
      temp_list.push_back(*it_this);
      ++it_this;
    }
    while (it_other != other.end()) {
      temp_list.push_back(*it_other);
      ++it_other;
    }
    // Заменяем исходный список отсортированными элементами
    this->clear();
    for (auto item : temp_list) {
      this->push_back(item);
    }
    // Очищаем второй список, так как его элементы теперь в первом списке
    other.clear();
  }

  // Этот метод необходим для сортировки слиянием
  void merge(list &first, list &second) {
    auto it1 = first.begin();
    auto it2 = second.begin();

    while (it1 != first.end() && it2 != second.end()) {
      if (*it1 <= *it2) {
        push_back(*it1);
        ++it1;
      } else {
        push_back(*it2);
        ++it2;
      }
    }
    while (it1 != first.end()) {
      push_back(*it1);
      ++it1;
    }
    while (it2 != second.end()) {
      push_back(*it2);
      ++it2;
    }
  }

  void splice(const_iterator pos, list &other) {
    // Получаем указатели на узлы
    Node *target_node = pos.getNode();
    Node *first_node_from_other = other.head_;
    Node *last_node_from_other = other.tail_;

    // Если другой список пуст, ничего не делаем
    if (first_node_from_other == nullptr) {
      return;
    }
    // Обновляем указатели в исходном списке
    if (target_node != nullptr) {
      Node *prev_target_node = target_node->prev;
      if (prev_target_node != nullptr) {
        prev_target_node->next = first_node_from_other;
      }
      first_node_from_other->prev = prev_target_node;
      last_node_from_other->next = target_node;
      target_node->prev = last_node_from_other;

      // Обновляем head_, если pos указывал на начало списка
      if (target_node == head_) {
        head_ = first_node_from_other;
      }
    } else {
      // Если pos указывает на конец исходного списка
      if (tail_ != nullptr) {  // Если исходный список не пуст
        tail_->next = first_node_from_other;
        first_node_from_other->prev = tail_;
      } else {  // Если исходный список пуст
        head_ = first_node_from_other;
      }
      tail_ = last_node_from_other;
    }
    // Обновляем размеры списков и обнуляем указатели в другом списке
    size_ += other.size_;
    other.size_ = 0;
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  void reverse() {
    // Первый проход: меняем местами prev и next для каждого узла
    Node *current = head_;
    while (current != nullptr) {
      // Меняем местами prev и next
      std::swap(current->prev, current->next);
      // Переходим к предыдущему узлу (который теперь является next)
      current = current->prev;
    }
    // Второй проход: коррекция head и tail
    std::swap(head_, tail_);
  }

  void unique() {
    if (size_ < 2) return;
    iterator current = begin();
    iterator next = ++begin();
    while (next != end()) {
      if (*current == *next) {
        erase(next);
        next = current;
        ++next;  // Смещаем итератор next, чтобы он снова указывал на элемент
                 // после current
      } else {
        ++current;
        ++next;  // Перемещаем оба итератора вперед
      }
    }
  }

  void sort() {
    if (size_ <= 1) {
      return;  // Список уже отсортирован
    }
    list first_half, second_half;
    // Разделяем список на две половины
    auto it = begin();
    for (size_type i = 0; i < size_ / 2; ++i) {
      first_half.push_back(*it);
      ++it;
    }
    for (; it != end(); ++it) {
      second_half.push_back(*it);
    }
    // Рекурсивно сортируем каждую половину
    first_half.sort();
    second_half.sort();
    // Сливаем две отсортированные половины
    clear();
    merge(first_half, second_half);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    (insert(pos, std::forward<Args>(args)), ...);
    return iterator(pos.getNode(), tail_);
  }
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push_back(std::forward<Args>(args)), ...);
  }

  template <typename First, typename... Rest>
  void insert_many_front(First &&first, Rest &&...rest) {
    // Сначала добавляем все остальные элементы
    if constexpr (sizeof...(rest) > 0) {
      insert_many_front(std::forward<Rest>(rest)...);
    }
    // Затем добавляем первый элемент
    push_front(std::forward<First>(first));
  }

  //--------------END--------------------

 private:
  Node *head_;
  Node *tail_;
  size_type size_;
};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_LIST_S21_LIST_H_
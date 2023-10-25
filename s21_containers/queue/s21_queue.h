/**
 * @file s21_queue.h
 * @brief Очередь (queue) на основе двусвязного списка.
 *
 * Класс queue предоставляет стандартные методы управления очередью:
 * push (добавление элемента в конец очереди),
 * pop (удаление элемента из начала очереди),
 * front (доступ к первому элементу очереди),
 * back (доступ к последнему элементу очереди) и др.
 * Для внутреннего представления очереди используется двусвязный список (list)
 * или другой контейнер, предоставляемый пользователем.
 *
 * @author emerosro
 * @version 1.0
 */

#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_H_

#include "../list/s21_list.h"

namespace s21 {
template <typename T, typename Container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  queue() : s21container_() {}

  queue(std::initializer_list<value_type> const& items)
      : s21container_(items) {}

  queue(const Container& cont) : s21container_(cont) {}

  queue(const queue& q) : s21container_(q.s21container_) {}

  queue(queue&& q) : s21container_(std::move(q.s21container_)) {}

  ~queue() = default;

  queue& operator=(queue&& q) noexcept {
    if (this == &q) {
      return *this;
    }
    s21container_ = std::move(q.s21container_);
    return *this;
  }

  queue& operator=(const queue& q) {
    if (this == &q) {
      return *this;
    }
    s21container_ = q.s21container_;
    return *this;
  }

  const_reference front() { return s21container_.front(); }

  const_reference front() const { return s21container_.front(); }

  const_reference back() { return s21container_.back(); }

  const_reference back() const { return s21container_.back(); }

  [[nodiscard]] bool empty() const noexcept { return s21container_.empty(); }

  [[nodiscard]] size_type size() const noexcept { return s21container_.size(); }

  void push(const_reference value) { s21container_.push_back(value); }

  void pop() {
    if (empty()) {
      throw std::out_of_range("Очередь пуста!");
    }
    s21container_.pop_front();
  }

  void swap(queue& other) noexcept {
    std::swap(s21container_, other.s21container_);
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (s21container_.push_back(std::forward<Args>(args)), ...);
  }

 private:
  Container s21container_;
};

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_H_

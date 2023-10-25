/**
 * @file s21_stack.h
 * @brief Стек (stack) на основе двусвязного списка.
 *
 * Класс stack предоставляет стандартные методы управления стеком:
 * push (добавление элемента в верхушку стека),
 * pop (удаление элемента с верхушки стека),
 * top (доступ к верхнему элементу стека) и др.
 * Для внутреннего представления стека используется двусвязный список (list)
 * или другой контейнер, предоставляемый пользователем.
 *
 * @author [emerosro]
 * @version 1.0
 */

#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_STACK_S21_STACK_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_STACK_S21_STACK_H_

#include "../list/s21_list.h"

namespace s21 {
template <typename T, typename Container = s21::list<T>>
class stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  stack() : s21container_() {}
  stack(std::initializer_list<value_type> const& items)
      : s21container_(items) {}
  stack(const Container& cont) : s21container_(cont) {}
  stack(const stack& s) : s21container_(s.s21container_) {}
  stack(stack&& s) : s21container_(std::move(s.s21container_)) {}
  ~stack() = default;

  stack& operator=(stack&& s) noexcept {
    if (this == &s) {
      return *this;
    }
    s21container_ = std::move(s.s21container_);
    return *this;
  }

  stack& operator=(const stack& s) {
    if (this == &s) {
      return *this;
    }
    s21container_ = s.s21container_;
    return *this;
  }

  const_reference top() { return s21container_.back(); }
  const_reference top() const { return s21container_.back(); }
  // Предупреждает что обязательно нужно куда-то присвоить возращаемое значнеие.
  [[nodiscard]] bool empty() const noexcept { return s21container_.empty(); }
  [[nodiscard]] size_type size() const noexcept { return s21container_.size(); }
  void push(const_reference value) { s21container_.push_back(value); }
  void pop() {
    if (empty()) {
      throw std::out_of_range("Стек пуст!");
    }
    s21container_.pop_back();
  }
  void swap(stack& other) noexcept {
    std::swap(s21container_, other.s21container_);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    (s21container_.push_back(std::forward<Args>(args)), ...);
  }

 private:
  Container s21container_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_STACK_S21_STACK_H_
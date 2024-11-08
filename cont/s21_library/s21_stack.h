#ifndef S21_STACK
#define S21_STACK

#include <cstddef>

#include "s21_vector.h"

namespace s21 {
template <typename T, typename _container = s21::vector<T>>
class stack {
  using value_type = T;
  using const_reference = const T &;
  using reference = T &;
  using size_type = size_t;

 private:
  _container stack_;

 public:
  // Stack Member functions
  stack();
  stack(std::initializer_list<T> const &items);
  stack(const stack &s);
  stack(stack &&s);
  stack &operator=(stack &&s);
  ~stack();

  // Stack Element access
  reference top() const noexcept;

  // Stack Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;

  // Stack Modifiers
  void pop() noexcept;
  void push(const_reference value) noexcept;
  void swap(stack &other) noexcept;
};
}  // namespace s21

template <typename T, typename _container>
s21::stack<T, _container>::stack() {}

template <typename T, typename _container>
s21::stack<T, _container>::stack(std::initializer_list<T> const &items) {
  for (T i : items) push(i);
  stack_.print();
}

template <typename T, typename _container>
s21::stack<T, _container>::stack(const stack &s) : stack_(s.stack_) {}

template <typename T, typename _container>
s21::stack<T, _container>::stack(stack &&s) : stack_(std::move(s.stack_)) {}

template <typename T, typename _container>
s21::stack<T, _container> &s21::stack<T, _container>::operator=(stack &&s) {
  if (this != &s) {
    stack_ = std::move(s.stack_);
  }
  return *this;
}

template <typename T, typename _container>
s21::stack<T, _container>::~stack() {}

template <typename T, typename _container>
typename s21::stack<T, _container>::reference s21::stack<T, _container>::top()
    const noexcept {
  return stack_.back();
}

template <typename T, typename _container>
bool s21::stack<T, _container>::empty() const noexcept {
  return stack_.empty();
}

template <typename T, typename _container>
size_t s21::stack<T, _container>::size() const noexcept {
  return stack_.size();
}

template <typename T, typename _container>
void s21::stack<T, _container>::pop() noexcept {
  stack_.pop_back();
}

template <typename T, typename _container>
void s21::stack<T, _container>::push(const_reference value) noexcept {
  stack_.push_back(value);
}

template <typename T, typename _container>
void s21::stack<T, _container>::swap(stack &other) noexcept {
  std::swap(stack_, other.stack_);
}

#endif
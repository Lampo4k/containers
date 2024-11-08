#ifndef S21_QUEUE
#define S21_QUEUE

#include <cstddef>

#include "s21_list.h"

namespace s21 {
template <typename T, typename _container = s21::list<T>>
class queue {
  using size_type = size_t;
  using const_reference = const T &;
  using reference = T &;

 private:
  _container queue_;

 public:
  // Queue Member functions
  queue();
  queue(std::initializer_list<T> const &items);
  queue(const queue &q);
  queue(queue &&q);
  queue &operator=(queue &&q);
  ~queue();  // и так по умолчанию вызывается

  // Queue Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;

  // Queue Element access
  const_reference front() const noexcept;
  const_reference back() const noexcept;

  // Queue Modifiers
  void pop() noexcept;
  void push(const_reference value) noexcept;
  void swap(queue &other) noexcept;
};
}  // namespace s21

template <typename T, typename _container>
s21::queue<T, _container>::queue() {}

template <typename T, typename _container>
s21::queue<T, _container>::queue(std::initializer_list<T> const &items) {
  for (T i : items) push(i);
  queue_.print();
}

template <typename T, typename _container>
s21::queue<T, _container>::queue(const queue &q) : queue_(q.queue_) {}

template <typename T, typename _container>
s21::queue<T, _container>::queue(queue &&q) : queue_(std::move(q.queue_)) {}

template <typename T, typename _container>
s21::queue<T, _container> &s21::queue<T, _container>::operator=(queue &&q) {
  if (this != &q) {
    queue_ = std::move(q.queue_);
  }
  return *this;
}

template <typename T, typename _container>
s21::queue<T, _container>::~queue() {}

template <typename T, typename _container>
bool s21::queue<T, _container>::empty() const noexcept {
  return queue_.empty();
}

template <typename T, typename _container>
size_t s21::queue<T, _container>::size() const noexcept {
  return queue_.size();
}

template <typename T, typename _container>
typename s21::queue<T, _container>::const_reference
s21::queue<T, _container>::front() const noexcept {
  return queue_.back();
}

template <typename T, typename _container>
typename s21::queue<T, _container>::const_reference
s21::queue<T, _container>::back() const noexcept {
  return queue_.front();
}

template <typename T, typename _container>
void s21::queue<T, _container>::pop() noexcept {
  queue_.pop_back();
}

template <typename T, typename _container>
void s21::queue<T, _container>::push(const_reference value) noexcept {
  queue_.push_front(value);
}

template <typename T, typename _container>
void s21::queue<T, _container>::swap(queue &other) noexcept {
  std::swap(queue_, other.queue_);
}

#endif

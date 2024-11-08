#ifndef S21_VECTOR
#define S21_VECTOR

#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

namespace s21 {
template <typename T, typename Allocator = std::allocator<T>>
class vector {
  using size_type = size_t;
  using value_type = T;
  using const_reference = const T&;
  using reference = T&;

 private:
  T* data_;
  size_type size_;
  size_type capacity_;
  Allocator allocator_;

 public:
  // Iterator
  class iterator {
   private:
    T* ptr_;

   public:
    iterator(T* ptr) : ptr_(ptr) {}
    reference operator*() const { return *ptr_; }
    iterator& operator++() {
      ++ptr_;
      return *this;
    }
    iterator& operator--() {
      --ptr_;
      return *this;
    }
    iterator operator+(std::ptrdiff_t n) { return iterator(ptr_ + n); }
    iterator operator-(std::ptrdiff_t n) { return iterator(ptr_ - n); }
    bool operator>(const iterator& other) const { return ptr_ > other.ptr_; }
    bool operator>=(const iterator& other) const { return ptr_ >= other.ptr_; }
    bool operator<(const iterator& other) const { return ptr_ < other.ptr_; }
    bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }
    T* get_ptr() { return ptr_; }
  };

  // Vector Member functions
  vector();
  vector(std::ptrdiff_t n);
  vector(const std::initializer_list<T>& items);
  vector(const vector& other);
  vector(vector&& other);
  vector& operator=(const vector& right);
  vector& operator=(vector&& right);
  ~vector();

  // Vector Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  reference front() const;
  reference back() const;

  // Vector Iterators
  iterator begin() const noexcept;
  iterator end() const noexcept;

  // Vector Capacity
  size_type size() const noexcept;  // O(1)
  size_type capacity() const noexcept;
  size_type max_size() const noexcept;
  bool empty() const noexcept;   // O(1)
  void reserve(size_type size);  // О(n)
  void shrink_to_fit();

  // Vector Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void push_back(const_reference value);
  void push_back(reference& value);
  void pop_back();
  void swap(vector& other);

  // Bonus
  template <typename... Args>
  iterator insert_many(iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  void insert_many_front(Args&&... args);

  // Other
  void print() const noexcept;
};
}  // namespace s21

template <typename T, typename Allocator>
s21::vector<T, Allocator>::vector() {
  size_ = 0;
  capacity_ = 0;
  data_ = nullptr;
}

template <typename T, typename Allocator>
s21::vector<T, Allocator>::vector(std::ptrdiff_t n) : size_(n), capacity_(n) {
  if (n < 0) {
    throw std::length_error("vector");
  }
  data_ = allocator_.allocate(n);
}

template <typename T, typename Allocator>
s21::vector<T, Allocator>::vector(const std::initializer_list<T>& items) {
  size_ = items.size();
  capacity_ = size_;
  data_ = allocator_.allocate(size_);
  std::uninitialized_copy(items.begin(), items.end(), data_);
}

template <typename T, typename Allocator>
s21::vector<T, Allocator>::vector(const vector& other)
    : size_(other.size_), capacity_(other.capacity_) {
  data_ = allocator_.allocate(capacity_);
  std::memcpy(data_, other.data_, capacity_ * sizeof(T));
}

template <typename T, typename Allocator>
s21::vector<T, Allocator>::vector(vector&& other)
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
  other.size_ = 0;
  other.capacity_ = 0;
  other.data_ = nullptr;
}

template <typename T, typename Allocator>
s21::vector<T, Allocator>& s21::vector<T, Allocator>::operator=(
    const vector& right) {
  if (this != &right) {
    allocator_.deallocate(data_, capacity_);
    for (size_type i = 0; i < size_; i++) {
      (data_ + i)->~T();  // (*(data_ + i)).~T();
    }
    size_ = right.size_;
    capacity_ = right.capacity_;
    data_ = allocator_.allocate(size_);
    for (size_type i = 0; i < size_; i++) {
      data_[i] = right.data_[i];
    }
  }
  return *this;
}

template <typename T, typename Allocator>
s21::vector<T, Allocator>& s21::vector<T, Allocator>::operator=(
    vector&& right) {
  if (this != &right) {
    allocator_.deallocate(
        data_, capacity_);  // сначала очищаем место для нового контейнера
    for (size_type i = 0; i < size_; i++) {
      (data_ + i)->~T();  // для вектора векторов
    }
    size_ = right.size_;
    capacity_ = right.capacity_;
    data_ = right.data_;
    right.size_ = 0;
    right.capacity_ = 0;
    right.data_ = nullptr;
  }
  return *this;
}

template <typename T, typename Allocator>
s21::vector<T, Allocator>::~vector() {
  if (data_) {
    allocator_.deallocate(data_, capacity_);
  }
}

template <typename T, typename Allocator>
typename s21::vector<T, Allocator>::reference s21::vector<T, Allocator>::at(
    size_type pos) {  // ОК
  if (pos >= size_ || pos < 0) throw std::out_of_range("Index out of range");
  return data_[pos];
}

template <typename T, typename Allocator>
typename s21::vector<T, Allocator>::reference
s21::vector<T, Allocator>::operator[](size_type pos) {
  // vec[pos] -> vec.operator[](pos) -> vec.at(pos) -> data_[pos]
  return at(pos);
}

template <typename T, typename Allocator>
typename s21::vector<T, Allocator>::reference s21::vector<T, Allocator>::front()
    const {  // ОК
  return data_[0];
}

template <typename T, typename Allocator>
typename s21::vector<T, Allocator>::reference s21::vector<T, Allocator>::back()
    const {  // ОК
  return data_[size_ - 1];
}

template <typename T, typename Allocator>
typename s21::vector<T, Allocator>::iterator s21::vector<T, Allocator>::begin()
    const noexcept {
  // std::cout << *(data_) << std::endl;
  // when forming return value, compiler created new iterator
  // using default constructor with given argument `T* data_`
  return data_;
}

template <typename T, typename Allocator>
typename s21::vector<T, Allocator>::iterator s21::vector<T, Allocator>::end()
    const noexcept {
  // std::cout << *(data_ + size_ - 1) << std::endl;
  return data_ + size_;
}

template <typename T, typename Allocator>
typename s21::vector<T, Allocator>::size_type s21::vector<T, Allocator>::size()
    const noexcept {
  return size_;
}

template <typename T, typename Allocator>
typename s21::vector<T, Allocator>::size_type
s21::vector<T, Allocator>::capacity() const noexcept {
  return capacity_;
}  // ОК O(1)

template <typename T, typename Allocator>
typename s21::vector<T, Allocator>::size_type
s21::vector<T, Allocator>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(T);
}

template <typename T, typename Allocator>
bool s21::vector<T, Allocator>::empty() const noexcept {
  return size_ == 0;
}

template <typename T, typename Allocator>
void s21::vector<T, Allocator>::reserve(size_type size) {  // О(n)
  if (size > capacity_ && size < max_size()) {
    T* new_data = allocator_.allocate(size);
    for (size_type i = 0; i < size_; ++i) {
      new_data[i] = std::move(data_[i]);
    }
    if (data_) {
      allocator_.deallocate(data_, capacity_);
    }
    data_ = new_data;
    capacity_ = size;
  }
}

template <typename T, typename Allocator>
void s21::vector<T, Allocator>::shrink_to_fit() {
  if (size_ < capacity_) {
    int* new_data = allocator_.allocate(size_);
    for (size_type i = 0; i < size_; ++i) {
      new_data[i] = std::move(
          data_[i]);  // поскольку = перегружено для rvalue через &&, мы
                      // избегаем копирования, то есть передается только
                      // указатель, доступ к старым данным обрубается
      // а копирование нужно в тех случаях, когда из копирующего(lvalue) массива
      // не удалялись элементы
    }
    if (data_) {
      allocator_.deallocate(data_, capacity_);
    }
    data_ = new_data;
    capacity_ = size_;
  }
}

template <typename T, typename Allocator>
void s21::vector<T,
                 Allocator>::clear() {  // capacity_ остается, size_ зануляется
  for (size_type i = 0; i < size_; i++) {
    data_[i].~T();
  }
  size_ = 0;
}

template <typename T, typename Allocator>
typename s21::vector<T, Allocator>::iterator s21::vector<T, Allocator>::insert(
    iterator pos,
    const_reference value) {  //  vec1.insert(vec1.begin() + 3, 0);
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("vector");
  }

  size_t index = 0;
  while (data_ + index != pos.get_ptr()) ++index;

  if (size_ == capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }

  print();

  size_t counter = 0;
  iterator iter = end();  // end указывает на последний элемент, потому что
                          // size_ еще не увеличился
  while (counter != (size_ - index)) {
    *iter = std::move(*(iter - 1));
    counter++;
    --iter;
  }

  *iter = value;
  ++size_;

  return iter;
}

template <typename T, typename Allocator>
void s21::vector<T, Allocator>::push_back(const_reference value) {
  // int a = 3; vec.push_back(a);
  if (size_ + 1 > capacity_) {
    reserve(size_ == 0 ? 1 : capacity_ * 2);
  }
  data_[size_] = value;
  ++size_;
}

template <typename T, typename Allocator>
void s21::vector<T, Allocator>::push_back(reference& value) {
  if (size_ == 0) {
    reserve(size_ + 1);  //
  } else if (size_ + 1 > capacity_) {
    reserve(capacity_ * 2);
  }
  data_[size_] = std::move(value);  // `value` IS ALREADY R-VALUE
  ++size_;
}

template <typename T, typename Allocator>
void s21::vector<T, Allocator>::pop_back() {
  if (size_ > 0) {
    data_[size_ - 1] = 0;
    --size_;
  }
}

template <typename T, typename Allocator>
void s21::vector<T, Allocator>::swap(vector& other) {
  std::swap(data_, other.data_);
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
}

template <typename T, typename Allocator>
template <typename... Args>
typename s21::vector<T, Allocator>::iterator
s21::vector<T, Allocator>::insert_many(iterator pos, Args&&... args) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("vector");
  }

  size_t index = 0;
  while (data_ + index != pos.get_ptr()) ++index;

  vector<T> temp_vector({std::forward<Args>(args)...});
  size_t temp_size = temp_vector.size();

  if (size_ + temp_size > capacity_) {
    reserve(capacity_ == 0 ? temp_size : capacity_ * 2);
  }

  size_t counter = 0;
  iterator iter = end();
  while (counter < size_ - index) {
    *(iter + temp_size - 1) = std::move(*(iter - 1));
    counter++;
    --iter;
  }

  for (size_t i = 0; i < temp_size; ++i) {
    *(begin() + index + i) = std::move(temp_vector[i]);
  }

  size_ += temp_size;

  return begin() + index;
}

template <typename T, typename Allocator>
template <typename... Args>
void s21::vector<T, Allocator>::insert_many_back(Args&&... args) {
  (push_back(args), ...);
}

template <typename T, typename Allocator>
template <typename... Args>
void s21::vector<T, Allocator>::insert_many_front(Args&&... args) {
  vector<T> temp_vector({args...});
  size_type temp_size = temp_vector.size();
  size_type new_size = temp_size + size_;

  if (new_size > capacity_) {
    reserve(new_size > capacity_ * 2 ? new_size : capacity_ * 2);
  }

  for (iterator iter = end() + temp_size - 1; iter != begin() + temp_size - 1;
       --iter) {
    *(iter) = std::move(*(iter - temp_size));
  }

  for (size_type i = 0; i < temp_size; ++i) {
    *(begin() + i) = std::move(temp_vector[i]);
  }

  size_ = new_size;
}

template <typename T, typename Allocator>
void s21::vector<T, Allocator>::print() const noexcept {
  for (auto& item : *this) std::cout << item << " ";
}

#endif
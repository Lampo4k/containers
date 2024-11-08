#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../s21_library/s21_vector.h"

// Тест для конструктора по умолчанию
TEST(VectorTests, DefaultConstructor) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  EXPECT_EQ(s21_vec.begin(), s21_vec.end());
  EXPECT_EQ(std_vec.begin(), std_vec.end());
}

// Тест для конструктора с размером
TEST(VectorTests, SizeConstructor) {
  s21::vector<int> s21_vec(5);
  std::vector<int> std_vec(5);
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorTests, InitializerListConstructor) {
  s21::vector<int> s21_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());

  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

// Тест для конструктора копирования
TEST(VectorTests, CopyConstructor) {
  s21::vector<int> s21_vec1{1, 2, 3, 4, 5};
  s21::vector<int> s21_vec2(s21_vec1);

  std::vector<int> std_vec1{1, 2, 3, 4, 5};
  std::vector<int> std_vec2(std_vec1);

  EXPECT_EQ(s21_vec2.size(), std_vec2.size());
  EXPECT_EQ(s21_vec2.capacity(), std_vec2.capacity());
  for (size_t i = 0; i < s21_vec1.size(); ++i) {
    EXPECT_EQ(s21_vec2[i], std_vec2[i]);
  }

  s21_vec1[0] = 10;
  std_vec1[0] = 10;
  EXPECT_EQ(s21_vec2[0], 1);  // Проверка на глубокое копирование
  EXPECT_EQ(std_vec2[0], 1);  // Проверка на глубокое копирование
}

// Тест для конструктора перемещения
TEST(VectorTests, MoveConstructor) {
  s21::vector<int> s21_vec1{1, 2, 3, 4, 5};
  s21::vector<int> s21_vec2(std::move(s21_vec1));

  std::vector<int> std_vec1{1, 2, 3, 4, 5};
  std::vector<int> std_vec2(std::move(std_vec1));

  EXPECT_EQ(s21_vec2.size(), std_vec2.size());
  EXPECT_EQ(s21_vec2.capacity(), std_vec2.capacity());
  EXPECT_EQ(s21_vec2[0], std_vec2[0]);
  EXPECT_EQ(s21_vec2[4], std_vec2[4]);

  EXPECT_EQ(s21_vec1.size(), std_vec1.size());
  EXPECT_EQ(s21_vec1.capacity(), std_vec1.capacity());
  EXPECT_EQ(s21_vec1.begin(), s21_vec1.end());
  EXPECT_EQ(std_vec1.begin(), std_vec1.end());
}

// Тест для оператора присваивания копированием
TEST(VectorTests, CopyAssignment) {
  s21::vector<int> s21_vec1{1, 2, 3, 4, 5};
  s21::vector<int> s21_vec2;
  s21_vec2 = s21_vec1;

  std::vector<int> std_vec1{1, 2, 3, 4, 5};
  std::vector<int> std_vec2;
  std_vec2 = std_vec1;

  EXPECT_EQ(s21_vec2.size(), std_vec2.size());
  EXPECT_EQ(s21_vec2.capacity(), std_vec2.capacity());
  for (size_t i = 0; i < s21_vec1.size(); ++i) {
    EXPECT_EQ(s21_vec2[i], std_vec2[i]);
  }

  s21_vec1[0] = 10;
  std_vec1[0] = 10;
  EXPECT_EQ(s21_vec2[0], std_vec2[0]);  // Проверка на глубокое копирование
}

// Тест для оператора присваивания перемещением
TEST(VectorTests, MoveAssignment) {
  s21::vector<int> s21_vec1{1, 2, 3, 4, 5};
  s21::vector<int> s21_vec2;
  s21_vec2 = std::move(s21_vec1);

  std::vector<int> std_vec1{1, 2, 3, 4, 5};
  std::vector<int> std_vec2;
  std_vec2 = std::move(std_vec1);

  EXPECT_EQ(s21_vec2.size(), std_vec2.size());
  EXPECT_EQ(s21_vec2.capacity(), std_vec2.capacity());
  EXPECT_EQ(s21_vec2[0], std_vec2[0]);
  EXPECT_EQ(s21_vec2[4], std_vec2[4]);

  EXPECT_EQ(s21_vec1.size(), std_vec1.size());
  EXPECT_EQ(s21_vec1.capacity(), std_vec1.capacity());
  EXPECT_EQ(s21_vec1.begin(), s21_vec1.end());
  EXPECT_EQ(std_vec1.begin(), std_vec1.end());
}

// Тест для метода at() с корректными и некорректными индексами
TEST(VectorTests, AtMethod) {
  s21::vector<int> s21_vec{1, 2, 3, 4, 5};
  std::vector<int> std_vec{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_vec.at(0), std_vec.at(0));
  EXPECT_EQ(s21_vec.at(4), std_vec.at(4));
  EXPECT_THROW(s21_vec.at(5), std::out_of_range);
  EXPECT_THROW(std_vec.at(5), std::out_of_range);
}

// Тест для оператора []
TEST(VectorTests, OperatorSquareBrackets) {
  s21::vector<int> s21_vec{1, 2, 3, 4, 5};
  std::vector<int> std_vec{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_vec[0], std_vec[0]);
  EXPECT_EQ(s21_vec[4], std_vec[4]);
}

// Тест для метода push_back()
TEST(VectorTests, PushBack) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  s21_vec.push_back(1);
  std_vec.push_back(1);
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  EXPECT_EQ(s21_vec[0], std_vec[0]);

  s21_vec.push_back(2);
  std_vec.push_back(2);
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  EXPECT_EQ(s21_vec[1], std_vec[1]);
}

TEST(VectorTests, SizeMethod) {
  s21::vector<int> s21_vec{1, 2, 3, 4, 5};
  std::vector<int> std_vec{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_vec.size(), std_vec.size());

  s21_vec.push_back(6);
  std_vec.push_back(6);
  EXPECT_EQ(s21_vec.size(), std_vec.size());

  s21_vec.pop_back();
  std_vec.pop_back();
  EXPECT_EQ(s21_vec.size(), std_vec.size());
}

// Тест для метода capacity()
TEST(VectorTests, CapacityMethod) {
  s21::vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());

  s21_vec.reserve(10);
  std_vec.reserve(10);
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());

  s21_vec.push_back(4);
  std_vec.push_back(4);
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
}

// Тест для метода max_size()
TEST(VectorTests, MaxSizeMethod) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  EXPECT_EQ(s21_vec.max_size(), std_vec.max_size());
}

// Тест для метода empty()
TEST(VectorTests, EmptyMethod) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  EXPECT_EQ(s21_vec.empty(),
            std_vec.empty());  // Вектор должен быть пустым после создания

  s21_vec.push_back(1);
  std_vec.push_back(1);
  EXPECT_EQ(s21_vec.empty(), std_vec.empty());  // Вектор не должен быть пустым
                                                // после добавления элемента

  s21_vec.clear();
  std_vec.clear();
  EXPECT_EQ(s21_vec.empty(), std_vec.empty());
}

// Тест для метода reserve(size_t size)
TEST(VectorTests, ReserveMethod) {
  s21::vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  s21_vec.reserve(10);
  std_vec.reserve(10);

  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  EXPECT_EQ(s21_vec.size(), std_vec.size());

  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

// Тест для метода shrink_to_fit()
TEST(VectorTests, ShrinkToFitMethod) {
  s21::vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  s21_vec.reserve(10);
  std_vec.reserve(10);
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());

  s21_vec.shrink_to_fit();
  std_vec.shrink_to_fit();
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  EXPECT_EQ(s21_vec.size(), std_vec.size());

  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

// Тест для метода clear()
TEST(VectorTests, ClearMethod) {
  s21::vector<int> s21_vec{1, 2, 3};
  std::vector<int> std_vec{1, 2, 3};

  s21_vec.clear();
  std_vec.clear();

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.empty(), std_vec.empty());
}

// Тест для метода insert(iterator pos, const T& value)
TEST(VectorTests, InsertMethod) {
  s21::vector<int> s21_vec{1, 2, 4, 5};
  std::vector<int> std_vec{1, 2, 4, 5};

  s21_vec.insert(s21_vec.begin() + 1, 3);
  std_vec.insert(std_vec.begin() + 1, 3);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

// Тест для push_back с копированием
TEST(VectorTests, PushBackCopy) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  s21_vec.push_back(1);
  s21_vec.push_back(2);
  s21_vec.push_back(3);

  std_vec.push_back(1);
  std_vec.push_back(2);
  std_vec.push_back(3);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

// Тест для push_back с перемещением
TEST(VectorTests, PushBackMove) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  int s1 = 2;
  int s2 = 2;
  int s3 = 2;

  s21_vec.push_back(std::move(s1));
  s21_vec.push_back(std::move(s2));
  s21_vec.push_back(std::move(s3));

  std_vec.push_back(2);
  std_vec.push_back(2);
  std_vec.push_back(2);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

// Тест для pop_back
TEST(VectorTests, PopBack) {
  s21::vector<int> s21_vec = {1, 2, 3};
  std::vector<int> std_vec = {1, 2, 3};

  s21_vec.pop_back();
  std_vec.pop_back();

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }

  s21_vec.pop_back();
  std_vec.pop_back();

  s21_vec.pop_back();
  std_vec.pop_back();

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
}

// Тест для swap
TEST(VectorTests, Swap) {
  s21::vector<int> s21_vec1 = {1, 2, 3};
  s21::vector<int> s21_vec2 = {4, 5};

  std::vector<int> std_vec1 = {1, 2, 3};
  std::vector<int> std_vec2 = {4, 5};

  s21_vec1.swap(s21_vec2);
  std_vec1.swap(std_vec2);

  EXPECT_EQ(s21_vec1.size(), std_vec1.size());
  EXPECT_EQ(s21_vec2.size(), std_vec2.size());
  for (size_t i = 0; i < s21_vec1.size(); ++i) {
    EXPECT_EQ(s21_vec1[i], std_vec1[i]);
  }
  for (size_t i = 0; i < s21_vec2.size(); ++i) {
    EXPECT_EQ(s21_vec2[i], std_vec2[i]);
  }
}

// Тест для insert_many
TEST(VectorTests, InsertMany) {
  s21::vector<int> s21_vec = {1, 2, 5};
  std::vector<int> std_vec = {1, 2, 5};

  s21_vec.insert_many(s21_vec.begin() + 2, 3, 4);
  std_vec.insert(std_vec.begin() + 2, {3, 4});

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

// Тест для insert_many_back
TEST(VectorTests, InsertManyBack) {
  s21::vector<int> s21_vec = {1, 2};
  std::vector<int> std_vec = {1, 2};

  s21_vec.insert_many_back(3, 4, 5);
  std_vec.insert(std_vec.end(), {3, 4, 5});

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

// Тест для insert_many_front
TEST(VectorTests, InsertManyFront) {
  s21::vector<int> s21_vec = {4, 5};
  std::vector<int> std_vec = {4, 5};

  s21_vec.insert_many_front(1, 2, 3);
  std_vec.insert(std_vec.begin(), {1, 2, 3});

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}
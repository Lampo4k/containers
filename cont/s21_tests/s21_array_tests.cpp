#include <gtest/gtest.h>

#include <array>
#include <iostream>

#include "../s21_library/s21_array.h"

// Тест для конструктора по умолчанию
TEST(ArrayTests, DefaultConstructor) {
  s21::array<int, 0> s21_arr;
  std::array<int, 0> std_arr;
  EXPECT_EQ(s21_arr.size(), std_arr.size());
  EXPECT_EQ(s21_arr.begin(), s21_arr.end());
  EXPECT_EQ(std_arr.begin(), std_arr.end());
}

// Тест для конструктора с размером
TEST(ArrayTests, SizeConstructor) {
  s21::array<int, 5> s21_arr;
  std::array<int, 5> std_arr = {0};
  EXPECT_EQ(s21_arr.size(), std_arr.size());
  for (size_t i = 0; i < s21_arr.size(); ++i) {
    EXPECT_EQ(s21_arr[i],
              std_arr[i]);  // Предполагаем, что элементы инициализируются нулем
  }
}

// Тест для конструктора с инициализатором списка
TEST(ArrayTests, InitializerListConstructor) {
  s21::array<int, 5> s21_arr = {1, 2, 3, 4, 5};
  std::array<int, 5> std_arr = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_arr.size(), std_arr.size());

  for (size_t i = 0; i < s21_arr.size(); ++i) {
    EXPECT_EQ(s21_arr[i], std_arr[i]);
  }
}

// Тест для конструктора копирования
TEST(ArrayTests, CopyConstructor) {
  s21::array<int, 5> s21_arr1{1, 2, 3, 4, 5};
  s21::array<int, 5> s21_arr2(s21_arr1);

  std::array<int, 5> std_arr1{1, 2, 3, 4, 5};
  std::array<int, 5> std_arr2(std_arr1);

  EXPECT_EQ(s21_arr2.size(), std_arr2.size());
  for (size_t i = 0; i < s21_arr1.size(); ++i) {
    EXPECT_EQ(s21_arr2[i], std_arr2[i]);
  }

  s21_arr1[0] = 10;
  std_arr1[0] = 10;
  EXPECT_EQ(s21_arr2[0], std_arr2[0]);  // Проверка на глубокое копирование
}

// Тест для конструктора перемещения
TEST(ArrayTests, MoveConstructor) {
  s21::array<int, 5> s21_arr1{1, 2, 3, 4, 5};
  s21::array<int, 5> s21_arr2(std::move(s21_arr1));

  std::array<int, 5> std_arr1{1, 2, 3, 4, 5};
  std::array<int, 5> std_arr2(std::move(std_arr1));

  EXPECT_EQ(s21_arr2.size(), std_arr2.size());
  EXPECT_EQ(s21_arr2[0], std_arr2[0]);
  EXPECT_EQ(s21_arr2[4], std_arr2[4]);
}

// Тест для метода at()
TEST(ArrayTests, AtMethod) {
  s21::array<int, 5> s21_arr{1, 2, 3, 4, 5};
  std::array<int, 5> std_arr{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_arr.at(0), std_arr.at(0));
  EXPECT_EQ(s21_arr.at(4), std_arr.at(4));
  EXPECT_THROW(s21_arr.at(5), std::out_of_range);
  EXPECT_THROW(std_arr.at(5), std::out_of_range);
}

// Тест для оператора []
TEST(ArrayTests, OperatorSquareBrackets) {
  s21::array<int, 5> s21_arr{1, 2, 3, 4, 5};
  std::array<int, 5> std_arr{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_arr[0], std_arr[0]);
  EXPECT_EQ(s21_arr[4], std_arr[4]);
}

// Тест для метода size()
TEST(ArrayTests, SizeMethod) {
  s21::array<int, 5> s21_arr{1, 2, 3, 4, 5};
  std::array<int, 5> std_arr{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_arr.size(), std_arr.size());
}

// Тест для метода fill()
TEST(ArrayTests, FillMethod) {
  s21::array<int, 5> s21_arr;
  std::array<int, 5> std_arr;

  s21_arr.fill(7);
  std_arr.fill(7);

  for (size_t i = 0; i < s21_arr.size(); ++i) {
    EXPECT_EQ(s21_arr[i], std_arr[i]);
  }
}

// Тест для метода swap()
TEST(ArrayTests, SwapMethod) {
  s21::array<int, 5> s21_arr1{1, 2, 3, 4, 5};
  s21::array<int, 5> s21_arr2{6, 7, 8, 9, 10};

  std::array<int, 5> std_arr1{1, 2, 3, 4, 5};
  std::array<int, 5> std_arr2{6, 7, 8, 9, 10};

  s21_arr1.swap(s21_arr2);
  std_arr1.swap(std_arr2);

  for (size_t i = 0; i < s21_arr1.size(); ++i) {
    EXPECT_EQ(s21_arr1[i], std_arr1[i]);
    EXPECT_EQ(s21_arr2[i], std_arr2[i]);
  }
}

// Тест для методов front() и back()
TEST(ArrayTests, FrontBackMethods) {
  s21::array<int, 5> s21_arr{1, 2, 3, 4, 5};
  std::array<int, 5> std_arr{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_arr.front(), std_arr.front());
  EXPECT_EQ(s21_arr.back(), std_arr.back());
}
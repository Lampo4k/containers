#include <gtest/gtest.h>

#include <stack>

#include "../s21_library/s21_stack.h"
#include "../s21_library/s21_vector.h"

// Тест для конструктора по умолчанию
TEST(StackTests, DefaultConstructor) {
  s21::stack<int> s21_s;
  std::stack<int> std_s;
  EXPECT_TRUE(s21_s.empty());
  EXPECT_EQ(s21_s.size(), std_s.size());
}

// Тест для конструктора с инициализатором списка
TEST(StackTests, InitializerListConstructor) {
  s21::stack<int> s21_s = {1, 2, 3, 4, 5};
  std::stack<int> std_s;
  std::initializer_list<int> init_list = {1, 2, 3, 4, 5};
  for (auto it = init_list.begin(); it != init_list.end(); ++it) {
    std_s.push(*it);
  }
  EXPECT_EQ(s21_s.size(), std_s.size());
  EXPECT_EQ(s21_s.top(), std_s.top());
}

// Тест для конструктора копирования
TEST(StackTests, CopyConstructor) {
  s21::stack<int> s21_s1 = {1, 2, 3, 4, 5};
  s21::stack<int> s21_s2(s21_s1);

  std::stack<int> std_s1;
  std::initializer_list<int> init_list = {1, 2, 3, 4, 5};
  for (auto it = init_list.begin(); it != init_list.end(); ++it) {
    std_s1.push(*it);
  }
  std::stack<int> std_s2(std_s1);

  EXPECT_EQ(s21_s2.size(), std_s2.size());
  EXPECT_EQ(s21_s2.top(), std_s2.top());
}

// Тест для конструктора перемещения
TEST(StackTests, MoveConstructor) {
  s21::stack<int> s21_s1 = {1, 2, 3, 4, 5};
  s21::stack<int> s21_s2(std::move(s21_s1));

  std::stack<int> std_s1;
  std::initializer_list<int> init_list = {1, 2, 3, 4, 5};
  for (auto it = init_list.begin(); it != init_list.end(); ++it) {
    std_s1.push(*it);
  }
  std::stack<int> std_s2(std::move(std_s1));

  EXPECT_EQ(s21_s2.size(), std_s2.size());
  EXPECT_EQ(s21_s2.top(), std_s2.top());
  EXPECT_TRUE(s21_s1.empty());
  EXPECT_TRUE(std_s1.empty());
}

// Тест для оператора присваивания перемещением
TEST(StackTests, MoveAssignment) {
  s21::stack<int> s21_s1 = {1, 2, 3, 4, 5};
  s21::stack<int> s21_s2;
  s21_s2 = std::move(s21_s1);

  std::stack<int> std_s1;
  std::initializer_list<int> init_list = {1, 2, 3, 4, 5};
  for (auto it = init_list.begin(); it != init_list.end(); ++it) {
    std_s1.push(*it);
  }
  std::stack<int> std_s2;
  std_s2 = std::move(std_s1);

  EXPECT_EQ(s21_s2.size(), std_s2.size());
  EXPECT_EQ(s21_s2.top(), std_s2.top());
  EXPECT_TRUE(s21_s1.empty());
  EXPECT_TRUE(std_s1.empty());
}

// Тест для метода top()
TEST(StackTests, TopMethod) {
  s21::stack<int> s21_s = {1, 2, 3, 4, 5};
  std::stack<int> std_s;
  std::initializer_list<int> init_list = {1, 2, 3, 4, 5};
  for (auto it = init_list.begin(); it != init_list.end(); ++it) {
    std_s.push(*it);
  }

  EXPECT_EQ(s21_s.top(), std_s.top());
  s21_s.pop();
  std_s.pop();
  EXPECT_EQ(s21_s.top(), std_s.top());
}

// Тест для метода empty()
TEST(StackTests, EmptyMethod) {
  s21::stack<int> s21_s;
  std::stack<int> std_s;
  EXPECT_EQ(s21_s.empty(), std_s.empty());
  s21_s.push(1);
  std_s.push(1);
  EXPECT_EQ(s21_s.empty(), std_s.empty());
}

// Тест для метода size()
TEST(StackTests, SizeMethod) {
  s21::stack<int> s21_s;
  std::stack<int> std_s;
  EXPECT_EQ(s21_s.size(), std_s.size());
  s21_s.push(1);
  std_s.push(1);
  EXPECT_EQ(s21_s.size(), std_s.size());
  s21_s.push(2);
  std_s.push(2);
  EXPECT_EQ(s21_s.size(), std_s.size());
}

// Тест для метода push()
TEST(StackTests, PushMethod) {
  s21::stack<int> s21_s;
  std::stack<int> std_s;
  s21_s.push(1);
  std_s.push(1);
  EXPECT_EQ(s21_s.size(), std_s.size());
  EXPECT_EQ(s21_s.top(), std_s.top());
  s21_s.push(2);
  std_s.push(2);
  EXPECT_EQ(s21_s.size(), std_s.size());
  EXPECT_EQ(s21_s.top(), std_s.top());
}

// Тест для метода pop()
TEST(StackTests, PopMethod) {
  s21::stack<int> s21_s = {1, 2, 3};
  std::stack<int> std_s;
  std::initializer_list<int> init_list = {1, 2, 3};
  for (auto it = init_list.begin(); it != init_list.end(); ++it) {
    std_s.push(*it);
  }

  s21_s.pop();
  std_s.pop();
  EXPECT_EQ(s21_s.size(), std_s.size());
  EXPECT_EQ(s21_s.top(), std_s.top());
  s21_s.pop();
  std_s.pop();
  EXPECT_EQ(s21_s.size(), std_s.size());
  EXPECT_EQ(s21_s.top(), std_s.top());
  s21_s.pop();
  std_s.pop();
  EXPECT_TRUE(s21_s.empty());
  EXPECT_TRUE(std_s.empty());
}

// Тест для метода swap()
TEST(StackTests, SwapMethod) {
  s21::stack<int> s21_s1 = {1, 2, 3};
  s21::stack<int> s21_s2 = {4, 5, 6};

  std::stack<int> std_s1;
  std::initializer_list<int> init_list1 = {1, 2, 3};
  for (auto it = init_list1.begin(); it != init_list1.end(); ++it) {
    std_s1.push(*it);
  }

  std::stack<int> std_s2;
  std::initializer_list<int> init_list2 = {4, 5, 6};
  for (auto it = init_list2.begin(); it != init_list2.end(); ++it) {
    std_s2.push(*it);
  }

  s21_s1.swap(s21_s2);
  std_s1.swap(std_s2);

  EXPECT_EQ(s21_s1.top(), std_s1.top());
  EXPECT_EQ(s21_s2.top(), std_s2.top());
}
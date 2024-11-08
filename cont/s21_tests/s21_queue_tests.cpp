#include <gtest/gtest.h>

#include <queue>

#include "../s21_library/s21_queue.h"

// Тест для конструктора по умолчанию
TEST(QueueTests, DefaultConstructor) {
  s21::queue<int> s21_q;
  std::queue<int> std_q;
  EXPECT_TRUE(s21_q.empty());
  EXPECT_EQ(s21_q.size(), std_q.size());
}

// Тест для конструктора с инициализатором списка
TEST(QueueTests, InitializerListConstructor) {
  s21::queue<int> s21_q = {1, 2, 3, 4, 5};
  std::queue<int> std_q;
  for (int i : {1, 2, 3, 4, 5}) {
    std_q.push(i);
  }
  EXPECT_EQ(s21_q.size(), std_q.size());
  EXPECT_EQ(s21_q.front(), std_q.front());
  EXPECT_EQ(s21_q.back(), std_q.back());
}

// Тест для конструктора копирования
TEST(QueueTests, CopyConstructor) {
  s21::queue<int> s21_q1 = {1, 2, 3, 4, 5};
  s21::queue<int> s21_q2(s21_q1);

  std::queue<int> std_q1;
  for (int i : {1, 2, 3, 4, 5}) {
    std_q1.push(i);
  }
  std::queue<int> std_q2(std_q1);

  EXPECT_EQ(s21_q2.size(), std_q2.size());
  EXPECT_EQ(s21_q2.front(), std_q2.front());
  EXPECT_EQ(s21_q2.back(), std_q2.back());
}

// Тест для конструктора перемещения
TEST(QueueTests, MoveConstructor) {
  s21::queue<int> s21_q1 = {1, 2, 3, 4, 5};
  s21::queue<int> s21_q2(std::move(s21_q1));

  std::queue<int> std_q1;
  for (int i : {1, 2, 3, 4, 5}) {
    std_q1.push(i);
  }
  std::queue<int> std_q2(std::move(std_q1));

  EXPECT_EQ(s21_q2.size(), std_q2.size());
  EXPECT_EQ(s21_q2.front(), std_q2.front());
  EXPECT_EQ(s21_q2.back(), std_q2.back());
  EXPECT_TRUE(s21_q1.empty());
  EXPECT_TRUE(std_q1.empty());
}

// Тест для оператора присваивания перемещением
TEST(QueueTests, MoveAssignment) {
  s21::queue<int> s21_q1 = {1, 2, 3, 4, 5};
  s21::queue<int> s21_q2;
  s21_q2 = std::move(s21_q1);

  std::queue<int> std_q1;
  for (int i : {1, 2, 3, 4, 5}) {
    std_q1.push(i);
  }
  std::queue<int> std_q2;
  std_q2 = std::move(std_q1);

  EXPECT_EQ(s21_q2.size(), std_q2.size());
  EXPECT_EQ(s21_q2.front(), std_q2.front());
  EXPECT_EQ(s21_q2.back(), std_q2.back());
  EXPECT_TRUE(s21_q1.empty());
  EXPECT_TRUE(std_q1.empty());
}

// Тест для метода front()
TEST(QueueTests, FrontMethod) {
  s21::queue<int> s21_q = {1, 2, 3, 4, 5};
  std::queue<int> std_q;
  for (int i : {1, 2, 3, 4, 5}) {
    std_q.push(i);
  }

  EXPECT_EQ(s21_q.front(), std_q.front());
  s21_q.pop();
  std_q.pop();
  EXPECT_EQ(s21_q.front(), std_q.front());
}

// Тест для метода back()
TEST(QueueTests, BackMethod) {
  s21::queue<int> s21_q = {1, 2, 3, 4, 5};
  std::queue<int> std_q;
  for (int i : {1, 2, 3, 4, 5}) {
    std_q.push(i);
  }

  EXPECT_EQ(s21_q.back(), std_q.back());
  s21_q.pop();
  std_q.pop();
  EXPECT_EQ(s21_q.back(), std_q.back());
}

// Тест для метода empty()
TEST(QueueTests, EmptyMethod) {
  s21::queue<int> s21_q;
  std::queue<int> std_q;
  EXPECT_EQ(s21_q.empty(), std_q.empty());
  s21_q.push(1);
  std_q.push(1);
  EXPECT_EQ(s21_q.empty(), std_q.empty());
}

// Тест для метода size()
TEST(QueueTests, SizeMethod) {
  s21::queue<int> s21_q;
  std::queue<int> std_q;
  EXPECT_EQ(s21_q.size(), std_q.size());
  s21_q.push(1);
  std_q.push(1);
  EXPECT_EQ(s21_q.size(), std_q.size());
  s21_q.push(2);
  std_q.push(2);
  EXPECT_EQ(s21_q.size(), std_q.size());
}

// Тест для метода push()
TEST(QueueTests, PushMethod) {
  s21::queue<int> s21_q;
  std::queue<int> std_q;
  s21_q.push(1);
  std_q.push(1);
  EXPECT_EQ(s21_q.size(), std_q.size());
  EXPECT_EQ(s21_q.front(), std_q.front());
  EXPECT_EQ(s21_q.back(), std_q.back());
  s21_q.push(2);
  std_q.push(2);
  EXPECT_EQ(s21_q.size(), std_q.size());
  EXPECT_EQ(s21_q.front(), std_q.front());
  EXPECT_EQ(s21_q.back(), std_q.back());
}

// Тест для метода pop()
TEST(QueueTests, PopMethod) {
  s21::queue<int> s21_q = {1, 2, 3};
  std::queue<int> std_q;
  for (int i : {1, 2, 3}) {
    std_q.push(i);
  }

  s21_q.pop();
  std_q.pop();
  EXPECT_EQ(s21_q.size(), std_q.size());
  EXPECT_EQ(s21_q.front(), std_q.front());
  s21_q.pop();
  std_q.pop();
  EXPECT_EQ(s21_q.size(), std_q.size());
  EXPECT_EQ(s21_q.front(), std_q.front());
}

// Тест для метода swap()
TEST(QueueTests, SwapMethod) {
  s21::queue<int> s21_q1 = {1, 2, 3};
  s21::queue<int> s21_q2 = {4, 5, 6};

  std::queue<int> std_q1;
  for (int i : {1, 2, 3}) {
    std_q1.push(i);
  }

  std::queue<int> std_q2;
  for (int i : {4, 5, 6}) {
    std_q2.push(i);
  }

  s21_q1.swap(s21_q2);
  std_q1.swap(std_q2);

  EXPECT_EQ(s21_q1.front(), std_q1.front());
  EXPECT_EQ(s21_q2.front(), std_q2.front());
  EXPECT_EQ(s21_q1.back(), std_q1.back());
  EXPECT_EQ(s21_q2.back(), std_q2.back());
}
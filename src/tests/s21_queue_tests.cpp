#include "s21_queue_tests.h"

TEST_F(S21QueueTests, NullConstructor) {
  s21::queue<int> q;

  EXPECT_EQ(q.size(), 0);
  EXPECT_EQ(q.empty(), true);
}

TEST_F(S21QueueTests, InitializerListConstructor) {
  s21::queue<int> testQueue{1, 2, 3, 4};

  EXPECT_EQ(testQueue.size(), 4);

  EXPECT_EQ(testQueue.front(), 1);
  EXPECT_EQ(testQueue.back(), 4);
}

TEST_F(S21QueueTests, CopyConstructor) {
  s21::queue<int> originalQueue{1, 2, 3};

  s21::queue<int> copiedQueue(originalQueue);

  EXPECT_EQ(copiedQueue.size(), 3);

  EXPECT_EQ(copiedQueue.front(), originalQueue.front());
  copiedQueue.pop();
  originalQueue.pop();
  EXPECT_EQ(copiedQueue.front(), originalQueue.front());
  copiedQueue.pop();
  originalQueue.pop();
  EXPECT_EQ(copiedQueue.front(), originalQueue.front());
}

TEST_F(S21QueueTests, MoveConstructor) {
  s21::queue<int> originalQueue;
  originalQueue.push(1);
  originalQueue.push(2);
  originalQueue.push(3);
  originalQueue.push(4);

  s21::queue<int> tempQueue(std::move(originalQueue));

  EXPECT_EQ(tempQueue.size(), 4);
  EXPECT_EQ(tempQueue.front(), 1);
  EXPECT_EQ(tempQueue.back(), 4);
  tempQueue.pop();
  EXPECT_EQ(tempQueue.front(), 2);
  tempQueue.pop();
  EXPECT_EQ(tempQueue.front(), 3);

  EXPECT_TRUE(originalQueue.empty());
}

TEST_F(S21QueueTests, OperatorMove) {
  s21::queue<int> originalQueue;
  originalQueue.push(1);
  originalQueue.push(2);
  originalQueue.push(3);
  originalQueue.push(4);

  s21::queue<int> tempQueue = std::move(originalQueue);

  EXPECT_EQ(tempQueue.size(), 4);
  EXPECT_EQ(tempQueue.front(), 1);
  EXPECT_EQ(tempQueue.back(), 4);

  EXPECT_TRUE(originalQueue.empty());
}

TEST_F(S21QueueTests, FrontEmpty) {
  s21::queue<int> testQueue;

  EXPECT_THROW(testQueue.front(), std::runtime_error);
}

TEST_F(S21QueueTests, FrontNotEmpty) {
  s21::queue<int> tempQueue;
  tempQueue.push(1);
  tempQueue.push(2);
  tempQueue.push(3);
  tempQueue.push(4);

  EXPECT_EQ(tempQueue.front(), 1);
  tempQueue.pop();
  EXPECT_EQ(tempQueue.front(), 2);
}

TEST_F(S21QueueTests, BackEmpty) {
  s21::queue<int> testQueue;

  EXPECT_THROW(testQueue.back(), std::runtime_error);
}

TEST_F(S21QueueTests, BackNotEmpty) {
  s21::queue<int> tempQueue;
  tempQueue.push(1);
  tempQueue.push(2);
  tempQueue.push(3);
  tempQueue.push(4);

  EXPECT_EQ(tempQueue.back(), 4);
}

TEST_F(S21QueueTests, Empty) {
  s21::queue<int> testQueue;

  EXPECT_TRUE(testQueue.empty());
}

TEST_F(S21QueueTests, NotEmpty) {
  s21::queue<int> testQueue;
  testQueue.push(1);

  EXPECT_FALSE(testQueue.empty());
}

TEST_F(S21QueueTests, SizeEmpty) {
  s21::queue<int> testQueue;

  EXPECT_EQ(testQueue.size(), 0);
}

TEST_F(S21QueueTests, SizeNotEmpty) {
  s21::queue<int> testQueue;
  testQueue.push(1);
  testQueue.push(2);
  testQueue.push(3);
  testQueue.push(4);

  EXPECT_EQ(testQueue.size(), 4);
}

TEST_F(S21QueueTests, Push) {
  s21::queue<int> testQueue;

  testQueue.push(1);
  EXPECT_EQ(testQueue.front(), 1);
  testQueue.push(2);
  EXPECT_EQ(testQueue.back(), 2);
  testQueue.push(3);
  EXPECT_EQ(testQueue.back(), 3);
}

TEST_F(S21QueueTests, PopEmpty) {
  s21::queue<int> testQueue;

  EXPECT_THROW(testQueue.pop(), std::runtime_error);
}

TEST_F(S21QueueTests, PopNotEmpty) {
  s21::queue<int> testQueue;
  testQueue.push(1);
  testQueue.push(2);
  testQueue.push(3);
  testQueue.push(4);

  EXPECT_EQ(testQueue.front(), 1);
  EXPECT_EQ(testQueue.back(), 4);
  testQueue.pop();
  EXPECT_EQ(testQueue.front(), 2);
  EXPECT_EQ(testQueue.back(), 4);
  testQueue.pop();
  EXPECT_EQ(testQueue.front(), 3);
  EXPECT_EQ(testQueue.back(), 4);
  testQueue.pop();
  testQueue.pop();

  EXPECT_TRUE(testQueue.empty());
}

TEST_F(S21QueueTests, SwapAllNotEmpty) {
  s21::queue<int> test1Queue;
  test1Queue.push(1);
  test1Queue.push(2);
  test1Queue.push(3);

  s21::queue<int> test2Queue;
  test2Queue.push(5);
  test2Queue.push(6);
  test2Queue.push(7);
  test2Queue.push(8);

  test1Queue.swap(test2Queue);

  EXPECT_EQ(test1Queue.size(), 4);
  EXPECT_EQ(test1Queue.front(), 5);
  EXPECT_EQ(test1Queue.back(), 8);

  EXPECT_EQ(test2Queue.size(), 3);
  EXPECT_EQ(test2Queue.front(), 1);
  EXPECT_EQ(test2Queue.back(), 3);
}

TEST_F(S21QueueTests, SwapOneEmpty) {
  s21::queue<int> test1Queue;
  test1Queue.push(1);
  test1Queue.push(2);
  test1Queue.push(3);

  s21::queue<int> test2Queue;

  test1Queue.swap(test2Queue);

  EXPECT_EQ(test1Queue.size(), 0);

  EXPECT_EQ(test2Queue.size(), 3);
  EXPECT_EQ(test2Queue.front(), 1);
  EXPECT_EQ(test2Queue.back(), 3);
}

TEST_F(S21QueueTests, SwapAllEmpty) {
  s21::queue<int> test1Queue;
  s21::queue<int> test2Queue;

  test1Queue.swap(test2Queue);

  EXPECT_EQ(test1Queue.size(), 0);

  EXPECT_EQ(test2Queue.size(), 0);
}

TEST_F(S21QueueTests, EmptyCopyCtor) {
  s21::queue<int> q2;
  s21::queue<int> q1(q2);

  EXPECT_EQ(q1.size(), 0);
}
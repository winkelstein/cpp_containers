#include "s21_stack_tests.h"

TEST_F(S21StackTests, NullConstructor) {
  s21::stack<int> l;

  EXPECT_EQ(l.size(), 0);
  EXPECT_EQ(l.empty(), true);
}

TEST_F(S21StackTests, InitializerListConstructor) {
  s21::stack<int> testStack{1, 2, 3};

  EXPECT_EQ(testStack.size(), 3);

  EXPECT_EQ(testStack.top(), 3);
  testStack.pop();
  EXPECT_EQ(testStack.top(), 2);
  testStack.pop();
  EXPECT_EQ(testStack.top(), 1);
  testStack.pop();

  EXPECT_TRUE(testStack.empty());
}

TEST_F(S21StackTests, CopyConstructor) {
  s21::stack<int> originalStack{1, 2, 3};

  s21::stack<int> copiedStack(originalStack);

  EXPECT_EQ(copiedStack.size(), originalStack.size());

  EXPECT_EQ(copiedStack.top(), originalStack.top());
  originalStack.pop();
  copiedStack.pop();
  EXPECT_EQ(copiedStack.top(), originalStack.top());
  originalStack.pop();
  copiedStack.pop();
  EXPECT_EQ(copiedStack.top(), originalStack.top());
  originalStack.pop();
  copiedStack.pop();

  EXPECT_TRUE(copiedStack.empty());
  EXPECT_TRUE(originalStack.empty());
}

TEST_F(S21StackTests, MoveConstructor) {
  s21::stack<int> originalStack{1, 2, 3};

  s21::stack<int> tempStack(std::move(originalStack));

  EXPECT_EQ(tempStack.size(), 3);
  EXPECT_EQ(tempStack.top(), 3);

  EXPECT_TRUE(originalStack.empty());
}

TEST_F(S21StackTests, OperatorMove) {
  s21::stack<int> originalStack{1, 2, 3};

  s21::stack<int> tempStack = std::move(originalStack);

  EXPECT_EQ(tempStack.size(), 3);
  EXPECT_EQ(tempStack.top(), 3);

  EXPECT_TRUE(originalStack.empty());
}

TEST_F(S21StackTests, TopEmpty) {
  s21::stack<int> testStack;

  EXPECT_THROW(testStack.top(), std::runtime_error);
}

TEST_F(S21StackTests, TopNotEmpty) {
  s21::stack<int> testStack{1, 2, 3};

  EXPECT_EQ(testStack.top(), 3);
  testStack.pop();
  EXPECT_EQ(testStack.top(), 2);
}

TEST_F(S21StackTests, Empty) {
  s21::stack<int> testStack;

  EXPECT_TRUE(testStack.empty());
}

TEST_F(S21StackTests, NotEmpty) {
  s21::stack<int> testStack{1, 2, 3};

  EXPECT_FALSE(testStack.empty());
}

TEST_F(S21StackTests, EmptySize) {
  s21::stack<int> testStack;

  EXPECT_EQ(testStack.size(), 0);
}

TEST_F(S21StackTests, NotEmptySize) {
  s21::stack<int> testStack{11, 11, 11, 55, 55, 55};

  EXPECT_EQ(testStack.size(), 6);
}

TEST_F(S21StackTests, Push) {
  s21::stack<int> testStack;

  testStack.push(1);
  EXPECT_EQ(testStack.size(), 1);
  EXPECT_EQ(testStack.top(), 1);
  testStack.push(2);
  EXPECT_EQ(testStack.size(), 2);
  EXPECT_EQ(testStack.top(), 2);
  testStack.push(3);
  EXPECT_EQ(testStack.size(), 3);
  EXPECT_EQ(testStack.top(), 3);
  testStack.push(4);
  EXPECT_EQ(testStack.size(), 4);
  EXPECT_EQ(testStack.top(), 4);
}

TEST_F(S21StackTests, PopEmpty) {
  s21::stack<int> testStack;

  EXPECT_THROW(testStack.pop(), std::runtime_error);
}

TEST_F(S21StackTests, Pop) {
  s21::stack<int> testStack;

  testStack.push(1);
  testStack.push(2);
  testStack.push(3);

  EXPECT_EQ(testStack.top(), 3);
  testStack.pop();

  EXPECT_EQ(testStack.size(), 2);
  EXPECT_EQ(testStack.top(), 2);

  testStack.pop();
  testStack.pop();

  EXPECT_TRUE(testStack.empty());
}

TEST_F(S21StackTests, Swap) {
  s21::stack<int> stack1{1, 2, 3};
  s21::stack<int> stack2{4, 5};

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 2);
  EXPECT_EQ(stack1.top(), 5);

  EXPECT_EQ(stack2.size(), 3);
  EXPECT_EQ(stack2.top(), 3);
}

TEST_F(S21StackTests, SwapOneEmpty) {
  s21::stack<int> stack1{1, 2, 3};
  s21::stack<int> stack2;

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 0);

  EXPECT_EQ(stack2.size(), 3);
  EXPECT_EQ(stack2.top(), 3);
}

TEST_F(S21StackTests, SwapAllEmpty) {
  s21::stack<int> stack1;
  s21::stack<int> stack2;

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 0);

  EXPECT_EQ(stack2.size(), 0);
}
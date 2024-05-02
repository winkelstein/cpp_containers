#include "s21_vector_tests.h"

// Test default constructor
TEST_F(S21VectorTests, SimpleCtor) {
  s21::vector<int> vec;

  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.empty(), true);
}

// Test initializer list constructor
TEST_F(S21VectorTests, InitializerListCtor) {
  s21::vector<int> vec = {1, 3, 9};

  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.empty(), false);

  EXPECT_EQ(vec.at(0), 1);
  EXPECT_EQ(vec.at(1), 3);
  EXPECT_EQ(vec.at(2), 9);
}

// Test copy constructor
TEST_F(S21VectorTests, CopyCtor) {
  s21::vector<int> vec = {1, 3, 9};
  s21::vector<int> vec1 = vec;

  EXPECT_EQ(vec.size(), vec1.size());
  EXPECT_EQ(vec.at(0), vec1.at(0));
}

// Test move constructor
TEST_F(S21VectorTests, MoveCtor) {
  s21::vector<int> vec = {1, 3, 9};
  s21::vector<int> vec2(std::move(vec));

  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec2.size(), 3);

  EXPECT_EQ(vec2.at(0), 1);
}

// Test move assignment operator
TEST_F(S21VectorTests, MoveOperatorAssignment) {
  s21::vector<int> vec = {1, 3, 9};
  s21::vector<int> vec2 = std::move(vec);

  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec2.size(), 3);

  EXPECT_EQ(vec2.at(0), 1);
}

// Test at() function
TEST_F(S21VectorTests, At) {
  s21::vector<int> vec = {1, 3, 9};

  EXPECT_EQ(vec.at(0), 1);
  EXPECT_EQ(vec.at(1), 3);
  EXPECT_EQ(vec.at(2), 9);

  EXPECT_THROW(vec.at(5), std::out_of_range);
}

// Test operator[] function
TEST_F(S21VectorTests, OperatorSquareBrackets) {
  s21::vector<int> vec = {1, 3, 9};

  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 3);
  EXPECT_EQ(vec[2], 9);

  EXPECT_EQ(vec.size(), 3);

  vec[1] = 93;

  EXPECT_EQ(vec.at(1), 93);
}

// Test begin() function
TEST_F(S21VectorTests, Begin) {
  s21::vector<int> vec = {1, 3, 9};

  EXPECT_EQ(*(vec.begin()), 1);
}

// Test end() function
TEST_F(S21VectorTests, End) {
  s21::vector<int> vec = {1, 3, 9};

  auto iter = --vec.end();
  EXPECT_EQ(*iter, 9);
}

// Test empty() function
TEST_F(S21VectorTests, Empty) {
  s21::vector<int> vec1;
  s21::vector<int> vec2 = {};
  s21::vector<int> vec3 = {5};
  s21::vector<int> vec4;

  vec4.push_back(5);

  EXPECT_TRUE(vec1.empty());
  EXPECT_TRUE(vec2.empty());
  EXPECT_FALSE(vec3.empty());
  EXPECT_FALSE(vec4.empty());
}

// Test size() function
TEST_F(S21VectorTests, Size) {
  s21::vector<int> vec1;
  s21::vector<int> vec2 = {};
  s21::vector<int> vec3 = {5};
  s21::vector<int> vec4 = {6};

  vec4.push_back(5);

  EXPECT_EQ(vec1.size(), 0);
  EXPECT_EQ(vec2.size(), 0);
  EXPECT_EQ(vec3.size(), 1);
  EXPECT_EQ(vec4.size(), 2);
}

// Test clear() function
TEST_F(S21VectorTests, Clear) {
  s21::vector<int> vec = {8, 5, 6, 3};

  EXPECT_EQ(vec.size(), 4);
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
}

// Test move assignment operator
TEST_F(S21VectorTests, MoveAssignmentOperator) {
  s21::vector<int> temp = {1, 2, 3};
  s21::vector<int> vec;
  vec = std::move(temp);
  EXPECT_EQ(temp.size(), 0);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

// Test iterator end() function
TEST_F(S21VectorTests, IteratorEnd) {
  s21::vector<int> vec = {1, 2, 3};
  auto iter = vec.end();
  EXPECT_EQ(iter, ++ ++ ++vec.begin());
}
// Test capacity() function
TEST_F(S21VectorTests, Capacity) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_GE(vec.capacity(), vec.size());
}

// Test max_size() function
TEST_F(S21VectorTests, MaxSize) {
  s21::vector<int> vec;
  EXPECT_LT(vec.max_size(), std::numeric_limits<size_t>::max());
}

// Test pop_back() function
TEST_F(S21VectorTests, PopBack) {
  s21::vector<int> vec = {1, 2, 3};
  vec.pop_back();
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.back(), 2);
}

// Test push_back() function
TEST_F(S21VectorTests, PushBack) {
  s21::vector<int> vec = {1, 2, 3};
  vec.push_back(4);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec.back(), 4);
}

// Test data() function
TEST_F(S21VectorTests, Data) {
  s21::vector<int> vec = {1, 2, 3};
  int* ptr = vec.data();
  EXPECT_EQ(*ptr, 1);
  // Modify the data using pointer and check if vector is modified
  *ptr = 10;
  EXPECT_EQ(vec[0], 10);
}

// Test front() function
TEST_F(S21VectorTests, Front) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.front(), 1);
}

// Test back() function
TEST_F(S21VectorTests, Back) {
  s21::vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.back(), 3);
}

// Test iterator equality operator
TEST_F(S21VectorTests, IteratorEqualityOperator) {
  s21::vector<int> vec = {1, 2, 3};
  auto iter1 = vec.begin();
  auto iter2 = vec.begin();
  EXPECT_TRUE(iter1 == iter2);
}

// Test iterator inequality operator
TEST_F(S21VectorTests, IteratorInequalityOperator) {
  s21::vector<int> vec = {1, 2, 3};
  auto iter1 = vec.begin();
  auto iter2 = vec.end();
  EXPECT_TRUE(iter1 != iter2);
}

// Test iterator increment operator
TEST_F(S21VectorTests, IteratorIncrementOperator) {
  s21::vector<int> vec = {1, 2, 3};
  auto iter = vec.begin();
  ++iter;
  EXPECT_EQ(*iter, 2);
}

// Test iterator decrement operator
TEST_F(S21VectorTests, IteratorDecrementOperator) {
  s21::vector<int> vec = {1, 2, 3};
  auto iter = vec.end();
  --iter;
  EXPECT_EQ(*iter, 3);
}

// Test iterator begin() function
TEST_F(S21VectorTests, IteratorBegin) {
  s21::vector<int> vec = {1, 2, 3};
  auto iter = vec.begin();
  EXPECT_EQ(*iter, 1);
}

// Test swap() function
TEST_F(S21VectorTests, Swap) {
  s21::vector<int> vec1 = {1, 2, 3};
  s21::vector<int> vec2 = {4, 5, 6};
  vec1.swap(vec2);
  EXPECT_EQ(vec1.size(), 3);
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec1[0], 4);
  EXPECT_EQ(vec1[1], 5);
  EXPECT_EQ(vec1[2], 6);
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 2);
  EXPECT_EQ(vec2[2], 3);
}

// Test reserve() function
TEST_F(S21VectorTests, Reserve) {
  s21::vector<int> vec;

  vec.reserve(10);

  EXPECT_EQ(vec.capacity(), 10);
}

// Test prefix and postfix increment and decrement operators for iterators
TEST_F(S21VectorTests, IteratorIncrementDecrementOperators) {
  s21::vector<int> vec = {1, 2, 3};
  auto it = vec.begin();
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(*(++it), 2);
  EXPECT_EQ(*it, 2);
  EXPECT_EQ(*(it++), 2);
  EXPECT_EQ(*it, 3);
  EXPECT_EQ(*(--it), 2);
  EXPECT_EQ(*it, 2);
  EXPECT_EQ(*(it--), 2);
  EXPECT_EQ(*it, 1);
}
// Test range-based for loop
TEST_F(S21VectorTests, RangeBasedForLoop) {
  s21::vector<int> vec = {1, 2, 3};
  int sum = 0;
  for (const auto& elem : vec) {
    sum += elem;
  }
  EXPECT_EQ(sum, 6);
}

// Test reserve with larger capacity
TEST_F(S21VectorTests, ReserveWithLargerCapacity) {
  s21::vector<int> vec = {1, 2, 3};
  vec.reserve(10);
  EXPECT_GE(vec.capacity(), 10);
}

// Test move constructor
TEST_F(S21VectorTests, MoveConstructor) {
  s21::vector<int> temp = {1, 2, 3};
  s21::vector<int> vec(std::move(temp));
  EXPECT_EQ(temp.size(), 0);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

// Test reserve() function with larger capacity
TEST_F(S21VectorTests, ReserveLargerCapacity) {
  s21::vector<int> vec = {1, 2, 3};
  vec.reserve(10);
  EXPECT_GE(vec.capacity(), 10);
}

// Test shrink_to_fit() function
TEST_F(S21VectorTests, ShrinkToFit) {
  s21::vector<int> vec = {1, 2, 3};

  vec.pop_back();
  vec.pop_back();
  vec.pop_back();

  EXPECT_EQ(vec.capacity(), 3);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), 0);
}

// Test erase() function
TEST_F(S21VectorTests, Erase) {
  s21::vector<int> vec = {1, 2, 3};
  // auto iter = vec.erase(vec.begin() + 1);
  vec.erase(++vec.begin());

  EXPECT_EQ(vec.size(), 2);
}

TEST_F(S21VectorTests, EmptyBegin) {
  s21::vector<int> v;
  EXPECT_EQ(v.begin(), s21::vector<int>::iterator(&v, -1));
}

TEST_F(S21VectorTests, EmptyEnd) {
  s21::vector<int> v;
  EXPECT_EQ(v.end(), s21::vector<int>::iterator(&v, -1));
}

TEST_F(S21VectorTests, EmptyErase) {
  s21::vector<int> v;

  EXPECT_THROW(v.erase(v.begin()), std::out_of_range);
}
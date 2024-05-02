#include "s21_array_tests.h"

TEST_F(S21ArrayTests, SimpleCtor) {
  s21::array<int, 8> arr;
  EXPECT_EQ(arr.size(), 8);
}

TEST_F(S21ArrayTests, InitializerListCtor) {
  s21::array<int, 8> arr = {0, 1, 2, 3, 4, 5, 6, 7};

  EXPECT_EQ(arr.size(), 8);
  EXPECT_EQ(arr.front(), 0);
  EXPECT_EQ(arr.back(), 7);
}

TEST_F(S21ArrayTests, CopyCtor) {
  s21::array<int, 8> arr1 = {5, 8, 3, 5, 2, 9, 5, 1};
  s21::array<int, 8> arr2(arr1);

  for (size_t i = 0; i < arr1.size(); i++) {
    EXPECT_EQ(arr1.at(i), arr2.at(i));
  }
}

TEST_F(S21ArrayTests, MoveCtor) {
  s21::array<int, 8> arr1 = {0, 1, 2, 3, 4, 5, 6, 7};
  s21::array<int, 8> arr2(std::move(arr1));

  EXPECT_EQ(arr1.size(), 0);

  for (size_t i = 0; i < arr2.size(); i++) {
    EXPECT_EQ(arr2.at(i), i);
  }
}

TEST_F(S21ArrayTests, MoveOperatorAssignment) {
  s21::array<int, 8> arr1 = {0, 1, 2, 3, 4, 5, 6, 7};
  s21::array<int, 8> arr2 = std::move(arr1);

  EXPECT_EQ(arr1.size(), 0);

  for (size_t i = 0; i < arr2.size(); i++) {
    EXPECT_EQ(arr2.at(i), i);
  }
}

TEST_F(S21ArrayTests, At) {
  s21::array<int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  EXPECT_EQ(arr.at(0), 0);
  EXPECT_EQ(arr.at(5), 5);

  arr.at(4) = 86;

  EXPECT_EQ(arr.at(4), 86);

  EXPECT_THROW(arr.at(59), std::out_of_range);
}

TEST_F(S21ArrayTests, OperatorSquareBrackets) {
  s21::array<int, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(arr[5], 5);

  arr[4] = 86;

  EXPECT_EQ(arr[4], 86);

  EXPECT_NO_THROW(arr[11]);
}

TEST_F(S21ArrayTests, Front) {
  s21::array<int, 5> arr = {5, 4, 6, 2, 5};

  EXPECT_EQ(arr.front(), 5);
}

TEST_F(S21ArrayTests, Back) {
  s21::array<char, 5> arr = {'h', 'e', 'l', 'l', 'o'};

  EXPECT_EQ(arr.back(), 'o');
}

TEST_F(S21ArrayTests, Data) {
  s21::array<double, 10> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (size_t i = 0; i < 10; i++) {
    EXPECT_EQ(arr.data()[i], i);
  }
}

TEST_F(S21ArrayTests, Empty) {
  s21::array<int, 5> arr = {4, 6, 2, 9, 5};

  EXPECT_FALSE(arr.empty());

  s21::array<int, 0> arr2;

  EXPECT_TRUE(arr2.empty());
}

TEST_F(S21ArrayTests, Size) {
  s21::array<int, 54> arr;

  EXPECT_EQ(arr.size(), 54);
}

TEST_F(S21ArrayTests, MaxSize) {
  s21::array<int, 38> arr;

  EXPECT_EQ(arr.max_size(), 38);
}

TEST_F(S21ArrayTests, Swap) {
  s21::array<char, 10> arr1 = {'h', 'e', 'l', 'l', 'o'};
  s21::array<char, 10> arr2 = {'w', 'e', 'l', 'c', 'o', 'm', 'e'};

  arr1.swap(arr2);

  EXPECT_EQ(arr1.front(), 'w');
  EXPECT_EQ(arr2.front(), 'h');
}

TEST_F(S21ArrayTests, Fill) {
  s21::array<double, 15> arr;

  double val = 3.14159;
  arr.fill(val);

  for (size_t i = 0; i < arr.size(); i++) {
    EXPECT_DOUBLE_EQ(arr[i], val);
  }
}
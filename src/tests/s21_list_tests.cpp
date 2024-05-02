#include "s21_list_tests.h"

TEST_F(S21ListTests, SimpleCtor) {
  s21::list<int> l;
  std::list<int> l_;

  EXPECT_EQ(l.size(), 0);
  EXPECT_TRUE(l.empty());

  EXPECT_EQ(l_.size(), 0);
  EXPECT_TRUE(l_.empty());
}

TEST_F(S21ListTests, SizedCtor) {
  s21::list<bool> l(8);
  std::list<bool> l_(8);

  EXPECT_EQ(l.size(), 8);
  EXPECT_FALSE(l.empty());

  EXPECT_EQ(l_.size(), 8);
  EXPECT_FALSE(l_.empty());
}

TEST_F(S21ListTests, ZeroSizedCtor) {
  EXPECT_THROW(s21::list<int> l(0), std::invalid_argument);
}

TEST_F(S21ListTests, InitializerListCtor) {
  s21::list<int> l = {8, 5, 26, 32, 7};
  std::list<int> l_ = {8, 5, 26, 32, 7};

  auto iter = l.begin();

  EXPECT_EQ(*iter++, 8);
  EXPECT_EQ(*iter++, 5);
  EXPECT_EQ(*iter++, 26);
  EXPECT_EQ(*iter++, 32);
  EXPECT_EQ(*iter, 7);

  auto iter_ = l_.begin();

  EXPECT_EQ(*iter_++, 8);
  EXPECT_EQ(*iter_++, 5);
  EXPECT_EQ(*iter_++, 26);
  EXPECT_EQ(*iter_++, 32);
  EXPECT_EQ(*iter_, 7);
}

TEST_F(S21ListTests, CopyCtor) {
  s21::list<int> l1 = {8, 5, 26, 32, 7};
  s21::list<int> l2 = l1;

  EXPECT_EQ(l1.size(), l2.size());

  auto iter1 = l1.begin();
  auto iter2 = l2.begin();

  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1, *iter2);
}

TEST_F(S21ListTests, MoveCtor) {
  s21::list<int> l1 = {8, 5, 26, 32, 7};
  s21::list<int> l2(std::move(l1));

  EXPECT_EQ(l1.size(), 0);
  EXPECT_EQ(l2.size(), 5);
}

TEST_F(S21ListTests, OperatorEqMove) {
  s21::list<int> l1 = {8, 5, 26, 32, 7};
  s21::list<int> l2 = std::move(l1);

  EXPECT_EQ(l1.size(), 0);
  EXPECT_EQ(l2.size(), 5);
}

TEST_F(S21ListTests, Front) {
  s21::list<int> l = {8, 5, 26, 32, 7};
  std::list<int> l_ = {8, 5, 26, 32, 7};

  EXPECT_EQ(l.front(), l_.front());
}

TEST_F(S21ListTests, Back) {
  s21::list<int> l = {8, 5, 26, 32, 7};
  std::list<int> l_ = {8, 5, 26, 32, 7};

  EXPECT_EQ(l.back(), l_.back());
}

TEST_F(S21ListTests, Begin) {
  s21::list<int> l = {15, 8, 14, 6};
  std::list<int> l_ = {15, 8, 14, 6};

  EXPECT_EQ(*l.begin(), *l_.begin());
}

TEST_F(S21ListTests, EmptyBegin) {
  s21::list<int> l;

  EXPECT_EQ(l.begin(), s21::list<int>::iterator(&l, nullptr));
}

TEST_F(S21ListTests, End) {
  s21::list<int> l1 = {15, 8, 14, 6};
  std::list<int> l2 = {15, 8, 14, 6};

  EXPECT_EQ(*--l1.end(), *--l2.end());
}

TEST_F(S21ListTests, EmptyEnd) {
  s21::list<int> l;

  EXPECT_EQ(l.end(), s21::list<int>::iterator(&l, nullptr));
}

TEST_F(S21ListTests, Empty) {
  s21::list<double> l1;
  s21::list<char> l2(8);
  s21::list<unsigned int> l3 = {0, 1, 2, 3, 4};

  EXPECT_EQ(l1.empty(), true);
  EXPECT_EQ(l2.empty(), false);
  EXPECT_EQ(l3.empty(), false);
}

TEST_F(S21ListTests, Size) {
  s21::list<double> l1;
  s21::list<char> l2(8);
  s21::list<unsigned int> l3 = {0, 1, 2, 3, 4};

  EXPECT_EQ(l1.size(), 0);
  EXPECT_EQ(l2.size(), 8);
  EXPECT_EQ(l3.size(), 5);
}

TEST_F(S21ListTests, Clear) {
  s21::list<int> l1 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(l1.size(), 11);
  l1.clear();
  EXPECT_EQ(l1.size(), 0);
}

TEST_F(S21ListTests, Insert) {
  s21::list<int> l1 = {5, 16, 32, 8, 10, 11};
  std::list<int> l2 = {5, 16, 32, 8, 10, 11};

  auto iter1 = l1.begin();
  auto iter2 = l2.begin();

  ++iter1;
  ++iter2;

  EXPECT_EQ(*l1.insert(iter1, 56), *l2.insert(iter2, 56));

  iter1 = l1.begin();
  iter2 = l2.begin();

  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1, *iter2);
}

TEST_F(S21ListTests, InsertFront) {
  s21::list<int> l1 = {5, 16, 32, 8, 10, 11};
  std::list<int> l2 = {5, 16, 32, 8, 10, 11};

  auto iter1 = l1.begin();
  auto iter2 = l2.begin();

  EXPECT_EQ(*l1.insert(iter1, 56), *l2.insert(iter2, 56));

  iter1 = l1.begin();
  iter2 = l2.begin();

  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1, *iter2);
}

TEST_F(S21ListTests, InsertBack) {
  s21::list<int> l1 = {5, 16, 32, 8, 10, 11};
  std::list<int> l2 = {5, 16, 32, 8, 10, 11};

  auto iter2 = --l2.end();
  auto iter1 = --l1.end();

  EXPECT_EQ(*l1.insert(iter1, 56), *l2.insert(iter2, 56));

  iter1 = l1.begin();
  iter2 = l2.begin();

  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1, *iter2);
}

TEST_F(S21ListTests, InsertEnd) {
  s21::list<int> l1 = {1, 2, 3};
  l1.insert(l1.end(), 28);

  EXPECT_EQ(l1.back(), 28);
}

TEST_F(S21ListTests, Erase) {
  s21::list<int> l1 = {5, 16, 32, 8, 10, 11};
  std::list<int> l2 = {5, 16, 32, 8, 10, 11};

  auto iter1 = l1.begin();
  auto iter2 = l2.begin();

  ++iter1;
  ++iter2;

  l1.erase(iter1);
  l2.erase(iter2);

  EXPECT_EQ(l1.size(), l2.size());

  iter1 = l1.begin();
  iter2 = l2.begin();

  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1, *iter2);
}

TEST_F(S21ListTests, EraseFront) {
  s21::list<int> l1 = {5, 16, 32, 8, 10, 11};
  std::list<int> l2 = {5, 16, 32, 8, 10, 11};

  auto iter1 = l1.begin();
  auto iter2 = l2.begin();

  l1.erase(iter1);
  l2.erase(iter2);

  EXPECT_EQ(l1.size(), l2.size());

  iter1 = l1.begin();
  iter2 = l2.begin();

  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1, *iter2);
}

TEST_F(S21ListTests, EraseBack) {
  s21::list<int> l1 = {5, 16, 32, 8, 10, 11};
  std::list<int> l2 = {5, 16, 32, 8, 10, 11};

  auto iter1 = --l1.end();
  auto iter2 = --l2.end();

  l1.erase(iter1);
  l2.erase(iter2);

  EXPECT_EQ(l1.size(), l2.size());

  iter1 = l1.begin();
  iter2 = l2.begin();

  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1, *iter2);
}

TEST_F(S21ListTests, EraseEmpty) {
  s21::list<int> l;

  l.erase(l.begin());

  EXPECT_EQ(l.size(), 0);
}

TEST_F(S21ListTests, EraseEnd) {
  s21::list<int> l = {1, 2, 3};

  l.erase(l.end());

  EXPECT_EQ(l.back(), 2);
}

TEST_F(S21ListTests, PushBack) {
  s21::list<int> l = {8, 14, 96, 5000, 11, 3};

  EXPECT_EQ(l.size(), 6);
  EXPECT_EQ(l.back(), 3);

  l.push_back(9);

  EXPECT_EQ(l.size(), 7);
  EXPECT_EQ(l.back(), 9);
}

TEST_F(S21ListTests, PushBackEmpty) {
  s21::list<int> l;

  EXPECT_EQ(l.size(), 0);

  l.push_back(15);

  EXPECT_EQ(l.size(), 1);
  EXPECT_EQ(l.back(), 15);
}

TEST_F(S21ListTests, PopBack) {
  s21::list<int> l = {8, 14, 96, 5000, 11, 3};
  EXPECT_EQ(l.size(), 6);
  EXPECT_EQ(l.back(), 3);

  l.pop_back();

  EXPECT_EQ(l.size(), 5);
  EXPECT_EQ(l.back(), 11);
}

TEST_F(S21ListTests, PopBackToTheEnd) {
  s21::list<int> l = {1};

  l.pop_back();

  EXPECT_EQ(l.size(), 0);
}

TEST_F(S21ListTests, PushFront) {
  s21::list<int> l = {8, 14, 96, 5000, 11, 3};

  EXPECT_EQ(l.size(), 6);
  EXPECT_EQ(l.front(), 8);

  l.push_front(9);

  EXPECT_EQ(l.size(), 7);
  EXPECT_EQ(l.front(), 9);
}

TEST_F(S21ListTests, PushFrontEmpty) {
  s21::list<int> l;

  EXPECT_EQ(l.size(), 0);

  l.push_front(15);

  EXPECT_EQ(l.size(), 1);
  EXPECT_EQ(l.front(), 15);
}

TEST_F(S21ListTests, PopFront) {
  s21::list<int> l = {8, 14, 96, 5000, 11, 3};
  EXPECT_EQ(l.size(), 6);
  EXPECT_EQ(l.front(), 8);

  l.pop_front();

  EXPECT_EQ(l.size(), 5);
  EXPECT_EQ(l.front(), 14);
}

TEST_F(S21ListTests, Swap) {
  s21::list<int> l1 = {5, 16, 38, 14, 2};
  s21::list<int> l2 = {11, 9, 3};

  EXPECT_EQ(l1.size(), 5);
  EXPECT_EQ(l2.size(), 3);

  EXPECT_EQ(l1.front(), 5);
  EXPECT_EQ(l2.front(), 11);

  EXPECT_EQ(l1.back(), 2);
  EXPECT_EQ(l2.back(), 3);

  l1.swap(l2);

  EXPECT_EQ(l2.size(), 5);
  EXPECT_EQ(l1.size(), 3);

  EXPECT_EQ(l2.front(), 5);
  EXPECT_EQ(l1.front(), 11);

  EXPECT_EQ(l2.back(), 2);
  EXPECT_EQ(l1.back(), 3);
}

TEST_F(S21ListTests, Merge) {
  s21::list<int> l1 = {5, 16, 38, 14, 2};
  s21::list<int> l2 = {11, 9, 3};

  l1.sort();
  l2.sort();

  std::list<int> l1_std = {5, 16, 38, 14, 2};
  std::list<int> l2_std = {11, 9, 3};

  l1_std.sort();
  l2_std.sort();

  l1.merge(l2);
  l1_std.merge(l2_std);

  EXPECT_EQ(l1.size(), l1_std.size());
  EXPECT_EQ(l1.front(), l1_std.front());
  EXPECT_EQ(l1.back(), l1_std.back());
}

TEST_F(S21ListTests, Splice) {
  s21::list<int> l1 = {1};
  s21::list<int> l2 = {2, 3, 4, 5};
  std::list<int> l1_std = {1};
  std::list<int> l2_std = {2, 3, 4, 5};

  auto our_it = l1.begin();
  auto std_it = l1_std.begin();

  l1.splice(our_it, l2);
  l1_std.splice(std_it, l2_std);

  EXPECT_EQ(l1.front(), l1_std.front());
  EXPECT_EQ(l1.back(), l1_std.back());
}

TEST_F(S21ListTests, Reverse) {
  s21::list<int> l1 = {5, 16, 38, 14, 2};

  EXPECT_EQ(l1.front(), 5);
  EXPECT_EQ(l1.back(), 2);

  l1.reverse();

  EXPECT_EQ(l1.front(), 2);
  EXPECT_EQ(l1.back(), 5);
}

TEST_F(S21ListTests, ReverseEmpty) {
  s21::list<int> l;

  EXPECT_THROW(l.reverse(), std::runtime_error);
}

TEST_F(S21ListTests, Unique) {
  s21::list<int> l1 = {1, 2, 2, 3, 3};
  std::list<int> l2 = {1, 2, 2, 3, 3};
  l1.unique();
  l2.unique();
  auto iter1 = l1.begin();
  auto iter2 = l2.begin();
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1, *iter2);
}

TEST_F(S21ListTests, UniqueEmpty) {
  s21::list<int> l;

  EXPECT_THROW(l.unique(), std::runtime_error);
}

TEST_F(S21ListTests, Sort) {
  s21::list<int> l1 = {2, 4, 1, 3, 5};
  std::list<int> l2 = {2, 4, 1, 3, 5};
  l1.sort();
  l2.sort();

  auto iter1 = l1.begin();
  auto iter2 = l2.begin();

  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1, *iter2);
}

TEST_F(S21ListTests, SortEmpty) {
  s21::list<int> l;

  EXPECT_THROW(l.sort(), std::runtime_error);
}

TEST_F(S21ListTests, IteratorCopyCtor) {
  s21::list<int> l = {5, 14, 12, 15};

  s21::list<int>::iterator iter1 = l.begin();

  s21::list<int>::iterator iter2(iter1);

  EXPECT_EQ(iter1, iter2);
  EXPECT_EQ(iter2, l.begin());
}

TEST_F(S21ListTests, IteratorOperatorEq) {
  s21::list<int> l = {5, 14, 12, 15};

  s21::list<int>::iterator iter1 = l.begin();

  s21::list<int>::iterator iter2 = iter1;

  EXPECT_EQ(iter1, iter2);
  EXPECT_EQ(iter2, l.begin());
}

TEST_F(S21ListTests, IteratorOperatorDeref) {
  s21::list<int> l = {8, 14, 5};

  s21::list<int>::iterator iter1 = l.begin();
  s21::list<int>::iterator iter2 = --l.end();

  EXPECT_EQ(*iter1, l.front());
  EXPECT_EQ(*iter2, l.back());
}

TEST_F(S21ListTests, IteratorOperatorIDKWhatItSCalled) {
  s21::list<std::string> l1 = {std::string("Hello"), std::string(", "),
                               std::string("world!")};
  std::list<std::string> l2 = {std::string("Hello"), std::string(", "),
                               std::string("world!")};

  s21::list<std::string>::iterator iter1 = l1.begin();
  std::list<std::string>::iterator iter2 = l2.begin();

  EXPECT_EQ(iter1->length(), iter2->length());
}

TEST_F(S21ListTests, IteratorOperatorPrefixIncrement) {
  s21::list<int> l1 = {5, 15, 9, 8, 14, 3};
  std::list<int> l2 = {5, 15, 9, 8, 14, 3};

  s21::list<int>::iterator iter1 = l1.begin();
  std::list<int>::iterator iter2 = l2.begin();

  EXPECT_EQ(*++iter1, *++iter2);
  EXPECT_EQ(*iter1, *iter2);
}

TEST_F(S21ListTests, IteratorOperatorPostfixIncrement) {
  s21::list<int> l1 = {5, 15, 9, 8, 14, 3};
  std::list<int> l2 = {5, 15, 9, 8, 14, 3};

  s21::list<int>::iterator iter1 = l1.begin();
  std::list<int>::iterator iter2 = l2.begin();

  EXPECT_EQ(*iter1++, *iter2++);
  EXPECT_EQ(*iter1, *iter2);
}

TEST_F(S21ListTests, IteratorOperatorPrefixDecrement) {
  s21::list<int> l1 = {5, 15, 9, 8, 14, 3};
  std::list<int> l2 = {5, 15, 9, 8, 14, 3};

  s21::list<int>::iterator iter1 = --l1.end();
  std::list<int>::iterator iter2 = --l2.end();

  EXPECT_EQ(*--iter1, *--iter2);
  EXPECT_EQ(*iter1, *iter2);
}

TEST_F(S21ListTests, IteratorOperatorPostfixDecrement) {
  s21::list<int> l1 = {5, 15, 9, 8, 14, 3};
  std::list<int> l2 = {5, 15, 9, 8, 14, 3};

  s21::list<int>::iterator iter1 = --l1.end();
  std::list<int>::iterator iter2 = --l2.end();

  EXPECT_EQ(*iter1--, *iter2--);
  EXPECT_EQ(*iter1, *iter2);
}

TEST_F(S21ListTests, IteratorOperatorEqual) {
  s21::list<int> l1 = {5, 15, 9, 8, 14, 3};

  s21::list<int>::iterator iter1 = l1.begin();
  s21::list<int>::iterator iter2 = l1.begin();

  EXPECT_EQ(iter1 == iter2, true);
  iter1++;
  iter2++;
  EXPECT_EQ(iter1 == iter2, true);
  iter1++;
  EXPECT_EQ(iter1 == iter2, false);
}

TEST_F(S21ListTests, IteratorOperatorNotEqual) {
  s21::list<int> l1 = {5, 15, 9, 8, 14, 3};

  s21::list<int>::iterator iter1 = l1.begin();
  s21::list<int>::iterator iter2 = l1.begin();

  EXPECT_EQ(iter1 != iter2, false);
  iter1++;
  iter2++;
  EXPECT_EQ(iter1 != iter2, false);
  iter1++;
  EXPECT_EQ(iter1 != iter2, true);
}
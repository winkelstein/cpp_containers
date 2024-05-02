#include "s21_multiset_tests.h"

TEST_F(S21MultisetTests, ConstructorDefault) {
  s21::multiset<char> my_empty_multiset;
  std::multiset<char> orig_empty_multiset;
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
}

TEST_F(S21MultisetTests, ConstructorInitializer) {
  s21::multiset<char> my_multiset = {'x', 'b', 'z', 'y', 'x'};
  std::multiset<char> orig_multiset = {'x', 'b', 'z', 'y', 'x'};

  EXPECT_EQ(my_multiset.size(), orig_multiset.size());
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  for (; my_it != my_multiset.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST_F(S21MultisetTests, ConstructorInitializer2) {
  s21::multiset<char> my_multiset = {};
  std::multiset<char> orig_multiset = {};
  EXPECT_EQ(my_multiset.size(), orig_multiset.size());
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  for (; my_it != my_multiset.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST_F(S21MultisetTests, ConstructorCopy) {
  s21::multiset<int> my_multiset = {1, 2, 3, 4, 5};
  std::multiset<int> orig_multiset = {1, 2, 3, 4, 5};
  EXPECT_EQ(my_multiset.size(), orig_multiset.size());
  s21::multiset<int> my_multiset_copy = my_multiset;
  std::multiset<int> orig_multiset_copy = orig_multiset;
  EXPECT_EQ(my_multiset_copy.size(), orig_multiset_copy.size());
  auto my_it = my_multiset_copy.begin();
  auto orig_it = orig_multiset_copy.begin();
  for (; my_it != my_multiset_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST_F(S21MultisetTests, ConstructorMove) {
  s21::multiset<int> my_multiset = {1, 2, 3, 4, 5};
  std::multiset<int> orig_multiset = {1, 2, 3, 4, 5};
  s21::multiset<int> my_multiset_copy = std::move(my_multiset);
  std::multiset<int> orig_multiset_copy = std::move(orig_multiset);
  EXPECT_EQ(my_multiset.size(), orig_multiset.size());
  EXPECT_EQ(my_multiset_copy.size(), orig_multiset_copy.size());
  auto my_it = my_multiset_copy.begin();
  auto orig_it = orig_multiset_copy.begin();
  for (; my_it != my_multiset_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST_F(S21MultisetTests, multisetIterators) {
  s21::multiset<std::string> my_multiset = {"This", "is", "my", "multiset"};
  std::multiset<std::string> orig_multiset = {"This", "is", "my", "multiset"};
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  EXPECT_TRUE(*orig_it == *my_it);
  my_it = my_multiset.end();
  orig_it = orig_multiset.end();
  --my_it;
  --orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST_F(S21MultisetTests, multisetIterators2) {
  s21::multiset<std::string> my_multiset = {"This", "is", "my", "multiset"};
  std::multiset<std::string> orig_multiset = {"This", "is", "my", "multiset"};
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  EXPECT_TRUE(*orig_it == *my_it);
  my_it++;
  orig_it++;
  EXPECT_TRUE(*orig_it == *my_it);
  ++my_it;
  ++orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
  my_it--;
  orig_it--;
  EXPECT_TRUE(*orig_it == *my_it);
  --my_it;
  --orig_it;
  EXPECT_FALSE(*orig_it != *my_it);
  my_it = my_multiset.end();
  orig_it = orig_multiset.end();
  --my_it;
  --orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST_F(S21MultisetTests, Capacity) {
  s21::multiset<char> my_empty_multiset;
  std::multiset<char> orig_empty_multiset;
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
  my_empty_multiset.insert('b');
  orig_empty_multiset.insert('c');
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
}

TEST_F(S21MultisetTests, Clear) {
  s21::multiset<char> my_empty_multiset;
  std::multiset<char> orig_empty_multiset;
  my_empty_multiset.clear();
  orig_empty_multiset.clear();
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
  my_empty_multiset.insert('a');
  orig_empty_multiset.insert('b');
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
  my_empty_multiset.clear();
  orig_empty_multiset.clear();
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
}

TEST_F(S21MultisetTests, Insert) {
  s21::multiset<std::string> my_multiset = {"This", "is", "my", "multiset"};
  std::multiset<std::string> orig_multiset = {"This", "is", "my", "multiset"};
  auto my_pr = my_multiset.insert("is");
  auto orig_pr = orig_multiset.insert("is");
  EXPECT_TRUE(*my_pr == *orig_pr);
  my_pr = my_multiset.insert("best");
  orig_pr = orig_multiset.insert("best");
  EXPECT_TRUE(*my_pr == *orig_pr);
}

TEST_F(S21MultisetTests, Erase) {
  s21::multiset<int> my_multiset = {5, 4, 3, 2, 7, 8, 9};
  std::multiset<int> orig_multiset = {5, 4, 3, 2, 7, 8, 9};
  auto size = my_multiset.size();
  my_multiset.erase(my_multiset.end());
  auto new_size = my_multiset.size();
  EXPECT_EQ(size, new_size);
  my_multiset.erase(my_multiset.begin());
  orig_multiset.erase(orig_multiset.begin());
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  for (; my_it != my_multiset.end(); ++my_it, ++orig_it) {
    EXPECT_EQ(*orig_it, *my_it);
  }
}

TEST_F(S21MultisetTests, Erase2) {
  s21::multiset<int> my_multiset;
  std::multiset<int> orig_multiset;
  auto size = my_multiset.size();
  my_multiset.erase(my_multiset.end());
  auto new_size = my_multiset.size();
  EXPECT_EQ(size, new_size);
}

TEST_F(S21MultisetTests, Swap) {
  s21::multiset<int> my_multiset = {1};
  s21::multiset<int> my_swap_multiset = {3, 4, 5};

  my_multiset.swap(my_swap_multiset);
  EXPECT_EQ(my_multiset.size(), 3);
  EXPECT_EQ(my_swap_multiset.size(), 1);
  EXPECT_EQ(*my_multiset.begin(), 3);
  EXPECT_EQ(*my_swap_multiset.begin(), 1);
}

TEST_F(S21MultisetTests, Merge) {
  s21::multiset<int> my_multiset = {1};
  s21::multiset<int> my_merge_multiset = {3, 4, 5};
  my_multiset.merge(my_merge_multiset);

  std::multiset<int> orig_multiset = {1};
  std::multiset<int> orig_merge_multiset = {3, 4, 5};
  orig_multiset.merge(orig_merge_multiset);
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  for (; my_it != my_multiset.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
  EXPECT_EQ(orig_multiset.size(), my_multiset.size());
  EXPECT_EQ(my_merge_multiset.size(), orig_merge_multiset.size());
}

TEST_F(S21MultisetTests, Find) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  std::multiset<double> orig_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my_it = my_multiset.find(2.4);
  auto orig_it = orig_multiset.find(2.4);
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST_F(S21MultisetTests, Contains) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  EXPECT_FALSE(my_multiset.contains(2));
  EXPECT_TRUE(my_multiset.contains(2.1));
}

TEST_F(S21MultisetTests, UpperBound) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  std::multiset<double> orig_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my = my_multiset.upper_bound(2);
  auto orig = orig_multiset.upper_bound(2);
  EXPECT_EQ(*my, *orig);
}

TEST_F(S21MultisetTests, LowerBound) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  std::multiset<double> orig_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my = my_multiset.lower_bound(2);
  auto orig = orig_multiset.lower_bound(2);
  EXPECT_EQ(*my, *orig);
}

TEST_F(S21MultisetTests, EqualRange) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  std::multiset<double> orig_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my = my_multiset.equal_range(2);
  auto orig = orig_multiset.equal_range(2);
  EXPECT_EQ(*my.first, *orig.first);
  EXPECT_EQ(*my.second, *orig.second);
}

TEST_F(S21MultisetTests, Count) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.6};
  std::multiset<double> orig_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.6};
  auto my = my_multiset.count(2);
  auto orig = orig_multiset.count(2);
  EXPECT_EQ(my, orig);
  my = my_multiset.count(2.1);
  orig = orig_multiset.count(2.1);
  EXPECT_EQ(my, orig);
  my = my_multiset.count(2.6);
  orig = orig_multiset.count(2.6);
  EXPECT_EQ(my, orig);
}

TEST_F(S21MultisetTests, MergeSame) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5};

  ms.merge(ms);

  EXPECT_EQ(ms.size(), 5);
}

TEST_F(S21MultisetTests, LowerBound2) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::multiset<int> ms_ = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto iter = ms.lower_bound(5);
  auto iter_ = ms_.lower_bound(5);

  EXPECT_EQ(*iter, *iter_);
}

TEST_F(S21MultisetTests, UpperBound2) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::multiset<int> ms_ = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto iter = ms.upper_bound(5);
  auto iter_ = ms_.upper_bound(5);

  EXPECT_EQ(*iter, *iter_);
}
#include "s21_map_tests.h"

TEST_F(S21MapTests, SimpleCtor) {
  s21::map<int, int> m;

  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m.empty(), true);
}

TEST_F(S21MapTests, InitializerListCtor) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};

  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m.empty(), false);

  EXPECT_EQ(m.at(1), 5);
  EXPECT_EQ(m.at(3), 8);
  EXPECT_EQ(m.at(9), 6);
}

TEST_F(S21MapTests, CopyCtor) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};
  s21::map<int, int> m1 = m;

  EXPECT_EQ(m.size(), m1.size());
  EXPECT_EQ(*m.begin(), *m.begin());
}

TEST_F(S21MapTests, MoveCtor) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};
  s21::map<int, int> m2(std::move(m));

  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m2.size(), 3);

  EXPECT_EQ((*m2.begin()).first, 1);
}

TEST_F(S21MapTests, MoveOperatorAssignment) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};
  s21::map<int, int> m2 = std::move(m);

  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m2.size(), 3);

  EXPECT_EQ((*m2.begin()).first, 1);
}

TEST_F(S21MapTests, At) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};

  EXPECT_EQ(m.at(1), 5);
  EXPECT_EQ(m.at(3), 8);
  EXPECT_EQ(m.at(9), 6);

  EXPECT_THROW(m.at(5), std::out_of_range);
}

TEST_F(S21MapTests, OperatorSquareBrackets) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};

  EXPECT_EQ(m[1], 5);
  EXPECT_EQ(m[3], 8);
  EXPECT_EQ(m[9], 6);

  EXPECT_EQ(m.size(), 3);

  m[56] = 9;

  EXPECT_EQ(m[56], 9);
  EXPECT_EQ(m.size(), 4);
}

TEST_F(S21MapTests, Begin) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};

  EXPECT_EQ((*m.begin()).first, 1);
  EXPECT_EQ((*m.begin()).second, 5);
}

TEST_F(S21MapTests, End) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};

  auto iter = --m.end();
  auto [key, value] = *iter;

  EXPECT_EQ(key, 9);
  EXPECT_EQ(value, 6);
}

TEST_F(S21MapTests, Empty) {
  s21::map<int, int> m1;
  s21::map<int, int> m2 = {};
  s21::map<int, int> m3 = {std::make_pair(5, 9)};
  s21::map<int, int> m4;

  m4[5] = 9;

  EXPECT_TRUE(m1.empty());
  EXPECT_TRUE(m2.empty());
  EXPECT_FALSE(m3.empty());
  EXPECT_FALSE(m4.empty());
}

TEST_F(S21MapTests, Size) {
  s21::map<int, int> m1;
  s21::map<int, int> m2 = {};
  s21::map<int, int> m3 = {std::make_pair(5, 9)};
  s21::map<int, int> m4 = {std::make_pair(6, 1)};

  m4[5] = 9;

  EXPECT_EQ(m1.size(), 0);
  EXPECT_EQ(m2.size(), 0);
  EXPECT_EQ(m3.size(), 1);
  EXPECT_EQ(m4.size(), 2);
}

TEST_F(S21MapTests, Clear) {
  s21::map<int, int> m = {std::make_pair(8, 3), std::make_pair(5, 1),
                          std::make_pair(6, 4), std::make_pair(3, 2)};

  EXPECT_EQ(m.size(), 4);
  m.clear();
  EXPECT_EQ(m.size(), 0);
}

TEST_F(S21MapTests, InsertOneParam) {
  s21::map<int, int> m = {std::make_pair(8, 3), std::make_pair(5, 1),
                          std::make_pair(6, 4), std::make_pair(3, 2)};

  auto [iter, inserted] = m.insert(std::make_pair(58, 3));

  EXPECT_EQ(m.size(), 5);
  EXPECT_TRUE(m.contains(58));

  EXPECT_TRUE(inserted);
  EXPECT_EQ((*iter).first, 58);
  EXPECT_EQ((*iter).second, 3);

  auto [iter2, inserted2] = m.insert(std::make_pair(8, 2));

  EXPECT_EQ(m.size(), 5);
  EXPECT_FALSE(inserted2);
  EXPECT_EQ((*iter2).first, 8);
  EXPECT_EQ((*iter2).second, 3);
}

TEST_F(S21MapTests, Insert) {
  s21::map<int, int> m = {std::make_pair(8, 3), std::make_pair(5, 1),
                          std::make_pair(6, 4), std::make_pair(3, 2)};

  auto [iter, inserted] = m.insert(58, 3);

  EXPECT_EQ(m.size(), 5);
  EXPECT_TRUE(m.contains(58));

  EXPECT_TRUE(inserted);
  EXPECT_EQ((*iter).first, 58);
  EXPECT_EQ((*iter).second, 3);

  auto [iter2, inserted2] = m.insert(8, 2);

  EXPECT_EQ(m.size(), 5);
  EXPECT_FALSE(inserted2);
  EXPECT_EQ((*iter2).first, 8);
  EXPECT_EQ((*iter2).second, 3);
}

TEST_F(S21MapTests, InsertOrAssign) {
  s21::map<int, int> m = {std::make_pair(8, 3), std::make_pair(5, 1),
                          std::make_pair(6, 4), std::make_pair(3, 2)};

  auto [iter, inserted] = m.insert_or_assign(58, 3);

  EXPECT_EQ(m.size(), 5);
  EXPECT_TRUE(m.contains(58));

  EXPECT_TRUE(inserted);
  EXPECT_EQ((*iter).first, 58);
  EXPECT_EQ((*iter).second, 3);

  auto [iter2, inserted2] = m.insert_or_assign(8, 2);

  EXPECT_EQ(m.size(), 5);
  EXPECT_FALSE(inserted2);
  EXPECT_EQ((*iter2).first, 8);
  EXPECT_EQ((*iter2).second, 2);
}

TEST_F(S21MapTests, Erase) {
  s21::map<int, int> m = {std::make_pair(8, 3), std::make_pair(5, 1),
                          std::make_pair(6, 4), std::make_pair(3, 2)};

  EXPECT_EQ(m.size(), 4);

  auto iter = m.begin();
  EXPECT_TRUE(m.contains(3));
  m.erase(iter);
  EXPECT_EQ(m.size(), 3);
  EXPECT_FALSE(m.contains(3));

  iter = m.begin();
  EXPECT_TRUE(m.contains(5));
  m.erase(iter);
  EXPECT_EQ(m.size(), 2);
  EXPECT_FALSE(m.contains(5));

  iter = m.begin();
  EXPECT_TRUE(m.contains(6));
  m.erase(iter);
  EXPECT_EQ(m.size(), 1);
  EXPECT_FALSE(m.contains(6));

  iter = m.begin();
  EXPECT_TRUE(m.contains(8));
  m.erase(iter);
  EXPECT_EQ(m.size(), 0);
  EXPECT_FALSE(m.contains(8));
}

TEST_F(S21MapTests, Swap) {
  s21::map<int, int> m1 = {std::make_pair(8, 50), std::make_pair(5, 1),
                           std::make_pair(6, 4), std::make_pair(3, 2)};

  s21::map<int, int> m2 = {std::make_pair(6, 1), std::make_pair(13, 9)};

  m1.swap(m2);

  EXPECT_EQ(m1.size(), 2);
  EXPECT_EQ(m2.size(), 4);

  EXPECT_EQ((*m1.begin()).first, 6);
  EXPECT_EQ((*m2.begin()).first, 3);
}

TEST_F(S21MapTests, Merge) {
  s21::map<int, int> m1 = {std::make_pair(8, 50), std::make_pair(5, 1),
                           std::make_pair(6, 4), std::make_pair(3, 2)};

  s21::map<int, int> m2 = {std::make_pair(6, 1), std::make_pair(13, 9)};

  m1.merge(m2);

  EXPECT_EQ(m1.size(), 5);

  EXPECT_TRUE(m1.contains(8));
  EXPECT_TRUE(m1.contains(5));
  EXPECT_TRUE(m1.contains(6));
  EXPECT_TRUE(m1.contains(3));
  EXPECT_TRUE(m1.contains(13));

  EXPECT_EQ(m2.size(), 0);
}

TEST_F(S21MapTests, Contains) {
  s21::map<int, int> m = {std::make_pair(8, 3), std::make_pair(5, 1),
                          std::make_pair(6, 4), std::make_pair(3, 2)};

  EXPECT_TRUE(m.contains(8));
  EXPECT_TRUE(m.contains(5));
  EXPECT_TRUE(m.contains(6));
  EXPECT_TRUE(m.contains(3));

  EXPECT_FALSE(m.contains(9));
  EXPECT_FALSE(m.contains(4));
  EXPECT_FALSE(m.contains(15));
  EXPECT_FALSE(m.contains(333));
}

TEST_F(S21MapTests, IteratorOperatorDecrement1) {
  s21::map<int, int> m = {std::make_pair(8, 3), std::make_pair(5, 1),
                          std::make_pair(6, 4), std::make_pair(3, 2)};

  auto iter = m.end();

  EXPECT_EQ((*--iter).first, 8);
  EXPECT_EQ((*--iter).first, 6);
  EXPECT_EQ((*--iter).first, 5);
  EXPECT_EQ((*--iter).first, 3);
}

TEST_F(S21MapTests, IteratorOperatorDecrement2) {
  s21::map<int, int> m = {std::make_pair(8, 3),   std::make_pair(5, 1),
                          std::make_pair(6, 4),   std::make_pair(3, 2),
                          std::make_pair(93, 9),  std::make_pair(15, 8),
                          std::make_pair(-30, 2), std::make_pair(56, 15)};

  auto iter = m.end();

  EXPECT_EQ((*--iter).first, 93);
  EXPECT_EQ((*--iter).first, 56);
  EXPECT_EQ((*--iter).first, 15);
  EXPECT_EQ((*--iter).first, 8);
  EXPECT_EQ((*--iter).first, 6);
  EXPECT_EQ((*--iter).first, 5);
  EXPECT_EQ((*--iter).first, 3);
  EXPECT_EQ((*--iter).first, -30);
}

TEST_F(S21MapTests, EmptyBegin) {
  s21::map<int, int> m;

  s21::map<int, int>::iterator iter(&m, nullptr);
  EXPECT_EQ(m.begin(), iter);
}

TEST_F(S21MapTests, EmptyEnd) {
  s21::map<int, int> m;

  s21::map<int, int>::iterator iter(&m, nullptr);
  EXPECT_EQ(m.end(), iter);
}

TEST_F(S21MapTests, EmptyInsertOrAssign) {
  s21::map<int, int> m;

  m.insert_or_assign(15, 96);

  EXPECT_EQ(m.at(15), 96);
}

TEST_F(S21MapTests, Erase2) {
  s21::map<int, int> m = {std::make_pair(8, 3),   std::make_pair(5, 1),
                          std::make_pair(6, 4),   std::make_pair(3, 2),
                          std::make_pair(93, 9),  std::make_pair(15, 8),
                          std::make_pair(-30, 2), std::make_pair(56, 15)};

  auto iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(93));

  iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(56));

  iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(15));

  iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(8));

  iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(6));

  iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(5));

  iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(3));

  iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(-30));
}
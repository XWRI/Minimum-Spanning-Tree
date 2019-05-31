#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "index_min_pq.h"

// Check if Push and Pop is working with size
TEST(IndexMinPQ, PushPopSize) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert key-values
  std::vector<std::pair<double, int>> keyval{
    { 2.0, 20},
    { 4.0, 40},
    { 6.0, 60},
    { 8.0, 80}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
    EXPECT_TRUE(impq.Contains(i.second));
  }
  EXPECT_EQ(impq.Size(), 4);
  impq.Pop();
  EXPECT_EQ(impq.Size(), 3);
  impq.Pop();
  EXPECT_EQ(impq.Size(), 2);
  impq.Pop();
  EXPECT_EQ(impq.Size(), 1);
  impq.Pop();
  EXPECT_EQ(impq.Size(), 0);
}

// check insertion in increasing order of both key and index
TEST(IndexMinPQ, SimpleScenarioII) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert key-values
  std::vector<std::pair<double, int>> keyval{
    { 2.0, 20},
    { 4.0, 40},
    { 6.0, 60},
    { 8.0, 80}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
    EXPECT_TRUE(impq.Contains(i.second));
  }
  // Key-value at the top should now be (2.0, 20)
  EXPECT_EQ(impq.Top(), 20);
  impq.Pop();
  // Test Contains()
  EXPECT_FALSE(impq.Contains(20));
  EXPECT_EQ(impq.Top(), 40);

  // Test ChangeKey(): change key associated to value 80
  impq.ChangeKey(1.0, 80);
  // Key-value at the top should now be (1.0, 80)
  EXPECT_EQ(impq.Top(), 80);
}

// Check insertion in decreasing order of both key and index
TEST(IndexMinPQ, SimpleScenarioDD) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert key-values
  std::vector<std::pair<double, int>> keyval{
    { 8.0, 80},
    { 6.0, 60},
    { 4.0, 40},
    { 2.0, 20}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
    EXPECT_TRUE(impq.Contains(i.second));
  }
  // Key-value at the top should now be (2.0, 20)
  EXPECT_EQ(impq.Top(), 20);
  impq.Pop();
  // Test Contains()
  EXPECT_FALSE(impq.Contains(20));
  EXPECT_EQ(impq.Top(), 40);

  // Test ChangeKey(): change key associated to value 80
  impq.ChangeKey(1.0, 80);
  // Key-value at the top should now be (1.0, 80)
  EXPECT_EQ(impq.Top(), 80);
}

// Check insertion in decreasing order of key and increasing order of index
TEST(IndexMinPQ, SimpleScenarioDI) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert key-values
  std::vector<std::pair<double, int>> keyval{
    { 8.0, 20},
    { 6.0, 40},
    { 4.0, 60},
    { 2.0, 80}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
    EXPECT_TRUE(impq.Contains(i.second));
  }
  // Key-value at the top should now be (2.0, 80)
  EXPECT_EQ(impq.Top(), 80);
  impq.Pop();
  // Test Contains()
  EXPECT_FALSE(impq.Contains(80));
  EXPECT_EQ(impq.Top(), 60);

  // Test ChangeKey(): change key associated to value 20
  impq.ChangeKey(1.0, 20);
  // Key-value at the top should now be (1.0, 20)
  EXPECT_EQ(impq.Top(), 20);
}

// Check insertion in increasing order of key and decreasing order of index
TEST(IndexMinPQ, SimpleScenarioID) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert key-values
  std::vector<std::pair<double, int>> keyval{
    { 2.0, 80},
    { 4.0, 60},
    { 6.0, 40},
    { 8.0, 20}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
    EXPECT_TRUE(impq.Contains(i.second));
  }
  // Key-value at the top should now be (2.0, 80)
  EXPECT_EQ(impq.Top(), 80);
  impq.Pop();
  // Test Contains()
  EXPECT_FALSE(impq.Contains(80));
  EXPECT_EQ(impq.Top(), 60);

  // Test ChangeKey(): change key associated to value 20
  impq.ChangeKey(1.0, 20);
  // Key-value at the top should now be (1.0, 20)
  EXPECT_EQ(impq.Top(), 20);
}

// Check insertion in random order of both key and index
TEST(IndexMinPQ, SimpleScenarioRandom) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert key-values
  std::vector<std::pair<double, int>> keyval{
    { 2.2, 99},
    { 51.0, 54},
    { 42.5, 53},
    { 74.32, 93}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
    EXPECT_TRUE(impq.Contains(i.second));
  }
  // Key-value at the top should now be (2.2, 99)
  EXPECT_EQ(impq.Top(), 99);
  impq.Pop();
  // Test Contains()
  EXPECT_FALSE(impq.Contains(99));
  EXPECT_EQ(impq.Top(), 53);

  // Test ChangeKey(): change key associated to value 93
  impq.ChangeKey(1.0, 93);
  // Key-value at the top should now be (1.0, 93)
  EXPECT_EQ(impq.Top(), 93);
}

// Check Changekey
TEST(IndexMinPQ, CheckChangeKey) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<double> impq(100);

  // Insert key-values
  std::vector<std::pair<double, int>> keyval{
    { 5.0, 99},
    { 25.0, 77},
    { 50.0, 55},
    { 75.0, 33}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
  }
  EXPECT_TRUE(impq.Contains(33));

  EXPECT_EQ(impq.Top(), 99);

  impq.ChangeKey(1.0, 33);
  EXPECT_EQ(impq.Top(), 33);

  impq.ChangeKey(2.0, 55);
  EXPECT_EQ(impq.Top(), 33);

  impq.ChangeKey(90.0, 33);
  EXPECT_EQ(impq.Top(), 55);

  impq.ChangeKey(95.0, 55);
  EXPECT_EQ(impq.Top(), 99);

  impq.ChangeKey(97.0, 99);
  EXPECT_EQ(impq.Top(), 77);

  impq.ChangeKey(99.0, 77);
  EXPECT_EQ(impq.Top(), 33);
}

// Check with char Key
TEST(IndexMinPQ, SimpleCharScenario) {
  // Indexed min-priority queue of capacity 100
  IndexMinPQ<char> impq(100);

  // Insert a bunch of key-value
  std::vector<std::pair<char, int>> keyval{
    { 'B', 99},
    { 'C', 54},
    { 'D', 53},
    { 'E', 93}
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
    EXPECT_TRUE(impq.Contains(i.second));
  }

  // Key-value at the top should now be ('B', 99)
  EXPECT_EQ(impq.Top(), 99);
  impq.Pop();
  // Test Contains()
  EXPECT_FALSE(impq.Contains(99));
  EXPECT_EQ(impq.Top(), 54);

  // Test ChangeKey(): change key associated to value 93
  impq.ChangeKey('A', 93);
  // Key-value at the top should now be ('A', 93)
  EXPECT_EQ(impq.Top(), 93);
}

// Check Exception for Push
TEST(IndexMinPQ, PushException) {
  // Indexed min-priority queue of capacity 4
  IndexMinPQ<char> impq(4);

  // Insert a bunch of key-value
  std::vector<std::pair<char, int>> keyval{
    { 'B', 0},
    { 'C', 1},
    { 'D', 2},
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
    EXPECT_TRUE(impq.Contains(i.second));
  }
  // runtime_error (duplicate index)
  EXPECT_THROW(impq.Push('H', 2), std::exception);
  impq.Push('B', 3);
  // overflow_error
  EXPECT_THROW(impq.Push('F', 4), std::exception);
}

// Check Exception for Pop
TEST(IndexMinPQ, PopException) {
  // Indexed min-priority queue of capacity 4
  IndexMinPQ<char> impq(4);

  // underflow_error
  EXPECT_THROW(impq.Pop(), std::exception);
}

// Check Excption for Top
TEST(IndexMinPQ, TopException) {
  // Indexed min-priority queue of capacity 4
  IndexMinPQ<char> impq(4);

  // underflow_error
  EXPECT_THROW(impq.Top(), std::exception);
}

// Check Exception for ChangeKey
TEST(IndexMinPQ, ChangeKeyException) {
  // Indexed min-priority queue of capacity 4
  IndexMinPQ<char> impq(4);

  // Insert a bunch of key-value
  std::vector<std::pair<char, int>> keyval{
    { 'B', 0},
    { 'C', 1},
    { 'D', 3},
  };
  for (auto &i : keyval) {
    impq.Push(i.first, i.second);
    EXPECT_TRUE(impq.Contains(i.second));
  }
  // runtime_error (duplicate index)
  EXPECT_THROW(impq.ChangeKey('H', 2), std::exception);
  impq.ChangeKey('B', 3);
  // overflow_error
  EXPECT_THROW(impq.ChangeKey('F', 4), std::exception);
}


int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

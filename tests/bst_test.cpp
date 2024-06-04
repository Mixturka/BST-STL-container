#include "../lib/BST.hpp"

#include <gtest/gtest.h>

#include <vector>

class BSTTest : public ::testing::Test {
 protected:
  BST<int> bst;
};

TEST_F(BSTTest, InorderTest) {
  bst.insert({5, 4, 1, 7, 2, 8, 6});

  int expected_array[] = {1, 2, 4, 5, 6, 7, 8};
  int i = 0;

  for (auto it = bst.begin<IteratorType::INORDER>();
       it != bst.end<IteratorType::INORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, ReverseInorderTest) {
  bst.insert({5, 4, 1, 7, 2, 8, 6});

  int expected_array[] = {8, 7, 6, 5, 4, 2, 1};
  int i = 0;

  for (auto it = bst.rbegin<IteratorType::INORDER>();
       it != bst.rend<IteratorType::INORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, PreorderTest) {
  bst.insert({5, 4, 1, 7, 2, 8, 6});

  int expected_array[] = {5, 4, 1, 2, 7, 6, 8};
  int i = 0;

  for (auto it = bst.begin<IteratorType::PREORDER>();
       it != bst.end<IteratorType::PREORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, ReversePreorderTest) {
  bst.insert({5, 4, 1, 7, 2, 8, 6});

  int expected_array[] = {8, 6, 7, 2, 1, 4, 5};
  int i = 0;

  for (auto it = bst.rbegin<IteratorType::PREORDER>();
       it != bst.rend<IteratorType::PREORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, PostorderTest) {
  bst.insert({5, 4, 1, 7, 2, 8, 6});

  int expected_array[] = {2, 1, 4, 6, 8, 7, 5};
  int i = 0;

  for (auto it = bst.begin<IteratorType::POSTORDER>();
       it != bst.end<IteratorType::POSTORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, ReversePostorderTest) {
  bst.insert({5, 4, 1, 7, 2, 8, 6});

  int expected_array[] = {5, 7, 8, 6, 4, 1, 2};
  int i = 0;

  for (auto it = bst.rbegin<IteratorType::POSTORDER>();
       it != bst.rend<IteratorType::POSTORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, ConstInorderTest) {
  bst.insert({5, 4, 1, 7, 2, 8, 6});

  int expected_array[] = {1, 2, 4, 5, 6, 7, 8};
  int i = 0;

  for (auto it = bst.cbegin<IteratorType::INORDER>();
       it != bst.cend<IteratorType::INORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, ConstReverseInorderTest) {
  bst.insert({5, 4, 1, 7, 2, 8, 6});

  int expected_array[] = {1, 2, 4, 5, 6, 7, 8};
  int i = 0;

  for (auto it = bst.crbegin<IteratorType::INORDER>();
       it != bst.crend<IteratorType::INORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, ConstPreorderTest) {
  bst.insert({5, 4, 1, 7, 2, 8, 6});

  int expected_array[] = {5, 4, 1, 2, 7, 6, 8};
  int i = 0;

  for (auto it = bst.cbegin<IteratorType::PREORDER>();
       it != bst.cend<IteratorType::PREORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, ConstReversePreorderTest) {
  bst.insert({5, 4, 1, 7, 2, 8, 6});

  int expected_array[] = {8, 6, 7, 2, 1, 4, 5};
  int i = 0;

  for (auto it = bst.crbegin<IteratorType::PREORDER>();
       it != bst.crend<IteratorType::PREORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, ConstPostorderTest) {
  bst.insert({5, 4, 1, 7, 2, 8, 6});

  int expected_array[] = {2, 1, 4, 6, 8, 7, 5};
  int i = 0;

  for (auto it = bst.cbegin<IteratorType::POSTORDER>();
       it != bst.cend<IteratorType::POSTORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, ConstReversePostorderTest) {
  bst.insert({5, 4, 1, 7, 2, 8, 6});

  int expected_array[] = {5, 7, 8, 6, 4, 1, 2};
  int i = 0;

  for (auto it = bst.crbegin<IteratorType::POSTORDER>();
       it != bst.crend<IteratorType::POSTORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, EmptyTest) { ASSERT_EQ(bst.empty(), true); }

TEST_F(BSTTest, NotEmptyTest) {
  bst.insert<IteratorType::INORDER>(1);
  ASSERT_EQ(bst.empty(), false);
}

TEST_F(BSTTest, SizeTestNoRemove) {
  bst.insert({1, 2, 3, 4, 5, 6, 7});
  ASSERT_EQ(bst.size(), 7);
}

TEST_F(BSTTest, SizeTestWithRemove) {
  bst.insert({1, 2, 3, 4, 5, 6, 7});
  bst.erase(5);
  ASSERT_EQ(bst.size(), 6);
}

TEST_F(BSTTest, InsertTest) {
  bst.insert<IteratorType::INORDER>(1);

  ASSERT_EQ(bst.size(), 1);
  ASSERT_EQ(bst.extract(1)->value, 1);
}

TEST_F(BSTTest, InsertListTest) {
  bst.insert({5, 4, 1, 7, 2, 8, 6});
  int expected_array[] = {1, 2, 4, 5, 6, 7, 8};
  int i = 0;
  ASSERT_EQ(bst.size(), 7);

  for (auto it = bst.cbegin<IteratorType::INORDER>();
       it != bst.cend<IteratorType::INORDER>(); ++it) {
    EXPECT_EQ(expected_array[i], *it);
    ++i;
  }
}

TEST_F(BSTTest, EmptyInorderTest) {
  int expected_array[] = {};
  int i = 0;

  for (auto it = bst.begin<IteratorType::INORDER>();
       it != bst.end<IteratorType::INORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, EmptyPreorderTest) {
  int expected_array[] = {};
  int i = 0;

  for (auto it = bst.begin<IteratorType::PREORDER>();
       it != bst.end<IteratorType::PREORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, EmptyPostorderTest) {
  int expected_array[] = {};
  int i = 0;

  for (auto it = bst.begin<IteratorType::POSTORDER>();
       it != bst.end<IteratorType::POSTORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, ClearTest) {
  bst.insert({1, 2, 3, 4, 5, 6, 7});
  bst.clear();
  ASSERT_EQ(bst.size(), 0);
}

TEST_F(BSTTest, EmplaceTest) {
  bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);
  int expected_array[7] = {1, 2, 4, 5, 6, 7, 8};
  int i = 0;
  ASSERT_EQ(bst.size(), 7);

  for (auto it = bst.begin<IteratorType::INORDER>();
       it != bst.end<IteratorType::INORDER>(); ++it) {
    EXPECT_EQ(expected_array[i], *it);
    ++i;
  }
}

TEST_F(BSTTest, EraseIteratorPosTest) {
  auto aboba = bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);

  auto it = bst.begin<IteratorType::INORDER>();
  ASSERT_EQ(*aboba.first, 6);

  while (*it != 5) {
    ++it;
  }

  bst.erase(it);
  int expected_array[] = {1, 2, 4, 6, 7, 8};
  int i = 0;
  ASSERT_EQ(bst.size(), 6);

  for (auto it = bst.begin<IteratorType::INORDER>();
       it != bst.end<IteratorType::INORDER>(); ++it) {
    EXPECT_EQ(expected_array[i], *it);
    ++i;
  }
}

TEST_F(BSTTest, EraseInRangeTest) {
  auto aboba = bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);

  auto it = bst.begin<IteratorType::INORDER>();
  auto it1 = bst.begin<IteratorType::INORDER>();
  ASSERT_EQ(*aboba.first, 6);

  while (*it != 5) {
    ++it;
  }

  while (*it1 != 2) {
    ++it1;
  }

  auto result = bst.erase<IteratorType::INORDER>(it1, it);
  int expected_array[] = {1, 5, 6, 7, 8};
  int i = 0;
  ASSERT_EQ(bst.size(), 5);

  for (auto it = bst.begin<IteratorType::INORDER>();
       it != bst.end<IteratorType::INORDER>(); ++it) {
    EXPECT_EQ(expected_array[i], *it);
    ++i;
  }

  ASSERT_EQ(*result, 5);
}

TEST_F(BSTTest, EraseSuccessKeyTest) {
  auto aboba = bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);
  auto result = bst.erase(8);
  int expected_array[] = {1, 2, 4, 5, 6, 7};
  int i = 0;
  ASSERT_EQ(bst.size(), 6);

  for (auto it = bst.begin<IteratorType::INORDER>();
       it != bst.end<IteratorType::INORDER>(); ++it) {
    EXPECT_EQ(expected_array[i], *it);
    ++i;
  }

  ASSERT_EQ(result, 1);
}

TEST_F(BSTTest, EraseNotSuccessKeyTest) {
  auto aboba = bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);
  auto result = bst.erase(0);
  int expected_array[] = {1, 2, 4, 5, 6, 7, 8};
  int i = 0;
  ASSERT_EQ(bst.size(), 7);

  for (auto it = bst.begin<IteratorType::INORDER>();
       it != bst.end<IteratorType::INORDER>(); ++it) {
    EXPECT_EQ(expected_array[i], *it);
    ++i;
  }

  ASSERT_EQ(result, 0);
}

TEST_F(BSTTest, SwapTest) {
  bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);
  BST<int> bst2;
  bst2.emplace<IteratorType::INORDER>(20, 30, 40, 50);

  bst.swap(bst2);

  int expected_bst[] = {20, 30, 40, 50};
  int expected_bst2[] = {1, 2, 4, 5, 6, 7, 8};
  int i = 0;
  ASSERT_EQ(bst.size(), 4);
  ASSERT_EQ(bst2.size(), 7);

  for (auto it = bst.begin<IteratorType::INORDER>();
       it != bst.end<IteratorType::INORDER>(); ++it) {
    EXPECT_EQ(expected_bst[i], *it);
    ++i;
  }
  i = 0;
  for (auto it = bst2.begin<IteratorType::INORDER>();
       it != bst2.end<IteratorType::INORDER>(); ++it) {
    EXPECT_EQ(expected_bst2[i], *it);
    ++i;
  }
}

TEST_F(BSTTest, ExtractTest) {
  bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);

  Node<int>* node = bst.extract(4);
  ASSERT_EQ(node->value, 4);
}

TEST_F(BSTTest, MergeTest) {
  bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);
  BST<int> bst2;
  bst2 = {20, 30, 40, 50};
  bst.merge(bst2);
  ASSERT_EQ(bst2.size(), 0);

  int expected_array[] = {1, 2, 4, 5, 6, 7, 8, 20, 30, 40, 50};
  int i = 0;

  for (auto it = bst.begin<IteratorType::INORDER>();
       it != bst.end<IteratorType::INORDER>(); ++it) {
    EXPECT_EQ(*it, expected_array[i]);
    ++i;
  }
}

TEST_F(BSTTest, CountTest) {
  bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);

  ASSERT_EQ(bst.count(1), 1);
  ASSERT_EQ(bst.count(0), 0);
}

TEST_F(BSTTest, FindTest) {
  bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);

  auto result = bst.find<IteratorType::INORDER>(8);
  ASSERT_EQ(*result, 8);
}

TEST_F(BSTTest, ContainsTest) {
  bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);

  auto result = bst.contains(8);
  ASSERT_EQ(result, true);
}

TEST_F(BSTTest, LowerBoundEqualTest) {
  bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);

  auto result = bst.lower_bound<IteratorType::INORDER>(1);

  ASSERT_EQ(*result, 1);
}

TEST_F(BSTTest, LowerBoundNextTest) {
  bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);

  auto result = bst.lower_bound<IteratorType::INORDER>(3);

  ASSERT_EQ(*result, 4);
}

TEST_F(BSTTest, UpperBoundTest) {
  bst.emplace<IteratorType::INORDER>(5, 4, 1, 7, 2, 8, 6);

  auto result = bst.upper_bound<IteratorType::INORDER>(4);

  ASSERT_EQ(*result, 5);
}

TEST_F(BSTTest, NullPointerExceptionIterator) {
  BST<int>::const_iterator<IteratorType::INORDER> iter(nullptr);

  try {
    *iter;
  } catch(std::invalid_argument const &err) {
    EXPECT_EQ(err.what(), std::string("Dereferencing null pointer."));
  }
}

TEST_F(BSTTest, NullPointerExceptionReverseIterator) {
  BST<int>::const_reverse_iterator<BST<int>::const_iterator<IteratorType::INORDER>> iter(nullptr);

  try {
    *iter;
  } catch(std::invalid_argument const &err) {
    EXPECT_EQ(err.what(), std::string("Dereferencing null pointer."));
  }
}

TEST_F(BSTTest, EqualTest) {
  bst = {18, 5, 3, 4, 1};

  BST<int> bst2;
  bst2 = {18, 5, 3, 4, 1};

  ASSERT_EQ(bst == bst2, true);
}

TEST_F(BSTTest, NotEqualTest1) {
  bst = {18, 5, 3, 4, 1};

  BST<int> bst2;
  bst2 = {18, 5, 3, 4, 1};

  ASSERT_EQ(bst != bst2, false);
}

TEST_F(BSTTest, NotEqualTest2) {
  bst = {18, 5, 3, 4, 1};

  BST<int> bst2;
  bst2 = {18, 3, 4, 1};

  ASSERT_EQ(bst != bst2, true);
}
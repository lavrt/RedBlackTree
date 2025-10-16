#include <gtest/gtest.h>

#include "tree.hpp"

using KeyT = int;

class RBTreeTest : public ::testing::Test {
protected:
    std::vector<KeyT> CollectKeys(const Trees::RBTree<KeyT>& tree) {
        std::vector<KeyT> keys;
        for (auto it = tree.begin(); it != tree.end(); ++it) {
            keys.push_back(*it);
        }
        return keys;
    }
};

TEST_F(RBTreeTest, Constructors) {
    // constructor
    Trees::RBTree<KeyT> tree1;
    EXPECT_TRUE(tree1.begin() == tree1.end());
    
    // insert
    tree1.Insert(5);
    tree1.Insert(3);
    tree1.Insert(7);
    
    // copy constructor
    Trees::RBTree<KeyT> tree2(tree1);
    EXPECT_NE(tree1.begin(), tree2.begin());
    
    auto keys1 = CollectKeys(tree1);
    auto keys2 = CollectKeys(tree2);
    EXPECT_EQ(keys1, keys2);
    
    // operator=
    Trees::RBTree<KeyT> tree3;
    tree3 = tree1;
    
    auto keys3 = CollectKeys(tree3);
    EXPECT_EQ(keys1, keys3);
    
    // move constructor
    Trees::RBTree<KeyT> tree4(std::move(tree1));
    auto keys4 = CollectKeys(tree4);
    EXPECT_EQ(keys2, keys4);
    EXPECT_TRUE(tree1.begin() == tree1.end());
    
    // move operator=
    Trees::RBTree<KeyT> tree5;
    tree5 = std::move(tree2);
    auto keys5 = CollectKeys(tree5);
    EXPECT_EQ(keys2, keys5);
    EXPECT_TRUE(tree2.begin() == tree2.end());
}

TEST_F(RBTreeTest, Insert) {
    Trees::RBTree<KeyT> tree;
    
    EXPECT_TRUE(tree.Insert(10));
    EXPECT_TRUE(tree.Insert(5));
    EXPECT_TRUE(tree.Insert(15));
    EXPECT_FALSE(tree.Insert(10));
    EXPECT_TRUE(tree.Insert(3));
    EXPECT_TRUE(tree.Insert(7));
    EXPECT_TRUE(tree.Insert(12));
    EXPECT_TRUE(tree.Insert(18));
    
    size_t count = 0;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 7);
}

TEST_F(RBTreeTest, Iterators) {
    Trees::RBTree<KeyT> tree;
    std::vector<KeyT> expected = {1, 3, 5, 7, 9};
    
    tree.Insert(5);
    tree.Insert(1);
    tree.Insert(9);
    tree.Insert(3);
    tree.Insert(7);
    
    std::vector<KeyT> actual;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        actual.push_back(*it);
    }
    
    EXPECT_EQ(actual, expected);
    
    Trees::RBTree<KeyT> empty_tree;
    EXPECT_TRUE(empty_tree.begin() == empty_tree.end());
}

TEST_F(RBTreeTest, Bounds) {
    Trees::RBTree<KeyT> tree;
    
    for (size_t i = 0; i < 10; i += 2) {
        tree.Insert(i);
    }
    
    EXPECT_EQ(*tree.LowerBound(3), 4);
    EXPECT_EQ(*tree.LowerBound(4), 4);
    EXPECT_EQ(*tree.LowerBound(0), 0);
    EXPECT_EQ(*tree.LowerBound(8), 8);
    EXPECT_TRUE(tree.LowerBound(9) == tree.end());
    EXPECT_TRUE(tree.LowerBound(10) == tree.end());
    
    EXPECT_EQ(*tree.UpperBound(3), 4);
    EXPECT_EQ(*tree.UpperBound(2), 4);
    EXPECT_EQ(*tree.UpperBound(0), 2);
    EXPECT_TRUE(tree.UpperBound(8) == tree.end());
    EXPECT_TRUE(tree.UpperBound(9) == tree.end());
}

TEST_F(RBTreeTest, Distance) {
    Trees::RBTree<KeyT> tree;
    
    EXPECT_EQ(tree.Distance(tree.begin(), tree.end()), 0);
    
    for (size_t i = 0; i < 10; ++i) {
        tree.Insert(i);
    }
    
    auto begin = tree.begin();
    auto end = tree.end();
    
    EXPECT_EQ(tree.Distance(begin, end), 10);
    
    auto it5 = tree.LowerBound(5);
    EXPECT_EQ(tree.Distance(begin, it5), 5);
    EXPECT_EQ(tree.Distance(it5, end), 5);
    
    EXPECT_EQ(tree.Distance(begin, begin), 0);
    EXPECT_EQ(tree.Distance(end, end), 0);
}

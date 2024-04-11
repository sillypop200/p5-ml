#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"


TEST(justone) {
    BinarySearchTree<int> tree; 
    tree.insert(5);
     ASSERT_TRUE(tree.size() == 1);
  ASSERT_TRUE(tree.height() == 1);
  ASSERT_TRUE(tree.find(5) != tree.end());
ASSERT_TRUE(tree.max_element() == tree.find(5));
  ASSERT_TRUE(tree.min_element() == tree.find(5));
  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_FALSE(tree.empty());
  ASSERT_TRUE(tree.find(5)==tree.begin());
  }
TEST (smalltree){
     BinarySearchTree<int> tree; 
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
     ASSERT_TRUE(tree.size() == 3);
  ASSERT_TRUE(tree.height() == 2);
  ASSERT_TRUE(tree.find(5) != tree.end());
  ASSERT_TRUE(tree.find(7) != tree.end());
ASSERT_TRUE(tree.max_element() == tree.find(7));
  ASSERT_TRUE(tree.min_element() == tree.find(3));
  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_FALSE(tree.empty());
  ASSERT_TRUE(tree.find(3)==tree.begin());
  }
  TEST(meep){
    BinarySearchTree<int> tree; 
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
    ASSERT_TRUE(tree.size() == 5);
  ASSERT_TRUE(tree.height() == 3);
  ASSERT_TRUE(tree.find(7) != tree.end());
ASSERT_TRUE(tree.max_element() == tree.find(7));
  ASSERT_TRUE(tree.min_element() == tree.find(1));
  ASSERT_TRUE(tree.check_sorting_invariant());
  ASSERT_FALSE(tree.empty());
  ASSERT_TRUE(tree.find(1)==tree.begin());
  }
  TEST (check_sorting_invariant){
    BinarySearchTree<int> tree; 
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
    ASSERT_TRUE(tree.check_sorting_invariant());
    BinarySearchTree<int>::Iterator  iterate = tree.begin();
    ++iterate; 
    *iterate = 10; 
    ASSERT_FALSE(tree.check_sorting_invariant());
  }
  TEST (check_sorting_invariant2){
    BinarySearchTree<int> tree; 
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
    ASSERT_TRUE(tree.check_sorting_invariant());
    BinarySearchTree<int>::Iterator  iterate = tree.begin();
    for (int i =0; i<4;++i){
        ++iterate;
    }
    *iterate = 1; 
    ASSERT_FALSE(tree.check_sorting_invariant());
  }
  TEST(copyconstructor){
    BinarySearchTree<int> tree; 
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
    BinarySearchTree<int> copy; 
    copy = tree; 
      ASSERT_TRUE(copy.size() == 5);
  ASSERT_TRUE(copy.height() == 3);
  ASSERT_TRUE(copy.find(7) != copy.end());
ASSERT_TRUE(copy.max_element() == copy.find(7));
  ASSERT_TRUE(copy.min_element() == copy.find(1));
  ASSERT_TRUE(copy.check_sorting_invariant());
  ASSERT_FALSE(copy.empty());
  ASSERT_TRUE(copy.find(1)==copy.begin());
  }
  TEST(copyconstructor2){
    BinarySearchTree<int> tree; 
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
    BinarySearchTree<int> copy(tree);
      ASSERT_TRUE(copy.size() == 5);
  ASSERT_TRUE(copy.height() == 3);
  ASSERT_TRUE(copy.find(7) != copy.end());
ASSERT_TRUE(copy.max_element() == copy.find(7));
  ASSERT_TRUE(copy.min_element() == copy.find(1));
  ASSERT_TRUE(copy.check_sorting_invariant());
  ASSERT_FALSE(copy.empty());
  ASSERT_TRUE(copy.find(1)==copy.begin());
  copy.insert(10);
ASSERT_TRUE(copy.max_element() == copy.find(10));
ASSERT_TRUE(tree.max_element() == tree.find(7));
ASSERT_FALSE(tree.max_element() == copy.find(7));
  }
  TEST(min_greater_than){
     BinarySearchTree<int> tree; 
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
    tree.insert(1);
    tree.insert(4);
     ASSERT_EQUAL(3,*tree.min_greater_than(2));
     ASSERT_EQUAL(tree.end(),tree.min_greater_than(30));
     ASSERT_EQUAL(tree.begin(),tree.min_greater_than(0));
     ASSERT_EQUAL(7,*tree.min_greater_than(6));
  }
  TEST(min_greater_than_empty){
     BinarySearchTree<int> tree; 
     ASSERT_EQUAL(tree.end(),tree.min_greater_than(3));
     ASSERT_EQUAL(tree.end(),tree.max_element());
     ASSERT_EQUAL(tree.end(),tree.min_element());
  }
  TEST(traverse_preorder){
    BinarySearchTree<int> tree; 
    tree.insert(7);

    tree.insert(2);
    tree.insert(10);
    
    tree.insert(1);
    tree.insert(4);
    tree.insert(13);

    tree.insert(3);
    tree.insert(5);
    tree.insert(11);
    std::ostringstream help;
    tree.traverse_preorder(help);
    // std::string correct = "7 2 1 4 3 5 10 13 11 ";
    // std::ostringstream right(correct);
    ASSERT_EQUAL (help.str(), "7 2 1 4 3 5 10 13 11 ");
  }
  TEST(traverse_inorder){
    BinarySearchTree<int> tree; 
        tree.insert(7);

    tree.insert(2);
    tree.insert(10);
    
    tree.insert(1);
    tree.insert(4);
    tree.insert(13);

    tree.insert(3);
    tree.insert(5);
    tree.insert(11);

    std::ostringstream help;
    tree.traverse_inorder(help);

  
    ASSERT_EQUAL (help.str(), "1 2 3 4 5 7 10 11 13 ");
  }
TEST_MAIN()

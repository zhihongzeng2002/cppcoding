// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <memory>

#include "./BST_prototype.h"

using std::unique_ptr;

// @include
bool search_min_first_BST(const unique_ptr<BSTNode<int>>& T, int k) {
  if (!T || T->data > k) {
    return false;
  } else if (T->data == k) {
    return true;
  }

  // Searches the right subtree if the smallest key in the right subtree is
  // greater than or equal to k.
  if (T->right && k >= T->right->data) {
    return search_min_first_BST(T->right, k);
  }
  return search_min_first_BST(T->left, k);
}
// @exclude

int main(int argc, char* argv[]) {
  // A min-first BST
  //    1
  //  2   4
  // 3   5 7
  auto root = unique_ptr<BSTNode<int>>(new BSTNode<int>{1});
  root->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{2});
  root->left->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{3});
  root->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{4});
  root->right->left = unique_ptr<BSTNode<int>>(new BSTNode<int>{5});
  root->right->right = unique_ptr<BSTNode<int>>(new BSTNode<int>{7});
  assert(search_min_first_BST(root, 1));
  assert(search_min_first_BST(root, 3));
  assert(search_min_first_BST(root, 5));
  assert(!search_min_first_BST(root, 6));
  return 0;
}

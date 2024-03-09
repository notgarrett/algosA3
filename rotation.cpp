#pragma once

#include "avl_tree.hpp"
#include <iostream>

template <typename T> int AVLTree<T>::height(Node<T> n) {}

template <typename T> int AVLTree<T>::height(Node<T> *node) {
  if (node == nullptr)
    return 0;
  return node->height;
}

template <typename T> int AVLTree<T>::balanceFactor(Node<T> *node) {
  if (node == nullptr)
    return 0;
  return height(node->left) - height(node->right);
}

template <typename T> Node<T> AVLTree<T>::*rightRotate(Node<T> *y) {
  Node<T> *x = y->left;
  Node<T> *T2 = x->right;

  // Perform rotation
  x->right = y;
  y->left = T2;

  // Update heights
  y->height = std::max(height(y->left), height(y->right)) + 1;
  x->height = std::max(height(x->left), height(x->right)) + 1;

  return x;
}

template <typename T> Node<T> AVLTree<T>::*leftRotate(Node<T> *x) {
  Node<T> *y = x->right;
  Node<T> *T2 = y->left;

  // Perform rotation
  y->left = x;
  x->right = T2;

  // Update heights
  x->height = std::max(height(x->left), height(x->right)) + 1;
  y->height = std::max(height(y->left), height(y->right)) + 1;

  return y;
}

template <typename T> Node<T> AVLTree<T>::*insertNode(Node<T> *node, T value) {
  // Perform normal BST insertion
  if (node == nullptr)
    return new Node<T>(value);

  if (value < node->data)
    node->left = insertNode(node->left, value);
  else if (value > node->data)
    node->right = insertNode(node->right, value);
  else // Duplicate values not allowed
    return node;

  // Update height of this ancestor node
  node->height = 1 + std::max(height(node->left), height(node->right));

  // Get the balance factor of this ancestor node to check whether this node
  // became unbalanced

  balance(node, value);

  // Return the unchanged node pointer
  return node;
}

template <typename T> void AVLTree<T>::balance(Node<T> *node, T value) {

  // If node becomes unbalanced, then there are 4 cases
  int balance = balanceFactor(node);

  // Left Left Case
  if (balance > 1 && value < node->left->data)
    return rightRotate(node);

  // Right Right Case
  if (balance < -1 && value > node->right->data)
    return leftRotate(node);

  // Left Right Case
  if (balance > 1 && value > node->left->data) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // Right Left Case
  if (balance < -1 && value < node->right->data) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }
}

template <typename T> AVLTree<T>::AVLTree() : root(nullptr) {}

template <typename T> void AVLTree<T>::insert(T value) {
  root = insertNode(root, value);
};

// Other AVL operations such as deletion, searching, etc. can be implemented
// similarly

// Helper function to print in-order traversal
template <typename T> void AVLTree<T>::printInOrder(Node<T> *node) {
  if (node == nullptr)
    return;
  printInOrder(node->left);
  std::cout << node->data << " ";
  printInOrder(node->right);
}

template <typename T> void AVLTree<T>::printInOrder() { printInOrder(root); }

template <typename T> void AVLTree<T>::printPostOrder(Node<T> *node) {
  if (node == nullptr)
    return;
  printPostOrder(node->left);
  printPostOrder(node->right);
  std::cout << node->data << " ";
}

template <typename T> void AVLTree<T>::printPostOrder() {
  printPostOrder(root);
}

template <typename T> void AVLTree<T>::printPreOrder(Node<T> *node) {
  if (node == nullptr)
    return;

  std::cout << node->data << " ";
  printPreOrder(node->left);
  printPreOrder(node->right);
}

template <typename T> void AVLTree<T>::printPreOrder() { printPreOrder(root); }

#pragma once

template <typename T> struct Node {
  T data;
  Node<T> *left;
  Node<T> *right;
  int height;
  Node(T val);
};

template <typename T> class AVLTree {
private:
  Node<T> *root;

  int height(Node<T>);
  int height(Node<T> *);
  int balanceFactor(Node<T> *);
  Node<T> *rightRotate(Node<T> *);
  Node<T> *leftRotate(Node<T>);
  Node<T> *insertNode(Node<T>, T);

public:
  AVLTree();
  void insert(T);
  void printInOrder(Node<T> *);
  void printInOrder();
  void printPostOrder(Node<T> *);
  void printPostOrder();
  void printPreOrder(Node<T> *);
  void printPreOrder();
  void balance(Node<T> *, T);
  Node<T> search(T);
};

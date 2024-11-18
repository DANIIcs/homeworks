#ifndef HW3_IMPL_H
#define HW3_IMPL_H

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "hw3.h"

template <typename T>
BST<T>::BST() : root(nullptr) {
}

template <typename T>
BST<T>::~BST() {
  clear();
}

template <typename T>
void BST<T>::insert(T const& value) {
  Node* current = root;
  Node* parent = nullptr;

  while (current != nullptr) {
    parent = current;
    if (value < current->value) {
      current = current->left;
    } else if (value > current->value) {
      current = current->right;
    } else {
      return;
    }
  }

  Node* newNode = new Node(value);
  if (parent == nullptr) {
    root = newNode;
  } else if (value < parent->value) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }
}

template <typename T>
bool BST<T>::search(T const& value) const {
  Node* current = root;

  while (current != nullptr) {
    if (value < current->value) {
      current = current->left;
    } else if (value > current->value) {
      current = current->right;
    } else {
      return true;
    }
  }

  return false;
}

template <typename T>
void BST<T>::remove(T const& value) {
  Node* current = root;
  Node* parent = nullptr;

  while (current != nullptr && current->value != value) {
    parent = current;
    if (value < current->value) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  if (current == nullptr) {
    return;
  }

  if (current->left == nullptr && current->right == nullptr) {
    if (current == root) {
      root = nullptr;
    } else if (parent->left == current) {
      parent->left = nullptr;
    } else {
      parent->right = nullptr;
    }
    delete current;
  }
  else if (current->left == nullptr || current->right == nullptr) {
    Node* child = (current->left != nullptr) ? current->left : current->right;

    if (current == root) {
      root = child;
    } else if (parent->left == current) {
      parent->left = child;
    } else {
      parent->right = child;
    }
    delete current;
  }
  else {
    Node* successorParent = current;
    Node* successor = current->right;

    while (successor->left != nullptr) {
      successorParent = successor;
      successor = successor->left;
    }

    current->value = successor->value;

    if (successorParent->left == successor) {
      successorParent->left = successor->right;
    } else {
      successorParent->right = successor->right;
    }

    delete successor;
  }
}

template <typename T>
size_t BST<T>::size() const {
  if (root == nullptr) {
    return 0;
  }

  size_t count = 0;
  std::vector<Node*> stack;
  stack.push_back(root);

  while (!stack.empty()) {
    Node* current = stack.back();
    stack.pop_back();
    count++;

    if (current->left != nullptr) {
      stack.push_back(current->left);
    }
    if (current->right != nullptr) {
      stack.push_back(current->right);
    }
  }

  return count;
}


template <typename T>
T BST<T>::findMin() const {
  if (root == nullptr) {
    return T();
  }

  Node* current = root;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current->value;
}


template <typename T>
T BST<T>::findMax() const {
  if (root == nullptr) {
    return T();
  }

  Node* current = root;
  while (current->right != nullptr) {
    current = current->right;
  }
  return current->value;
}

template <typename T>
bool BST<T>::isEmpty() const {
  return root == nullptr;
}

template <typename T>
void BST<T>::clear() {
  while (root != nullptr) {
    remove(root->value);
  }
}


#endif
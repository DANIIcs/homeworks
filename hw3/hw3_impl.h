#ifndef HW3_IMPL_H
#define HW3_IMPL_H

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "hw3.h"

template <typename T>
BST<T>::BST() : root(nullptr) {}

template <typename T>
BST<T>::~BST() {
  clear();
}

template <typename T>
void BST<T>::insert(T const& value) {
  Node* newNode = new Node{value, nullptr, nullptr};
  if (!root) {
    root = newNode;
    return;
  }
  Node* current = root;
  Node* parent = nullptr;

  while (current) {
    parent = current;
    if (value < current->data) {
      current = current->left;
    } else if (value > current->data) {
      current = current->right;
    } else {
      delete newNode; // Valor duplicado, no insertamos
      return;
    }
  }

  if (value < parent->data) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }
}

template <typename T>
bool BST<T>::search(T const& value) const {
  Node* current = root;
  while (current) {
    if (value == current->data) {
      return true;
    } else if (value < current->data) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return false;
}

template <typename T>
void BST<T>::remove(T const& value) {
  Node* current = root;
  Node* parent = nullptr;

  // Buscar el nodo a eliminar
  while (current && current->data != value) {
    parent = current;
    if (value < current->data) {
      current = current->left;
    } else {
      current = current->right;
    }
  }

  if (!current) return; // Nodo no encontrado

  // Caso 1: Nodo sin hijos
  if (!current->left && !current->right) {
    if (!parent) {
      root = nullptr;
    } else if (parent->left == current) {
      parent->left = nullptr;
    } else {
      parent->right = nullptr;
    }
    delete current;
  }
  // Caso 2: Nodo con un solo hijo
  else if (!current->left || !current->right) {
    Node* child = (current->left) ? current->left : current->right;
    if (!parent) {
      root = child;
    } else if (parent->left == current) {
      parent->left = child;
    } else {
      parent->right = child;
    }
    delete current;
  }
  // Caso 3: Nodo con dos hijos
  else {
    Node* successorParent = current;
    Node* successor = current->right;
    while (successor->left) {
      successorParent = successor;
      successor = successor->left;
    }
    current->data = successor->data;
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
    if (!root) return 0; // Si el árbol está vacío, el tamaño es 0

    size_t count = 0;
    std::vector<Node*> stack;
    stack.push_back(root);

    while (!stack.empty()) {
        Node* current = stack.back();
        stack.pop_back();
        count++; // Contar el nodo actual

        // Agregar los hijos al stack
        if (current->left) stack.push_back(current->left);
        if (current->right) stack.push_back(current->right);
    }

    return count;
}


template <typename T>
T BST<T>::findMin() const {
  Node* current = root;
  while (current->left) {
    current = current->left;
  }
  return current->data;
}

template <typename T>
T BST<T>::findMax() const {
  Node* current = root;
  while (current->right) {
    current = current->right;
  }
  return current->data;
}

template <typename T>
bool BST<T>::isEmpty() const {
  return root == nullptr;
}

template <typename T>
void BST<T>::clear() {
  std::vector<Node*> stack;
  if (root) stack.push_back(root);

  while (!stack.empty()) {
    Node* node = stack.back();
    stack.pop_back();

    if (node->right) stack.push_back(node->right);
    if (node->left) stack.push_back(node->left);

    delete node;
  }
  root = nullptr;
}

#endif

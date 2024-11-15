#ifndef HW1_IMPL_H
#define HW1_IMPL_H

#include <algorithm>
#include <cstdlib>
#include <vector>
#include <stack>

#include "hw1.h"

// AVLNode

template <typename T>
AVLNode<T>::AVLNode(T value)
    : data(value), left(nullptr), right(nullptr), height(0) {}

// AVLTree

template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template <typename T>
int AVLTree<T>::height(AVLNode<T>* node) {
  if (node == nullptr){
    return 0;
  }
  else {
    return node -> height;
  }
}

template <typename T>
int AVLTree<T>::getBalance(AVLNode<T>* node) {
  if (node == nullptr)
      return 0;
  return height(node->left) - height(node->right);
}

template <typename T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* y) {
  AVLNode<T>* x= y->left;
  AVLNode<T>* T2 = x-> right;

  x->right = y;
  y->left =T2;

  y->height=std::max(height(y->left), height(y->right))+1;
  x->height=std::max(height(x->left), height(x->right))+1;

  return x;
}

// Rotación izquierda
template <typename T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* x) {
  AVLNode<T>* y = x->right;
  AVLNode<T>* T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = std::max(height(x->left), height(x->right)) + 1;
  y->height = std::max(height(y->left), height(y->right)) + 1;

  return y;
}

template <typename T>
AVLNode<T>* AVLTree<T>::minValueNode(AVLNode<T>* node) {
  AVLNode<T>* current = node;
  while (current->left != nullptr)
      current = current->left;
  return current;
}

// Inserción
template <typename T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node, T key) {
    if (node == nullptr)
        return new AVLNode<T>(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = std::max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    if (balance < -1 && key > node->right->data)
        return leftRotate(node);

    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Eliminar un nodo
template <typename T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T>* root, T key) {
    if (root == nullptr)
        return root;

    if (key < root->data)
        root->left = remove(root->left, key);
    else if (key > root->data)
        root->right = remove(root->right, key);
    else {
        if (root->left == nullptr || root->right == nullptr) {
            AVLNode<T>* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            AVLNode<T>* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }
    }

    if (root == nullptr)
        return root;

    root->height = std::max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Búsqueda
template <typename T>
bool AVLTree<T>::search(AVLNode<T>* node, T key) {
  if (node == nullptr)
      return false;
  if (node->data == key)
      return true;
  if (key < node->data)
      return search(node->left, key);
  return search(node->right, key);
}

// Recorrido preorder
template <typename T>
void AVLTree<T>::preorder(AVLNode<T>* root, std::vector<T>& ret) {
    if (root != nullptr) {
        ret.push_back(root->data);
        preorder(root->left, ret);
        preorder(root->right, ret);
    }
}

// Recorrido inorder
template <typename T>
void AVLTree<T>::inorder(AVLNode<T>* root, std::vector<T>& ret) {
    if (root != nullptr) {
        inorder(root->left, ret);
        ret.push_back(root->data);
        inorder(root->right, ret);
    }
}

// Recorrido postorder
template <typename T>
void AVLTree<T>::postorder(AVLNode<T>* root, std::vector<T>& ret) {
    if (root != nullptr) {
        postorder(root->left, ret);
        postorder(root->right, ret);
        ret.push_back(root->data);
    }
}

template <typename T>
void AVLTree<T>::insert(T key) {
    root = insert(root,key);
}

template <typename T>
void AVLTree<T>::remove(T key) {
    root = remove(root, key);
}

template <typename T>
bool AVLTree<T>::search(T key) {
    return search(root, key);
}

template <typename T>
std::vector<T> AVLTree<T>::preorderTraversal() {
    std::vector<T> result;
    std::stack<AVLNode<T>*> nodeStack;
    
    if (root != nullptr)
        nodeStack.push(root);
    
    while (!nodeStack.empty()) {
        AVLNode<T>* node = nodeStack.top();
        nodeStack.pop();
        
        result.push_back(node->data);
        
        if (node->right != nullptr)
            nodeStack.push(node->right);
        if (node->left != nullptr)
            nodeStack.push(node->left);
    }

    return result;
}


template <typename T>
std::vector<T> AVLTree<T>::inorderTraversal() {
    std::vector<T> result;
    std::stack<AVLNode<T>*> nodeStack; 
    AVLNode<T>* node = root;

    while (node != nullptr || !nodeStack.empty()) {
        while (node != nullptr) {
            nodeStack.push(node);
            node = node->left;
        }
        node = nodeStack.top();
        nodeStack.pop();
        result.push_back(node->data);
        node = node->right;
    }

    return result;
}




template <typename T>
std::vector<T> AVLTree<T>::postorderTraversal() {
    std::vector<T> result;
    AVLNode<T>* node = root;
    if (node == nullptr)
        return result;
    
    std::stack<AVLNode<T>*> stack1, stack2;
    stack1.push(node);
    
    while (!stack1.empty()) {
        node = stack1.top();
        stack1.pop();
        stack2.push(node);
        
        if (node->left != nullptr)
            stack1.push(node->left);
        if (node->right != nullptr)
            stack1.push(node->right);
    }
    
    while (!stack2.empty()) {
        result.push_back(stack2.top()->data);
        stack2.pop();
    }

    return result;
}


template <typename T>
int AVLTree<T>::height() {
    return height(root);
}
template <typename T>
bool AVLTree<T>::isBalanced() {
    return std::abs(getBalance(root)) <= 1;
}

#endif

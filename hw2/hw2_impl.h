#ifndef HW2_IMPL_H
#define HW2_IMPL_H

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "hw2.h"

// Heap

template <typename T>
Heap<T>::Heap(bool isMinHeap) : minHeap(isMinHeap) {
  data=std::vector<T>();
}

template <typename T>
void Heap<T>::insert(T const& element) {
  data.push_back(element);
  int index = data.size()-1;
  while (index > 0) {
    int parent = (index - 1) / 2;

    if ((minHeap && data[index] < data[parent]) || (!minHeap && data[index] > data[parent])) {
      std::swap(data[index], data[parent]);
      index = parent; 
    } else {
      break;
    }
  }
  
}

template <typename T>
T Heap<T>::extractTop() {
  if (isEmpty()) return T{};

  T top = data[0];
  data[0] = data.back();
  data.pop_back();

  int index = 0;
  int size = data.size();

  while (true) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int swapIndex = index;

    if (leftChild < size && ((minHeap && data[leftChild] < data[swapIndex]) || (!minHeap && data[leftChild] > data[swapIndex]))) {
      swapIndex = leftChild;
    }
    if (rightChild < size && ((minHeap && data[rightChild] < data[swapIndex]) || (!minHeap && data[rightChild] > data[swapIndex]))) {
      swapIndex = rightChild;
    }

    if (swapIndex == index) break;

    std::swap(data[index], data[swapIndex]);
    index = swapIndex;
  }

  return top;
}

template <typename T>
T Heap<T>::peek() const {
  if (!isEmpty()) {
    return data[0];
  }
  return T{};
}

template <typename T>
size_t Heap<T>::size() const {
  return data.size();
}

template <typename T>
bool Heap<T>::isEmpty() const {
  return data.empty();
}

template <typename T>
void Heap<T>::clear() {
  data.clear();
}

#endif

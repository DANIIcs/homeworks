#ifndef HW2_IMPL_H
#define HW2_IMPL_H

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "hw2.h"

template <typename T>
Heap<T>::Heap(bool isMinHeap) : minHeap(isMinHeap), size_(0) {}


template <typename T>
void Heap<T>::insert(T const& element) {
    queue_.push_back(element);
    size_++;

  
    int idx = size_ - 1;
    while (idx > 0) {
        int parentIdx = (idx - 1) / 2;
        if ((minHeap && queue_[parentIdx] > queue_[idx]) || 
            (!minHeap && queue_[parentIdx] < queue_[idx])) {
            std::swap(queue_[parentIdx], queue_[idx]);
            idx = parentIdx;
        } else {
            break;
        }
    }
}

template <typename T>
T Heap<T>::extractTop() {

    T top = queue_[0];
    queue_[0] = queue_[size_ - 1];
    queue_.pop_back();
    size_--;

  
    int idx = 0;
    while (true) {
        int leftChildIdx = 2 * idx + 1;
        int rightChildIdx = 2 * idx + 2;
        int swapIdx = idx;

        if (leftChildIdx < size_ && 
            ((minHeap && queue_[leftChildIdx] < queue_[swapIdx]) || 
             (!minHeap && queue_[leftChildIdx] > queue_[swapIdx]))) {
            swapIdx = leftChildIdx;
        }

        if (rightChildIdx < size_ && 
            ((minHeap && queue_[rightChildIdx] < queue_[swapIdx]) || 
             (!minHeap && queue_[rightChildIdx] > queue_[swapIdx]))) {
            swapIdx = rightChildIdx;
        }

        if (swapIdx != idx) {
            std::swap(queue_[idx], queue_[swapIdx]);
            idx = swapIdx;
        } else {
            break;
        }
    }

    return top;
}


template <typename T>
T Heap<T>::peek() const {
    
    return queue_[0];
}


template <typename T>
size_t Heap<T>::size() const {
    return size_;
}


template <typename T>
bool Heap<T>::isEmpty() const {
    return size_ == 0;
}


template <typename T>
void Heap<T>::clear() {
    queue_.clear();
    size_ = 0;
}

#endif

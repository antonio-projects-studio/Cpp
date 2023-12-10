#ifndef BINARYSEARCH_H_KTHELEMENT_H
#define BINARYSEARCH_H_KTHELEMENT_H

#include <iostream>

template <typename T> void KthElement(T *begin, T *key, T *end) {
  T *left = begin;
  T *pivot = left;
  T *right = end;
  while (true) {
    pivot = left;
    T val = *pivot;
    for (int i = 1; i < right - left; ++i) {
      if (*(left + i) < val) {
        ++pivot;
        std::swap(*(left + i), *pivot);
      }
    }
    std::swap(*left, *pivot);
    if (pivot == key) {
      break;
    }
    if (pivot < key) {
      left = pivot + 1;
      continue;
    }
    if (key < pivot) {
      right = pivot;
      continue;
    }
  }
}

#endif
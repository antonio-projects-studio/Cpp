#pragma once

template <class T>
bool BinarySearch(const T *begin, const T *end, const T &target) {
  const T *middle;
  while (begin != end) {
    middle = begin + (end - begin) / 2;
    if (*middle < target) {
      begin = middle + 1;
      continue;
    }
    if (target < *middle) {
      end = middle;
      continue;
    }
    return true;
  }
  return false;
}

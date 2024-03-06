#pragma once

#include <cstring>
#include <iostream>

template <class T, class U, class Q>
void Merge(const T *first_begin, const T *first_end, const U *second_begin,
           const U *second_end, Q *sout) {
  int size = (second_end - first_begin);
  auto *out = new T[size];
  while (first_begin < first_end || second_begin < second_end) {
    if (first_begin < first_end && second_begin < second_end) {
      if (*first_begin < *second_begin) {
        *out = *first_begin;
        ++out;
        ++first_begin;
        continue;
      }
      *out = *second_begin;
      ++out;
      ++second_begin;
      continue;
    }
    if (first_begin < first_end) {
      *out = *first_begin;
      ++out;
      ++first_begin;
      continue;
    }
    *out = *second_begin;
    ++out;
    ++second_begin;
  }
  memcpy(sout, out - size, size * sizeof(T));
  delete[] (out - size);
}

template <class T> void Sort(T *begin, T *end) {
  if (end < (begin + 2)) {
    return;
  }
  T *mid = begin + (end - begin) / 2;
  Sort(begin, mid);
  Sort(mid, end);
  Merge(begin, mid, mid, end, begin);
}
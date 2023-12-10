#include <iostream>
void quicksort(int *arr, int left, int right) {
  int pivot = arr[left], i = left, j = right + 1, p = left, z = right + 1;
  if (right <= left) {
    return;
  }
  while (true) {
    while (arr[++i] < pivot) {
      if (i == right) {
        break;
      }
    }
    while (arr[--j] > pivot) {
      if (j == left) {
        break;
      }
    }
    if (i >= j) {
      std::swap(arr[left], arr[j]);
      break;
    }
    std::swap(arr[i], arr[j]);
    if (arr[i] == pivot) {
      ++p;
      std::swap(arr[i], arr[p]);
    }
    if (arr[j] == pivot) {
      --z;
      std::swap(arr[j], arr[z]);
    }
  }
  i = j + 1;
  --j;
  for (int k = left + 1; k <= p; ++k, --j) {
    std::swap(arr[k], arr[j]);
  }
  for (int k = right; k >= z; --k, ++i) {
    std::swap(arr[k], arr[i]);
  }
  quicksort(arr, left, j);
  quicksort(arr, i, right);
}
void quicksort(int *arr, int left, int right) {
  int pivot = arr[right], i = left - 1, j = right, p = left - 1, q = right;
  if (right <= left) {
    return;
  }
  while (true) {
    while (arr[++i] < pivot) {
      if (i == right) {
        break;
      }
    }
    while (arr[--j] > pivot) {
      if (j == left) {
        break;
      }
    }
    if (i >= j) {
      std::swap(arr[right], arr[i]);
      break;
    }
    std::swap(arr[i], arr[j]);
    if (arr[i] == pivot) {
      ++p;
      std::swap(arr[p], arr[i]);
    }
    if (arr[j] == pivot) {
      --q;
      std::swap(arr[j], arr[q]);
    }
  }
  j = i - 1;
  i++;
  for (int k = left; k <= p; ++k, --j) {
    std::swap(arr[k], arr[j]);
  }
  for (int k = right - 1; k >= q; --k, ++i) {
    std::swap(arr[k], arr[i]);
  }
  quicksort(arr, left, j);
  quicksort(arr, i, right);
}
void quicksort(int *arr, int left, int right) {
  int pivot = arr[right], i = left, j = right - 1, p = left - 1, q = right;
  if (right <= left) {
    return;
  }
  while (i <= j) {
    while (arr[i] < pivot) {
      ++i;
    }
    while (arr[j] > pivot) {
      --j;
    }
    if (i >= j) {

      break;
    }
    std::swap(arr[i], arr[j]);
    if (arr[i] == pivot) {
      ++p;
      std::swap(arr[p], arr[i]);
    }
    ++i;
    if (arr[j] == pivot) {
      --q;
      std::swap(arr[j], arr[q]);
    }
    --j;
  }
  std::swap(arr[right], arr[i]);
  j = i - 1;
  i++;
  for (int k = left; k <= p; ++k, --j) {
    std::swap(arr[k], arr[j]);
  }
  for (int k = right - 1; k >= q; --k, ++i) {
    std::swap(arr[k], arr[i]);
  }
  quicksort(arr, left, j);
  quicksort(arr, i, right);
}

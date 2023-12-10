#include <iostream>
#include <sstream>

struct Pyramid {
  int size = 0;
  int capasity = 0;
  int *arr = nullptr;

  void Allocate() {
    arr = (int *)realloc(arr, 2 * (capasity + 1) * sizeof(int));
    capasity = 2 * (capasity + 1);
  }

  void Push(int n) {
    if (size == capasity) {
      Allocate();
    }
    arr[size] = n;
    ++size;
  }
  void BuildHeap() {
    for (int i = size / 2; i >= 0; --i) {
      SiftDown(i);
    }
  }
  void SiftUp(int i) {
    if (size != 0) {
      while (i > 0 && arr[i] > arr[(i - 1) / 2]) {
        std::swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
      }
    }
  }

  void SiftDown(int i) {
    if (size != 0) {
      while (2 * i + 1 < size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int j = left;
        if (right < size && arr[right] > arr[left]) {
          j = right;
        }

        if (arr[i] < arr[j]) {
          std::swap(arr[i], arr[j]);
          i = j;
          continue;
        }
        return;
      }
    }
  }

  void Insert(int n) {
    if (size == capasity) {
      Allocate();
    }
    ++size;
    arr[size - 1] = n;
    SiftUp(size - 1);
  }

  int ExtractMax() {
    if (size == 0) {
      return -1;
    }
    int max = arr[0];
    std::swap(arr[size - 1], arr[0]);
    --size;
    SiftDown(0);
    return max;
  }

  void Clear(int x) {
    if (size != 0) {
      free(arr);
      size = 0;
      capasity = 0;
      arr = nullptr;
    }
  }

  void HeapSort(int n) {
    for (int i = 0; i < n; ++i) {
      arr[n - i - 1] = ExtractMax();
    }
  }
};

int main() {
  Pyramid array;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    array.Push(x);
  }
  array.BuildHeap();
  array.HeapSort(n);
  for (int i = 0; i < n; ++i) {
    std::cout << array.arr[i] << ' ';
  }
  free(array.arr);
  return 0;
}

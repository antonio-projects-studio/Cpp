#include <iostream>

struct Pyramid {
  int size = 0;
  int *arr = nullptr;
  int *arr2 = nullptr;

  void SiftUp(int i) {
    if (size != 0) {
      while (i > 0 && arr[i] < arr[(i - 1) / 2]) {
        std::swap(arr[i], arr[(i - 1) / 2]);
        std::swap(arr2[i], arr2[(i - 1) / 2]);
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
        if (right < size && arr[right] < arr[left]) {
          j = right;
        }
        if (arr[i] > arr[j]) {
          std::swap(arr[i], arr[j]);
          std::swap(arr2[i], arr2[j]);
          i = j;
          continue;
        }
        return;
      }
    }
  }

  void Insert(int n) {
    ++size;
    arr[size - 1] = n;
    SiftUp(size - 1);
  }

  void BuildHeap() {
    for (int i = size / 2; i >= 0; --i) {
      SiftDown(i);
    }
  }

  int ExtractMin() {
    if (size == 0) {
      return -1;
    }
    int min = arr[0];
    std::swap(arr[size - 1], arr[0]);
    std::swap(arr2[size - 1], arr2[0]);
    --size;
    SiftDown(0);
    return min;
  }
};

int *MergeSort(Pyramid &array, int **arr, const int *arrsize, int k) {
  int size = 0;
  int pos = 0;
  int *cnt = new int[k];
  for (int i = 0; i < k; ++i) {
    size += arrsize[i];
    cnt[i] = 1;
  }
  int *arr3 = new int[size];
  while (array.size != 1) {
    int x = array.arr2[0];
    arr3[pos] = array.ExtractMin();
    ++pos;
    if (cnt[x] < arrsize[x]) {
      array.Insert(arr[x][cnt[x]++]);
    }
  }
  int x = array.arr2[0];
  arr3[pos] = array.ExtractMin();
  ++pos;
  for (int i = cnt[x]; i < arrsize[x]; ++i) {
    arr3[pos] = arr[x][i];
    ++pos;
  }
  delete[] cnt;
  return arr3;
}

int main() {
  int n, k, val = 0;
  Pyramid array;
  std::cin >> k;
  int *sizearr = new int[k];
  array.size = k;
  array.arr = new int[k];
  array.arr2 = new int[k];
  int **arr = new int *[k];
  for (int i = 0; i < k; ++i) {
    std::cin >> n;
    val += n;
    arr[i] = new int[n];
    sizearr[i] = n;
    std::cin >> arr[i][0];
    array.arr[i] = arr[i][0];
    array.arr2[i] = i;
    for (int j = 1; j < n; ++j) {
      std::cin >> arr[i][j];
    }
  }
  array.BuildHeap();
  int *arr3 = MergeSort(array, arr, sizearr, k);
  for (int i = 0; i < val; ++i) {
    std::cout << arr3[i] << ' ';
  }
  delete[] arr3;
  delete[] array.arr;
  delete[] array.arr2;
  delete[] sizearr;
  for (int i = 0; i < k; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
}

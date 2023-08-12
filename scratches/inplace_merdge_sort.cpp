#include <iostream>

using namespace std;

struct Student {
  char *name = nullptr;
  char *surname = nullptr;
  int data = 0;
};

int LowerBound(Student *arr, int begin, int end, int x) {
  int mid;
  while (begin < end) {
    mid = begin + (end - begin) / 2;
    if (arr[x].data >= arr[mid].data) {
      end = mid;
    } else {
      begin = mid + 1;
    }
  }
  return begin;
}
void Reserge(Student *arr, int begin, int end) {
  for (int i = 0; i < (end - begin) / 2; ++i) {
    std::swap(arr[begin + i], arr[end - i - 1]);
  }
}
void Swap(Student *arr, int x, int mid, int lb) {
  Reserge(arr, x, mid);
  Reserge(arr, mid, lb);
  Reserge(arr, x, lb);
}
void InPlaceMerge(Student *arr, int l, int mid, int r) {
  if (mid - l < 1 || r - mid < 1) {
    return;
  }
  int x = l + (mid - l) / 2;
  int lb = LowerBound(arr, mid, r, x);
  Swap(arr, x, mid, lb);
  InPlaceMerge(arr, l, x, x + (lb - mid));
  InPlaceMerge(arr, x + (lb - mid) + 1, lb, r);
}

void MergeSort(Student *arr, int l, int r) {
  if (r - l < 2) {
    return;
  }
  int mid = l + (r - l) / 2;
  MergeSort(arr, l, mid);
  MergeSort(arr, mid, r);
  InPlaceMerge(arr, l, mid, r);
}

void Clear(Student *array, int size) {
  for (int i = 0; i < size; i++) {
    delete[] array[i].name;
    delete[] array[i].surname;
  }
}

int main() {
  int n;
  cin >> n;
  Student *arr = new Student[n];
  for (int i = 0; i < n; i++) {
    char *name = new char[1000];
    char *surname = new char[1000];
    cin >> name >> surname;
    int a, b, c;
    cin >> a >> b >> c;
    arr[i].data = a + b + c;
    arr[i].name = name;
    arr[i].surname = surname;
  }
  MergeSort(arr, 0, n);
  for (int i = 0; i < n; i++) {
    cout << arr[i].name << " " << arr[i].surname << endl;
  }
  Clear(arr, n);
  delete[] arr;
  return 0;
}

#include <iostream>

int main() {
  int n, element;
  std::cin >> n;
  int arr[n];
  for (int i; i < n; ++i) {
    std::cin >> arr[i];
  }
  for (int i = 0, k = 0; i < n; ++i) {
    if (arr[i] % 2 == 0) {
      std::swap(arr[i], arr[k++]);
    }
  }
  for (auto &element : arr) {
    std::cout << element << ' ';
  }
  return 0;
}

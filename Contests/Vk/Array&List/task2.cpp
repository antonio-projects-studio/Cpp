#include <iostream>
#include <vector>
int main() {
  int n, element, cnt = 0;
  std::cin >> n;
  std::vector<int> arr(n);
  for (int i; i < n; ++i) {
    std::cin >> arr[i];
  }
  for (int i = 0, k = 0; i < n; ++i) {
    if (arr[i] == 0) {
      arr.erase(arr.begin() + i--);
      --n;
      ++cnt;
    }
  }
  for (int i = 0; i < cnt; ++i) {
    arr.push_back(0);
  }
  for (auto &element : arr) {
    std::cout << element << ' ';
  }
  return 0;
}

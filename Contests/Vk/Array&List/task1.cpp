#include <iostream>
#include <vector>

int main() {
  int n, element;
  std::cin >> n;
  std::vector<int> arr(n);
  for (int i; i < n; ++i) {
    std::cin >> arr[i];
  }
  std::cin >> element;
  for (int i = 0; i < n; ++i) {
    if (arr[i] == element) {
      arr.erase(arr.begin() + i--);
      --n;
    }
  }
  std::cout << arr.size() << '\n';
  return 0;
}

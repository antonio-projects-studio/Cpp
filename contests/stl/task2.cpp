#include <algorithm>
#include <iostream>
#include <vector>

int FindCnt(const std::vector<int> &vector, const int number) {
  auto iter_1 = std::lower_bound(vector.begin(), vector.end(), number);
  if (iter_1 != vector.end() && *iter_1 == number) {
    auto iter_2 = std::upper_bound(iter_1, vector.end(), number);
    return static_cast<int>(iter_2 - iter_1);
  }
  return 0;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<int> vector;
  for (int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;
    vector.push_back(a);
  }
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;
    std::cout << FindCnt(vector, a) << '\n';
  }
  return 0;
}

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> peaks;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int f;
    std::cin >> f;
    peaks.push_back(f);
  }
  int x;
  std::cin >> x;
  std::cout << std::count(peaks.begin(), peaks.end(), x);
  return 0;
}

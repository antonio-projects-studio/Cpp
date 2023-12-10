#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int cnt;
  std::cin >> cnt;
  std::vector<std::vector<int>> peaks(cnt);
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;
    if (a == 1) {
      int b, c;
      std::cin >> b >> c;
      peaks[b - 1].push_back(c);
      peaks[c - 1].push_back(b);
    }
    if (a == 2) {
      int b;
      std::cin >> b;
      for (auto item : peaks[b - 1]) {
        std::cout << item << ' ';
      }
      std::cout << '\n';
    }
  }
  return 0;
}
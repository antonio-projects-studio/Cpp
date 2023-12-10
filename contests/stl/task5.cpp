#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::unordered_map<std::string, std::string> map;
  int n;
  std::cin >> n;
  std::string first, second;
  for (int i = 0; i < n; ++i) {
    std::cin >> first >> second;
    map[first] = second;
    map[second] = first;
  }
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> first;
    std::cout << map[first] << '\n';
  }
  return 0;
}
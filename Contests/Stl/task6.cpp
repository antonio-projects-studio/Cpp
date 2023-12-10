#include <algorithm>
#include <iostream>
#include <map>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::map<std::string, int> map;
  int n;
  std::cin >> n;
  std::string name;
  int command, val;
  for (int i = 0; i < n; ++i) {
    std::cin >> command;
    std::cin >> name;
    if (command == 1) {
      std::cin >> val;
      map[name] += val;
      continue;
    }
    if (map.find(name) != map.end()) {
      std::cout << map[name] << '\n';
      continue;
    }
    std::cout << "ERROR" << '\n';
  }
  return 0;
}

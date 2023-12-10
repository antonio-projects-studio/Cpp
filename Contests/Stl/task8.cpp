#include <iostream>
#include <map>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::map<std::string, int> map;
  std::map<std::string, std::map<std::string, int64_t>> table;
  std::string name, thing;
  int val;
  while (std::cin >> name) {
    std::cin >> thing;
    std::cin >> val;
    table[name][thing] += val;
  }
  for (auto &[item, item2] : table) {
    std::cout << item << ':' << '\n';
    for (auto &[item_1, item_2] : item2) {
      std::cout << item_1 << ' ' << item_2 << '\n';
    }
  }
  return 0;
}
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Comparator {
  Comparator() = default;

  bool operator()(const std::pair<int, std::string> &left,
                  const std::pair<int, std::string> &right) {
    if (left.first != right.first) {
      return left.first > right.first;
    }
    return left.second < right.second;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::map<std::string, int> map;
  std::string word;
  while (std::cin >> word) {
    ++map[word];
  }
  std::vector<std::pair<int, std::string>> vector;
  for (auto &[item1, item2] : map) {
    vector.emplace_back(item2, item1);
  }
  std::sort(vector.begin(), vector.end(), Comparator());
  for (auto &[item1, item2] : vector) {
    std::cout << item2 << '\n';
  }
  return 0;
}

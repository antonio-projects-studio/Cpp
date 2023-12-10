#include <iostream>
#include <map>
#include <queue>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::map<std::string, int> map;
  std::priority_queue<int64_t, std::vector<int64_t>, std::greater<>> queue;
  int n;
  std::cin >> n;
  int number;
  for (int i = 0; i < n; ++i) {
    std::cin >> number;
    queue.push(number);
  }
  double cnt{0};
  while (queue.size() != 1) {
    int64_t left, right;
    left = queue.top();
    queue.pop();
    right = queue.top();
    queue.pop();
    cnt += static_cast<double>(left + right) / 20;
    queue.push(left + right);
  }
  std::cout << cnt;
  return 0;
}

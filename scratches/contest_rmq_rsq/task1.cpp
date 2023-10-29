#include <iostream>
#include <vector>

int main() {
  std::vector<int64_t> sum;
  size_t n = 0;
  std::cin >> n;
  int voice;
  sum.resize(n + 1);
  sum.push_back(0);
  for (size_t i = 1; i < n + 1; ++i) {
    std::cin >> voice;
    sum[i] = sum[i - 1] + voice;
  }
  int cnt_command;
  std::cin >> cnt_command;
  std::pair<int, int> l_r;
  for (int i = 0; i < cnt_command; ++i) {
    std::cin >> l_r.first >> l_r.second;
    std::cout << sum[l_r.second] - sum[l_r.first - 1] << ' ';
  }
  return 0;
}

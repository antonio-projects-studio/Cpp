#include <algorithm>
#include <iostream>
#include <vector>

struct Team {
  int cnt_;
  int time_;
  int number_;

  Team(int x, int y, int z) : cnt_(x), time_(y), number_(z){};

  friend std::ostream &operator<<(std::ostream &os, const Team &team) {
    os << team.number_;
    return os;
  }
};

struct Comparator {
  Comparator() = default;

  bool operator()(const Team left, const Team right) {
    if (left.cnt_ != right.cnt_) {
      return left.cnt_ > right.cnt_;
    }
    if (left.time_ != right.time_) {
      return left.time_ < right.time_;
    }
    return left.number_ < right.number_;
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<Team> vector;
  for (int i = 1; i <= n; ++i) {
    int a, b;
    std::cin >> a >> b;
    vector.emplace_back(a, b, i);
  }
  std::sort(vector.begin(), vector.end(), Comparator());
  for (int i = 0; i < n; ++i) {
    std::cout << vector[i] << '\n';
  }
  return 0;
}

#include <iostream>
#include <vector>

inline int F(int i) { return (i | (i + 1)); }

inline int G(int i) { return i & (i + 1); }

class Fenv {
public:
  std::vector<int64_t> &tree_;
  std::vector<int64_t> &tree2_;

  Fenv(std::vector<int64_t> &tree, std::vector<int64_t> &tree2)
      : tree_(tree), tree2_(tree2) {}

  void Update(std::vector<int64_t> &tree, int idx, int a) {
    int i = 0, size = 0;
    for (i = idx, size = tree.size(); i < size; i = F(i)) {
      tree[i] += a;
    }
  }

  void UpdateUp(int begin, int end, int a) {
    Update(tree_, begin, a);
    Update(tree_, end, -a);
    Update(tree2_, begin, begin * a);
    Update(tree2_, end, end * (-a));
  }

  int64_t Query(int idx) {
    int64_t ans = 0;
    for (int i = idx; i >= 0; i = G(i) - 1) {
      ans += ((idx + 1) * tree_[i] - tree2_[i]);
    }
    return ans;
  }
};

int main() {
  int n = 0, m = 0, help = 0, begin = 0, end = 0, a = 0;
  std::cin >> n >> m;
  std::vector<int64_t> tree(n, 0);
  std::vector<int64_t> tree2(n, 0);
  Fenv fenv(tree, tree2);
  for (int i = 0; i < m; i++) {
    std::cin >> help;
    if (help == 1) {
      std::cin >> begin >> end >> a;
      fenv.UpdateUp(begin, end, a);
    } else if (help == 2) {
      std::cin >> begin >> end;
      if (begin == 0) {
        std::cout << fenv.Query(end - 1) << "\n";
      } else {
        std::cout << (fenv.Query(end - 1) - fenv.Query(begin - 1)) << "\n";
      }
    }
  }
  return 0;
}
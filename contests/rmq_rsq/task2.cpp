#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int Neutral(const std::string &op) {
  if (op == "max") {
    return -1000000000;
  }
  if (op == "+") {
    return 0;
  }
  return 100000000;
}

struct Node {
  int result;
  int promise;

  Node() = default;

  Node(int res) : result(res), promise(0){}; // NOLINT

  friend std::ostream &operator<<(std::ostream &os, const Node &node);
};

std::ostream &operator<<(std::ostream &os, const Node &node) {
  os << node.result;
  return os;
}

inline bool operator==(const Node &lhs, const Node &rhs) {
  return lhs.result == rhs.result;
}

inline bool operator<(const Node &lhs, const Node &rhs) {
  return lhs.result < rhs.result;
}

Node Parent(const Node &lhs, const Node &rhs, const std::string &op) {
  if (op == "max") {
    if (lhs == rhs) {
      return {lhs.result};
    }
    if (lhs < rhs) {
      return {rhs.result};
    }
    return {lhs.result};
  }
  return {0};
}

inline Node &UpdateResult(Node &node, int push, std::string &op) {
  if (op == "+") {
    node.result += push;
  }
  return node;
}

inline Node &UpdatePromise(Node &node, int push, std::string &op) {
  if (op == "+") {
    node.promise += push;
  }
  return node;
}

class SegmentTree {
private:
  std::vector<Node> tree_;
  int neutral_;
  std::string operator_for_build_;
  std::string operator_for_update_;
  static int32_t log(int32_t); // NOLINT

  static size_t left_son(size_t idx); // NOLINT

  static size_t right_son(size_t idx); // NOLINT

public:
  SegmentTree(const std::vector<int> &vec, std::string op, std::string op2)
      : neutral_(Neutral(op)), operator_for_build_(op),
        operator_for_update_(std::move(op2)) {
    auto size = static_cast<int64_t>(vec.size());
    tree_.resize(2 * log(static_cast<int32_t>(size)) - 1);
    auto size2 = static_cast<int64_t>(tree_.size());
    int64_t i = static_cast<int64_t>(size2) / 2;
    for (size_t j = 0; i < size2 / 2 + size; ++i, ++j) {
      tree_[i] = {vec[j]};
    }
    for (; i < size2; ++i) {
      tree_[i] = {neutral_};
    }
    i = static_cast<int64_t>(size2) / 2 - 1;
    for (; i >= 0; --i) {
      tree_[i] = Parent(tree_[2 * i + 1], tree_[2 * i + 2], op);
    }
  }

  Node Query(int l, int r, size_t node, int a, int b) { // NOLINT
    if (a >= l && b <= r) {
      return {tree_[node].result + tree_[node].promise};
    }
    if (a > r || b < l) {
      return {neutral_};
    }
    Push(node);
    auto left_res = Query(l, r, left_son(node), a, (a + b) / 2);
    auto right_res = Query(l, r, right_son(node), (a + b) / 2 + 1, b);
    return Parent(left_res, right_res, operator_for_build_);
  }

  Node Segment(int l, int r) {
    return Query(l, r, 0, 1, static_cast<int>(tree_.size()) / 2 + 1);
  }

  void UpdateSegment(int l, int r, int add) {
    return Update(l, r, 0, 1, static_cast<int>(tree_.size()) / 2 + 1, add);
  }

  void Push(size_t idx) {
    auto promise = tree_[idx].promise;
    tree_[idx].result += promise;
    tree_[idx].promise = 0;
    tree_[left_son(idx)].promise += promise;
    tree_[right_son(idx)].promise += promise;
  }

  void Update(int l, int r, size_t node, int a, int b, int add) { // NOLINT
    if (a >= l && b <= r) {
      UpdatePromise(tree_[node], add, operator_for_update_);
      return;
    }
    if (a > r || b < l) {
      return;
    }
    Push(node);
    Update(l, r, left_son(node), a, (a + b) / 2, add);
    Update(l, r, right_son(node), (a + b) / 2 + 1, b, add);
    auto x =
        Parent(Query(a, (a + b) / 2, left_son(node), a, (a + b) / 2),
               Query((a + b) / 2 + 1, b, right_son(node), (a + b) / 2 + 1, b),
               operator_for_build_)
            .result;
    tree_[node].result = x;
  }
  friend std::ostream &operator<<(std::ostream &os,
                                  const SegmentTree &segment_tree);
};

inline int32_t SegmentTree::log(int32_t n) { // NOLINT
  uint32_t val = 1 << (31 - __builtin_clz(n));
  if (n % val) {
    val *= 2;
  }
  return val;
}

int32_t loglog(size_t n) { // NOLINT
  int32_t i = 31 - __builtin_clz(n);
  return i;
}

std::ostream &operator<<(std::ostream &os, const SegmentTree &segment_tree) {
  int n = loglog(segment_tree.tree_.size() / 2 + 1);
  int m = 0;
  for (int i = 0; i <= n; ++i) {
    auto cnt = std::pow(2, i);
    for (int k = 0; k < cnt; ++k) {
      os << segment_tree.tree_[m++].result << ' ';
    }
    os << '\n';
  }
  return os;
}

inline size_t SegmentTree::left_son(size_t idx) { // NOLINT
  return 2 * idx + 1;
}

inline size_t SegmentTree::right_son(size_t idx) { // NOLINT
  return 2 * idx + 2;
}

int main() {
  std::vector<int> vec;
  int n;
  std::cin >> n;
  vec.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    vec.push_back(x);
  }
  SegmentTree tree(vec, "max", "+");
  int x;
  std::cin >> x;
  std::pair<int, int> pair;
  int add;
  char command;
  for (int i = 0; i < x; ++i) {
    std::cin >> command;
    if (command == 'm') {
      std::cin >> pair.first >> pair.second;
      std::cout << tree.Segment(pair.first, pair.second) << ' ';
      continue;
    }
    std::cin >> pair.first >> pair.second >> add;
    tree.UpdateSegment(pair.first, pair.second, add);
  }
  return 0;
}
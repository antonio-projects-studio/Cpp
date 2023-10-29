#include <iostream>
#include <utility>
#include <vector>

struct Node;

using Key = int64_t;
using Priority = int64_t;
using NodeTree = Node *;
using Value = int64_t;

struct Node {
  Key key;
  Priority priority;
  Value value{};
  Value result{};
  size_t size{};
  NodeTree left_son{};
  NodeTree right_son{};
  NodeTree parent{};

  Node(Key key1, Priority priority1, Value value1, Value result1, size_t size1)
      : key(key1), priority(priority1), value(value1), result(result1),
        size(size1){};
};

class Treap {
public:
  NodeTree Merge(NodeTree lhs, NodeTree rhs) { // NOLINT
    if (lhs == nullptr) {
      return rhs;
    }
    if (rhs == nullptr) {
      return lhs;
    }
    if (lhs->priority < rhs->priority) {
      lhs->right_son = Merge(lhs->right_son, rhs);
      lhs->right_son->parent = lhs;
      FixNode(lhs);
      return lhs;
    }
    rhs->left_son = Merge(lhs, rhs->left_son);
    rhs->left_son->parent = rhs;
    FixNode(rhs);
    return rhs;
  }

  size_t Size(NodeTree node) { // NOLINT
    if (node == nullptr) {
      return 0;
    }
    return node->size;
  }

  Value ResultNode(NodeTree node) { // NOLINT
    if (node != nullptr) {
      return node->result;
    }
    return 0;
  }

  void Move(Key l, Key r) {
    auto pair = Split(head_, l - 1);
    auto pair2 = Split(pair.second, r - l);
    head_ = Merge(Merge(pair2.first, pair.first), pair2.second);
  }

  void FixNode(NodeTree node) {
    if (node != nullptr) {
      node->size = Size(node->left_son) + Size(node->right_son) + 1;
      node->result = ResultNode(node->left_son) + ResultNode(node->right_son) +
                     node->value;
    }
  }

  std::pair<NodeTree, NodeTree> Split(NodeTree node, Key x) { // NOLINT
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    int64_t k = 0;
    if (node->left_son != nullptr) {
      k += node->left_son->size;
    }
    if (x >= k) {
      auto pair = Split(node->right_son, x - k - 1);
      node->right_son = pair.first;
      FixNode(node);
      return {node, pair.second};
    }
    auto pair = Split(node->left_son, x);
    node->left_son = pair.second;
    FixNode(node);
    return {pair.first, node};
  }

  NodeTree Insert(Key x, Key y) {
    auto node_insert = new Node(y, rand(), y, y, 1);
    auto pair = Split(head_, x);
    head_ = Merge(Merge(pair.first, node_insert), pair.second);
    return head_;
  }

  [[nodiscard]] NodeTree Next(Key x) const {
    auto node = head_;
    NodeTree res = nullptr;
    while (true) {
      if (node != nullptr) {
        if (node->key == x) {
          node = node->right_son;
          while (node != nullptr) {
            node = node->left_son;
          }
          res = node;
          return res;
        }
        if (node->key < x) {
          node = node->right_son;
          continue;
        }
        res = node;
        node = node->left_son;
        continue;
      }
      return res;
    }
  }

  [[nodiscard]] NodeTree Prev(Key x) const {
    auto node = head_;
    NodeTree res = nullptr;
    while (true) {
      if (node != nullptr) {
        if (node->key == x) {
          node = node->left_son;
          while (node != nullptr) {
            node = node->right_son;
          }
          res = node;
          return res;
        }
        if (node->key > x) {
          node = node->left_son;
          continue;
        }
        res = node;
        node = node->right_son;
        continue;
      }
      return res;
    }
  }

  [[nodiscard]] bool Exist(Key x) const {
    auto node = head_;
    while (true) {
      if (node != nullptr) {
        if (node->key == x) {
          return true;
        }
        if (node->key > x) {
          node = node->left_son;
          continue;
        }
        node = node->right_son;
        continue;
      }
      return false;
    }
  }

  NodeTree Erase(NodeTree node, Key x) {
    auto pair = Split(node, x);
    auto pair2 = Split(pair.second, x + 1);
    delete pair2.first;
    head_ = Merge(pair.first, pair2.second);
    return head_;
  }

  NodeTree OrdinalStatistics(size_t k) {
    auto node = head_;
    while (node != nullptr) {
      if (Size(node->left_son) < k) {
        k -= Size(node->left_son) + 1;
        node = node->right_son;
      } else if (Size(node->left_son) > k) {
        node = node->left_son;
      } else {
        return node;
      }
    }
    return nullptr;
  }

  Value Query(Key l, Key r) {
    auto pair = Split(head_, l);
    auto pair2 = Split(pair.second, r);
    Value result = 0;
    if (pair2.first != nullptr) {
      result = pair2.first->result;
    }
    head_ = Merge(Merge(pair.first, pair2.first), pair2.second);
    return result;
  }

  NodeTree Build(std::vector<std::pair<Key, Priority>> &vec) { // NOLINT
    NodeTree root = nullptr;
    NodeTree last_insert = nullptr;
    for (auto &[x, y] : vec) {
      auto node = new Node(x, y, 1, 1, 1);
      auto curr = last_insert;
      while (curr && curr->priority > y) {
        curr = curr->parent;
      }
      if (curr == nullptr) {
        node->left_son = root;
        if (root != nullptr) {
          root->parent = node;
        }
        root = node;
      } else {
        node->left_son = curr->right_son;
        if (curr->right_son != nullptr) {
          curr->right_son->parent = node;
        }
        curr->right_son = node;
        node->parent = curr;
      }
      last_insert = node;
    }
    head_ = root;
    return root;
  }

  void Clear(NodeTree node) { // NOLINT
    if (node == nullptr) {
      return;
    }
    Clear(node->left_son);
    Clear(node->right_son);
    delete node;
  }

  ~Treap() { Clear(head_); }

public:
  NodeTree head_ = nullptr;
};

int main() {
  Treap treap;
  int n, m;
  std::cin >> n >> m;
  int left = 0, right = 0;
  for (int i = 0; i < n; i++) {
    treap.Insert(i, i + 1);
  }
  for (int i = 0; i < m; ++i) {
    std::cin >> left >> right;
    treap.Move(left - 1, right - 1);
  }

  for (int i = 0; i < n; ++i) {
    std::cout << treap.OrdinalStatistics(i)->key << ' ';
  }
  std::cout << '\n';
  return 0;
}

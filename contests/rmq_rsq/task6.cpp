#include <iostream>
#include <utility>
#include <vector>

struct Node;

using ImplicitKey = size_t;
using Priority = int;
using NodeTree = Node *;
using ResultName = int;
using Value = int;

struct Node {
  Value value;
  Priority priority;
  size_t size{};
  ResultName result;
  NodeTree left_son{};
  NodeTree right_son{};
  NodeTree parent{};

  Node(Value value1, Priority priority1)
      : value(value1), priority(priority1), size(1), result(value1){};
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

  ResultName Result(NodeTree node) { // NOLINT
    if (node == nullptr) {
      return 1000000000;
    }
    return node->result;
  }

  void FixNode(NodeTree node) {
    if (node != nullptr) {
      node->size = Size(node->left_son) + Size(node->right_son) + 1;
      node->result =
          std::min(std::min(Result(node->left_son), Result(node->right_son)),
                   node->value);
    }
  }

  ResultName Query(ImplicitKey l, ImplicitKey r) {
    auto pair = Split(head_, l);
    auto n = r - Size(pair.first);
    ResultName result = 0;
    if (n <= size_) {
      auto pair2 = Split(pair.second, n);
      if (pair2.first != nullptr) {
        result = pair2.first->result;
      }
      head_ = Merge(Merge(pair.first, pair2.first), pair2.second);
    } else {
      if (pair.second != nullptr) {
        result = pair.second->result;
      }
      head_ = Merge(pair.first, pair.second);
    }
    return result;
  }

  std::pair<NodeTree, NodeTree> Split(NodeTree node, ImplicitKey x) { // NOLINT
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    if (Size(node->left_son) < x) {
      auto pair = Split(node->right_son, x - Size(node->left_son) - 1);
      node->right_son = pair.first;
      if (pair.first != nullptr) {
        pair.first->parent = node;
      }
      if (pair.second != nullptr) {
        pair.second->parent = nullptr;
      }
      FixNode(node);
      return {node, pair.second};
    }
    auto pair = Split(node->left_son, x);
    node->left_son = pair.second;
    if (pair.second != nullptr) {
      pair.second->parent = node;
    }
    if (pair.first != nullptr) {
      pair.first->parent = nullptr;
    }
    FixNode(node);
    return {pair.first, node};
  }

  NodeTree Insert(ImplicitKey x, Value val) {
    ++size_;
    auto node_insert = new Node(val, rand());
    auto pair = Split(head_, x);
    head_ = Merge(Merge(pair.first, node_insert), pair.second);
    return head_;
  }

  NodeTree Erase(NodeTree node, ImplicitKey x) {
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

  void Clear(NodeTree node) {
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
  size_t size_ = 0;
};

int main() {
  int n;
  Treap treap;
  std::cin >> n;
  char a;
  int b, c;
  for (int i = 0; i < n; ++i) {
    std::cin >> a >> b >> c;
    if (a == '?') {
      std::cout << treap.Query(b - 1, c) << '\n';
    } else {
      treap.Insert(b, c);
    }
  }
}
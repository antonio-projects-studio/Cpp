#include <iostream>

struct Node {
  int balance = 0;
  int data = 0;
  Node *parent = nullptr;
  Node *right = nullptr;
  Node *left = nullptr;
};

struct AVL {
  Node *top = nullptr;
  void Push(int n) {
    Node *ptr = new Node;
    ptr->data = n;
    if (top == nullptr) {
      top = ptr;
      return;
    }
    Node *copy = top;
    while (true) {
      if (copy->data < n) {
        if (copy->right == nullptr) {
          copy->right = ptr;
          ptr->parent = copy;
          break;
        }
        copy = copy->right;
        continue;
      }
      if (copy->data > n) {
        if (copy->left == nullptr) {
          copy->left = ptr;
          ptr->parent = copy;
          break;
        }
        copy = copy->left;
        continue;
      }
      break;
    }
    Balance(ptr);
  }

  void Balance(Node *ptr) {
    while (true) {
      if (ptr->parent == nullptr) {
        break;
      }
      if (ptr->parent->right == ptr) {
        --ptr->parent->balance;
        if (ptr->parent->balance == 0) {
          break;
        }
        if (ptr->parent->balance == -1) {
          ptr = ptr->parent;
          continue;
        }
        if (ptr->parent->balance == -2) {
          if (ptr->balance == 1) {
            BigLeft(ptr->parent);
            break;
          }
        }
        LittleLeft(ptr->parent);
        if (ptr->balance == 0) {
          break;
        }
        continue;
      }
      ++ptr->parent->balance;
      if (ptr->parent->balance == 0) {
        break;
      }
      if (ptr->parent->balance == 1) {
        ptr = ptr->parent;
        continue;
      }
      if (ptr->parent->balance == 2) {
        if (ptr->balance == -1) {
          BigRight(ptr->parent);
          break;
        }
      }
      LittleRight(ptr->parent);
      if (ptr->balance == 0) {
        break;
      }
    }
  }

  void LittleLeft(Node *ptr) {
    Node *copy = ptr->right->left;
    ptr->right->left = ptr;
    if (ptr->parent != nullptr) {
      if (ptr->parent->right == ptr) {
        ptr->parent->right = ptr->right;
      } else {
        ptr->parent->left = ptr->right;
      }
      ptr->right->parent = ptr->parent;
    } else {
      top = ptr->right;
      ptr->right->parent = nullptr;
    }
    ptr = ptr->right;
    ptr->left->right = copy;
    ptr->left->parent = ptr;
    if (copy != nullptr) {
      copy->parent = ptr->left;
    }
    if (ptr->left->balance == -1 && ptr->balance == 0) {
      ptr->left->balance = 0;
      ptr->balance = 1;
      return;
    }
    if (ptr->left->balance == -1 && ptr->balance == -1) {
      ptr->left->balance = 1;
      ptr->balance = 1;
      return;
    }
    if (ptr->left->balance == -1 && ptr->balance == 1) {
      ptr->left->balance = 0;
      ptr->balance = 2;
      return;
    }
    if (ptr->left->balance == -2 && ptr->balance == -2) {
      ptr->left->balance = 1;
      ptr->balance = 0;
      return;
    }
    ptr->left->balance = -1;
    if (ptr->balance == 0) {
      ptr->balance = 1;
      return;
    }
    ptr->left->balance = 0;
    ptr->balance = 0;
  }

  void LittleRight(Node *ptr) {
    Node *copy = ptr->left->right;
    ptr->left->right = ptr;
    if (ptr->parent != nullptr) {
      if (ptr->parent->right == ptr) {
        ptr->parent->right = ptr->left;
      } else {
        ptr->parent->left = ptr->left;
      }
      ptr->left->parent = ptr->parent;
    } else {
      top = ptr->left;
      ptr->left->parent = nullptr;
    }
    ptr = ptr->left;
    ptr->right->left = copy;
    ptr->right->parent = ptr;
    if (copy != nullptr) {
      copy->parent = ptr->right;
    }
    if (ptr->right->balance == 1 && ptr->balance == 0) {
      ptr->right->balance = 0;
      ptr->balance = -1;
      return;
    }
    if (ptr->right->balance == 1 && ptr->balance == 1) {
      ptr->right->balance = -1;
      ptr->balance = -1;
      return;
    }
    if (ptr->right->balance == 1 && ptr->balance == -1) {
      ptr->right->balance = 0;
      ptr->balance = -2;
      return;
    }
    if (ptr->right->balance == 2 && ptr->balance == 2) {
      ptr->left->balance = -1;
      ptr->balance = 0;
      return;
    }
    ptr->right->balance = 1;
    if (ptr->balance == 0) {
      ptr->balance = -1;
      return;
    }
    ptr->right->balance = 0;
    ptr->balance = 0;
  }

  void BigLeft(Node *ptr) {
    LittleRight(ptr->right);
    LittleLeft(ptr);
  }

  void BigRight(Node *ptr) {
    LittleLeft(ptr->left);
    LittleRight(ptr);
  }

  int Next(int z) {
    Node *copy = top;
    int next = -1;
    while (true) {
      if (copy == nullptr) {
        break;
      }
      if (copy->data > z && copy->left != nullptr) {
        next = copy->data;
        copy = copy->left;
        continue;
      }
      if ((copy->data > z && copy->left == nullptr) || copy->data == z) {
        return copy->data;
      }
      copy = copy->right;
    }
    return next;
  }

  void Clear(Node *ptr) {
    if (ptr == nullptr) {
      return;
    }
    Clear(ptr->left);
    Clear(ptr->right);
    delete ptr;
  }
};

int main() {
  AVL arr;
  int n;
  std::cin >> n;
  int cnt = 0;
  int y = 0;
  for (int i = 0; i < n; ++i) {
    char a;
    std::cin >> a;
    if (a == '+') {
      int x;
      std::cin >> x;
      if (cnt == 1) {
        int res = (x + y) % 1000000000;
        arr.Push(res);
        cnt = 0;
        continue;
      }
      arr.Push(x);
      continue;
    }
    int z;
    std::cin >> z;
    y = arr.Next(z);
    std::cout << y << '\n';
    cnt = 1;
  }
  arr.Clear(arr.top);
  return 0;
}

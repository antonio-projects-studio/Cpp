#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>

struct Node {
  Node *next = nullptr;
  Node *pred = nullptr;
  int data;
};

struct Dec {
  Node *top = nullptr;
  Node *down = nullptr;
  int size = 0;

  void Pushfront(int value) {
    Node *pv = new Node;
    pv->pred = top;
    pv->data = value;
    if (size != 0) {
      top->next = pv;
      top = pv;
      ++size;
    } else {
      top = pv;
      down = pv;
      ++size;
    }
  }

  void Pushback(int value) {
    Node *pv = new Node;
    pv->next = down;
    pv->data = value;
    if (size != 0) {
      down->pred = pv;
      down = pv;
      ++size;
    } else {
      top = pv;
      down = pv;
      ++size;
    }
  }

  int Front() { return top->data; }

  int Back() { return down->data; }

  int Size() { return size; }

  int Popfront() {
    Node *copy = top;
    int a = top->data;
    top = top->pred;
    delete copy;
    --size;
    return a;
  }

  int Popback() {
    if (size != 0) {
      Node *copy = down;
      int a = down->data;
      down = down->next;
      delete copy;
      --size;
      return a;
    }
    return 0;
  }

  void Clear() {
    if (size != 0) {
      while (size != 1) {
        Node *copy = top;
        top = top->pred;
        if (top != nullptr) {
          top->next = nullptr;
        }
        delete copy;
        --size;
      }
      Node *copy = top;
      top = nullptr;
      down = nullptr;
      --size;
      delete copy;
    }
  }
};

int main() {
  Dec st;
  int n;
  std::cin >> n;
  char *command = new char[n];
  char arr[9][20] = {"front",      "back",      "size",
                     "clear",      "pop_back",  "pop_front",
                     "push_front", "push_back", "exit"};
  std::cin.ignore(32767, '\n');
  for (int i = 0; i < n; ++i) {
    std::cin >> command;
    if (strcoll(command, arr[0]) == 0) {
      if (st.size != 0) {
        std::cout << st.Front() << '\n';
        continue;
      }
      std::cout << "error" << '\n';
      continue;
    }
    if (strcoll(command, arr[1]) == 0) {
      if (st.size != 0) {
        std::cout << st.Back() << '\n';
        continue;
      }
      std::cout << "error" << '\n';
      continue;
    }
    if (strcoll(command, arr[2]) == 0) {
      std::cout << st.Size() << '\n';
      continue;
    }
    if (strcoll(command, arr[3]) == 0) {
      if (st.size != 0) {
        st.Clear();
        std::cout << "ok" << '\n';
        continue;
      }
      std::cout << "ok" << '\n';
      continue;
    }
    if (strcoll(command, arr[4]) == 0) {
      if (st.size != 0) {
        std::cout << st.Popback() << '\n';
        continue;
      }
      std::cout << "error" << '\n';
      continue;
    }
    if (strcoll(command, arr[5]) == 0) {
      if (st.size != 0) {
        std::cout << st.Popfront() << '\n';
        continue;
      }
      std::cout << "error" << '\n';
      continue;
    }
    if (strcoll(command, arr[6]) == 0) {
      int number;
      std::cin >> number;
      st.Pushfront(number);
      std::cout << "ok" << '\n';
      continue;
    }
    if (strcoll(command, arr[7]) == 0) {
      int number;
      std::cin >> number;
      st.Pushback(number);
      std::cout << "ok" << '\n';
      continue;
    }
    if (strcoll(command, arr[8]) == 0) {
      std::cout << "bye" << '\n';
    }
  }
  st.Clear();
  delete[] command;
  return 0;
}

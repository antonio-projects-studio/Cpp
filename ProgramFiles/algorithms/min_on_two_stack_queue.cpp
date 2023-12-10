#include <cstring>
#include <iostream>
#include <sstream>

int Min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}

struct Node {
  Node *next = nullptr;
  Node *pred = nullptr;
  int data;
  int min = 0;
};

struct Dec {
  Node *top = nullptr;
  Node *down = nullptr;
  int size = 0;
  int minimum = 0;

  void Pushfront(int value) {
    Node *pv = new Node;
    pv->pred = top;
    pv->data = value;
    if (size != 0) {
      top->next = pv;
      top = pv;
      if (pv->data < minimum) {
        minimum = pv->data;
        pv->min = minimum;
      } else {
        pv->min = minimum;
      }
      ++size;
    } else {
      minimum = pv->data;
      pv->min = minimum;
      top = pv;
      down = pv;
      ++size;
    }
  }

  int Front() { return top->data; }

  int Back() { return down->data; }

  int Size() { return size; }

  int Dequeue() {
    Node *copy = top;
    int a = top->data;
    top = top->pred;
    if (top != nullptr) {
      top->next = nullptr;
    }
    delete copy;
    --size;
    return a;
  }

  void Clear() {
    if (size != 0) {
      while (size != 1) {
        Node *copy = top;
        top = top->pred;
        top->next = nullptr;
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

void Change(Dec &st1, Dec &st2) {
  while (st1.size != 0) {
    st2.Pushfront(st1.top->data);
    st1.Dequeue();
  }
}

int main() {
  Dec st1, st2;
  int n;
  std::cin >> n;
  char *command = new char[n];
  char arr[6][20] = {"front", "size", "clear", "dequeue", "enqueue", "min"};
  std::cin.ignore(32767, '\n');
  for (int i = 0; i < n; ++i) {
    std::cin >> command;
    if (strcoll(command, arr[4]) == 0) {
      int number;
      std::cin >> number;
      st1.Pushfront(number);
      std::cout << "ok" << '\n';
      continue;
    }
    if (strcoll(command, arr[0]) == 0) {
      if (st1.size != 0 || st2.size != 0) {
        if (st2.size != 0) {
          std::cout << st2.Front() << '\n';
          continue;
        }
        std::cout << st1.Back() << '\n';
        continue;
      }
      std::cout << "error" << '\n';
      continue;
    }
    if (strcoll(command, arr[5]) == 0) {
      if (st1.size != 0 || st2.size != 0) {
        if (st1.size != 0 && st2.size != 0) {
          std::cout << Min(st1.top->min, st2.top->min) << '\n';
          continue;
        }
        if (st1.size != 0) {
          std::cout << st1.top->min << '\n';
          continue;
        }
        if (st2.size != 0) {
          std::cout << st2.top->min << '\n';
          continue;
        }
      }
      std::cout << "error" << '\n';
      continue;
    }
    if (strcoll(command, arr[1]) == 0) {
      std::cout << st1.size + st2.size << '\n';
      continue;
    }
    if (strcoll(command, arr[2]) == 0) {
      st1.Clear();
      st2.Clear();
      std::cout << "ok" << '\n';
      continue;
    }
    if (st1.size != 0 || st2.size != 0) {
      if (st2.size != 0) {
        std::cout << st2.Dequeue() << '\n';
        continue;
      }
      Change(st1, st2);
      std::cout << st2.Dequeue() << '\n';
      continue;
    }
    std::cout << "error" << '\n';
  }
  st1.Clear();
  st2.Clear();
  delete[] command;
  return 0;
}

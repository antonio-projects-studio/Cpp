#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

struct Pyramid {
  int size = 0;
  int *arr = nullptr;
  int capasity = 0;

  void Realloc() {
    arr = (int *)realloc(arr, 2 * (capasity + 1) * sizeof(int));
    capasity = 2 * (capasity + 1);
  }

  void SiftUp(int i, int cnt) {
    if (size != 0) {
      if (cnt == 0) {
        while (i > 2 && arr[i] < arr[(i - 3) / 4]) {
          std::swap(arr[i], arr[(i - 3) / 4]);
          i = (i - 3) / 4;
        }
        return;
      }
      while (i > 2 && arr[i] > arr[(i - 3) / 4]) {
        std::swap(arr[i], arr[(i - 3) / 4]);
        i = (i - 3) / 4;
      }
    }
  }

  void SiftDown(int i, int cnt) {
    if (size != 0) {
      if (cnt == 0) {
        while (4 * i + 3 < size) {
          int left1 = 4 * i + 3;
          int right1 = 4 * i + 4;
          int left2 = 4 * i + 5;
          int right2 = 4 * i + 6;
          int j = left1;
          if (right1 < size && arr[right1] < arr[left1]) {
            j = right1;
          }
          if (left2 < size && arr[left2] < arr[j]) {
            j = left2;
          }
          if (right2 < size && arr[right2] < arr[j]) {
            j = right2;
          }
          if (arr[i] > arr[j]) {
            std::swap(arr[i], arr[j]);
            SiftDown(i, 0);
            i = j;
            continue;
          }
          break;
        }
        if (2 * i + 1 < size) {
          int left = 2 * i + 1;
          int right = 2 * i + 2;
          int j = left;
          if (right < size && arr[right] < arr[left]) {
            j = right;
          }
          if (arr[i] > arr[j]) {
            std::swap(arr[i], arr[j]);
            SiftUp(j, 1);
            SiftUp(i, 0);
          }
          return;
        }
        if ((i - 1) / 2 > 0) {
          if (arr[i] > arr[(i - 1) / 2]) {
            std::swap(arr[i], arr[(i - 1) / 2]);
            SiftUp(i, 0);
            SiftUp((i - 1) / 2, 1);
          }
        }
        return;
      }
      while (4 * i + 3 < size) {
        int left1 = 4 * i + 3;
        int right1 = 4 * i + 4;
        int left2 = 4 * i + 5;
        int right2 = 4 * i + 6;
        int j = left1;
        if (right1 < size && arr[right1] > arr[left1]) {
          j = right1;
        }
        if (left2 < size && arr[left2] > arr[j]) {
          j = left2;
        }
        if (right2 < size && arr[right2] > arr[j]) {
          j = right2;
        }
        if (arr[i] < arr[j]) {
          std::swap(arr[i], arr[j]);
          SiftDown(i, 1);
          i = j;
          continue;
        }
        break;
      }
      if (2 * i + 1 < size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int j = left;
        if (right < size && arr[right] > arr[left]) {
          j = right;
        }
        if (arr[i] < arr[j]) {
          std::swap(arr[i], arr[j]);
          SiftUp(j, 0);
          SiftUp(i, 1);
        }
        return;
      }
      if ((i - 1) / 2 > 0) {
        if (arr[i] < arr[(i - 1) / 2]) {
          std::swap(arr[i], arr[(i - 1) / 2]);
          SiftUp(i, 1);
          SiftUp((i - 1) / 2, 0);
        }
      }
    }
  }

  void Insert(int n) {
    if (size == capasity) {
      Realloc();
    }
    ++size;
    arr[size - 1] = n;
    int deg = 1, cnt = 0;
    while (deg <= size) {
      deg *= 2;
      ++cnt;
    }
    --cnt;
    if (cnt > 0 && cnt % 2 == 0) {
      if (arr[size - 1] > arr[(size - 2) / 2]) {
        std::swap(arr[size - 1], arr[(size - 2) / 2]);
        SiftUp((size - 2) / 2, 1);
        return;
      }
      SiftUp(size - 1, 0);
      return;
    }
    if (cnt % 2 != 0) {
      if (arr[size - 1] < arr[(size - 2) / 2]) {
        std::swap(arr[size - 1], arr[(size - 2) / 2]);
        SiftUp((size - 2) / 2, 0);
        return;
      }
      SiftUp(size - 1, 1);
    }
  }

  int GetMax() {
    if (size == 0) {
      return -1;
    }
    int res;
    if (size == 1) {
      --size;
      return arr[0];
    }
    if (size == 2) {
      --size;
      return arr[1];
    }
    if (arr[1] > arr[2]) {
      res = arr[1];
      std::swap(arr[size - 1], arr[1]);
      --size;
      if (3 < size) {
        int left = 3;
        int right = 4;
        int j = left;
        if (right < size && arr[right] > arr[left]) {
          j = right;
        }
        if (arr[1] < arr[j]) {
          std::swap(arr[1], arr[j]);
        }
      }
      SiftDown(1, 1);
      SiftDown(2, 1);
      SiftDown(0, 0);
      return res;
    }
    res = arr[2];
    std::swap(arr[size - 1], arr[2]);
    --size;
    if (5 < size) {
      int left = 5;
      int right = 6;
      int j = left;
      if (right < size && arr[right] > arr[left]) {
        j = right;
      }
      if (arr[2] < arr[j]) {
        std::swap(arr[2], arr[j]);
      }
    }
    SiftDown(2, 1);
    SiftDown(1, 1);
    SiftDown(0, 0);
    return res;
  }

  int GetMin() {
    if (size == 0) {
      return -1;
    }
    int res = arr[0];
    std::swap(arr[size - 1], arr[0]);
    --size;
    if (1 < size) {
      int left = 1;
      int right = 2;
      int j = left;
      if (right < size && arr[right] < arr[left]) {
        j = right;
      }
      if (arr[0] > arr[j]) {
        std::swap(arr[0], arr[j]);
      }
    }
    SiftDown(0, 0);
    SiftDown(1, 1);
    SiftDown(2, 1);
    return res;
  }

  int Min() {
    if (size == 0) {
      return -1;
    }
    int res = arr[0];
    return res;
  }

  int Max() {
    if (size == 0) {
      return -1;
    }
    int res;
    if (size == 1) {
      return arr[0];
    }
    if (size == 2) {
      return arr[1];
    }
    if (arr[1] > arr[2]) {
      res = arr[1];
      return res;
    }
    res = arr[2];
    return res;
  }

  void Clear() {
    free(arr);
    arr = nullptr;
    size = 0;
    capasity = 0;
  }
};

int main() {
  Pyramid array;
  char s[8][15] = {"insert",  "extract_min", "get_min", "extract_max",
                   "get_max", "size",        "clear",   "s"};
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    char comand[15];
    std::cin >> comand;
    if (strcmp(s[0], comand) == 0) {
      int x;
      std::cin >> x;
      array.Insert(x);
      std::cout << "ok" << '\n';
      continue;
    }
    if (strcmp(s[1], comand) == 0) {
      if (array.size == 0) {
        std::cout << "error" << '\n';
        continue;
      }
      std::cout << array.GetMin() << '\n';
      continue;
    }
    if (strcmp(s[2], comand) == 0) {
      if (array.size == 0) {
        std::cout << "error" << '\n';
        continue;
      }
      std::cout << array.Min() << '\n';
      continue;
    }
    if (strcmp(s[3], comand) == 0) {
      if (array.size == 0) {
        std::cout << "error" << '\n';
        continue;
      }
      std::cout << array.GetMax() << '\n';
      continue;
    }
    if (strcmp(s[4], comand) == 0) {
      if (array.size == 0) {
        std::cout << "error" << '\n';
        continue;
      }
      std::cout << array.Max() << '\n';
      continue;
    }
    if (strcmp(s[5], comand) == 0) {
      std::cout << array.size << '\n';
      continue;
    }
    if (strcmp(s[6], comand) == 0) {
      array.Clear();
      std::cout << "ok" << '\n';
      continue;
    }
    if (strcmp(s[7], comand) == 0) {
      for (int k = 0; k < array.size; ++k) {
        std::cout << array.arr[k] << ' ';
      }
      std::cout << '\n';
      continue;
    }
  }
  if (array.arr != nullptr) {
    array.Clear();
  }
  return 0;
}

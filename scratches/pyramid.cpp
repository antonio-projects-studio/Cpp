#include <iostream>
#include <cstring>

using namespace std;

struct Pyramid {
  int size = 0;
  int capasity = 0;
  int *arr = nullptr;
  int *ord = nullptr;
  int **pos = nullptr;

  void Allocate() {
    arr = (int *) realloc(arr, 2 * (capasity + 1) * sizeof(int));
    capasity = 2 * (capasity + 1);
  }

  void SiftUp(int i) {
    if (size != 0) {
      while (i > 0 && arr[i] <= arr[(i - 1) / 2]) {
        std::swap(arr[i], arr[(i - 1) / 2]);
        std::swap(*pos[i], *pos[(i - 1) / 2]);
        std::swap(pos[i], pos[(i - 1) / 2]);
        i = (i - 1) / 2;
      }
    }
  }

  void SiftDown(int i) {
    if (size != 0) {
      while (2 * i + 1 < size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int j = left;
        if (right < size && arr[right] <= arr[left]) {
          j = right;
        }

        if (arr[i] >= arr[j]) {
          std::swap(arr[i], arr[j]);
          std::swap(*pos[i], *pos[j]);
          std::swap(pos[i], pos[j]);
          i = j;
          continue;
        }
        return;
      }
    }
  }

  void Insert(int n, int x) {
    if (size == capasity) {
      Allocate();
    }
    ++size;
    arr[size - 1] = n;
    ord[x] = size - 1;
    pos[size - 1] = &(ord[x]);
    SiftUp(size - 1);
  }

  int Delete(int i, int cnt) {
    if (size == 0 || ord[i - 1] == -1 || cnt < i || i <= 0) {
      return -1;
    }
    int k = ord[i - 1];
    int z = arr[ord[i - 1]];
    std::swap(arr[k], arr[size - 1]);
    std::swap(*pos[k], *pos[size - 1]);
    std::swap(pos[k], pos[size - 1]);
    --size;
    SiftDown(k);
    SiftUp(k);
    ord[i - 1] = -1;
    return z;
  }

  int Change(int x, int y, int cnt) {
    if (size == 0 || ord[x - 1] == -1 || cnt < x || x <= 0) {
      return -1;
    }
    arr[ord[x - 1]] = y;
    SiftDown(ord[x - 1]);
    SiftUp(ord[x - 1]);
    return 1;
  }

  int ExtractMin() {
    if (size == 0) {
      return -1;
    }
    int min = arr[0];
    std::swap(arr[size - 1], arr[0]);
    std::swap(*pos[0], *pos[size - 1]);
    std::swap(pos[0], pos[size - 1]);
    *pos[size - 1] = -1;
    --size;
    SiftDown(0);
    return min;
  }

  int GetMin() {
    if (size == 0) {
      return -1;
    }
    return arr[0];
  }

  void Clear(int x) {
    size = 0;
    for (int i = 0; i < x; ++i) {
      ord[i] = -1;
    }
    delete [] pos;
    pos = new int * [x];
  }

  void Out() {
    for (int i = 0; i < size; i++) {
      std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
  }
};

int main() {
  Pyramid array;
  int n;
  char s[7][15] = {"insert", "extract_min", "delete", "change", "get_min", "size", "clear"};
  char s2[15];
  std::cin >> n;
  array.ord = new int[n];
  for (int i = 0; i < n; ++i) {
    array.ord[i] = -1;
  }
  array.pos = new int *[n];
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> s2;
    if (strcmp(s[0], s2) == 0) {
      int x;
      std::cin >> x;
      array.Insert(x, cnt);
      ++cnt;
      std::cout << "ok" << '\n';
      continue;
    }
    if (strcmp(s[1], s2) == 0) {
      int x;
      x = array.ExtractMin();
      if (x == -1) {
        std::cout << "error" << '\n';
        continue;
      }
      std::cout << x << '\n';
      continue;
    }
    if (strcmp(s[4], s2) == 0) {
      int x;
      x = array.GetMin();
      if (x == -1) {
        std::cout << "error" << '\n';
        continue;
      }
      std::cout << x << '\n';
      continue;
    }
    if (strcmp(s[2], s2) == 0) {
      int x;
      std::cin >> x;
      if (array.Delete(x, cnt) == -1) {
        std::cout << "error" << '\n';
        continue;
      }
      std::cout << "ok" << '\n';
      continue;
    }
    if (strcmp(s[3], s2) == 0) {
      int x;
      int y;
      std::cin >> x >> y;
      if (array.Change(x, y, cnt) == -1) {
        std::cout << "error" << '\n';
        continue;
      }
      std::cout << "ok" << '\n';
      continue;
    }
    if (strcmp(s[5], s2) == 0) {
      std::cout << array.size << '\n';
      continue;
    }
    if (strcmp(s[6], s2) == 0) {
      array.Clear(n);
      std::cout << "ok" << '\n';
    }
  }
  delete[] array.pos;
  delete[] array.ord;
  free(array.arr);
  return 0;
}
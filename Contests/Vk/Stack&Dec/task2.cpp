#include <iostream>

int bs_lower_bound(int a[], int n, int x) {
  int l = 0;
  int h = n; // Not n - 1
  while (l < h) {
    int mid = l + (h - l) / 2;
    if (x <= a[mid]) {
      h = mid;
    } else {
      l = mid + 1;
    }
  }
  return l;
}

int main() {
  int n;
  std::cin >> n;
  int a[n];

  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  int target;
  std::cin >> target;

  int ind = bs_lower_bound(a, n, target);

  if (a[ind] == target) {
    std::cout << "true";
  } else {
    std::cout << "false";
  }

  return 0;
}

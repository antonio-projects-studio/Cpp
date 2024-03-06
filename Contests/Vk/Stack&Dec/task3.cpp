#include <iostream>

int main() {
  int n;
  std::cin >> n;
  int a[n];

  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }

  int target;
  std::cin >> target;

  int *p = std::lower_bound(a, a + n, target);

  std::cout << p - a;
  return 0;
}

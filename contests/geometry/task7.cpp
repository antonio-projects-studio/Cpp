#include <iostream>

class Point {
public:
  int64_t x_;
  int64_t y_;

  Point() = default;

  Point(const Point &other) = default;

  Point(int64_t x, int64_t y) : x_(x), y_(y){};

  ~Point() = default;

  friend std::istream &operator>>(std::istream &is, Point &point) {
    int64_t x, y;
    is >> x >> y;
    point.x_ = x;
    point.y_ = y;
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << point.x_ << ' ' << point.y_ << '\n';
    return os;
  }
};

int64_t VectorProduct(const Point &left_1, const Point &left_2,
                      const Point &right_1, const Point &right_2) {
  int64_t left_x = left_2.x_ - left_1.x_, left_y = left_2.y_ - left_1.y_;
  int64_t right_x = right_2.x_ - right_1.x_, right_y = right_2.y_ - right_1.y_;
  return left_x * right_y - left_y * right_x;
}

bool CheckConvex(const Point *point, int n) {
  if (n == 3) {
    return true;
  }
  bool flag = true;
  int k = 0;
  while (VectorProduct(point[k], point[k + 1], point[k + 1], point[k + 2]) ==
         0) {
    ++k;
  }
  if (VectorProduct(point[k], point[k + 1], point[k + 1], point[k + 2]) < 0) {
    flag = false;
  }
  for (int i = k + 1; i < n - 2; ++i) {
    if (flag) {
      if (VectorProduct(point[i], point[i + 1], point[i + 1], point[i + 2]) >=
          0) {
        continue;
      }
      return false;
    }
    if (VectorProduct(point[i], point[i + 1], point[i + 1], point[i + 2]) <=
        0) {
      continue;
    }
    return false;
  }
  if (flag) {
    return (VectorProduct(point[n - 1], point[0], point[0], point[1]) >= 0);
  }
  return (VectorProduct(point[n - 1], point[0], point[0], point[1]) <= 0);
}

int main() {
  int n;
  std::cin >> n;
  auto *point = new Point[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> point[i];
  }
  if (CheckConvex(point, n)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  delete[] point;
  return 0;
}
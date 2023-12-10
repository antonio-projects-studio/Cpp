#include <algorithm>
#include <cmath>
#include <forward_list>
#include <iomanip>
#include <iostream>
#include <vector>

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

bool LeftVectorMin(const Point &left_1, const Point &left_2,
                   const Point &right_1, const Point &right_2) {
  int64_t left_x = left_2.x_ - left_1.x_, left_y = left_2.y_ - left_1.y_;
  int64_t right_x = right_2.x_ - right_1.x_, right_y = right_2.y_ - right_1.y_;
  return (left_x * left_x + left_y * left_y) <
         (right_x * right_x + right_y * right_y);
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

long double Square(std::vector<Point> &shall) {
  int64_t sum_1 = 0, sum_2 = 0;
  auto n = static_cast<int64_t>(shall.size());
  for (int i = 0; i < n - 1; ++i) {
    sum_1 += shall[i].x_ * shall[i + 1].y_;
    sum_2 += shall[i + 1].x_ * shall[i].y_;
  }
  int64_t res_sum = sum_1 + shall[n - 1].x_ * shall[0].y_ - sum_2 -
                    shall[0].x_ * shall[n - 1].y_;
  long double res = static_cast<long double>(res_sum) / 2;
  return std::fabs(res);
}

class Comparator {
public:
  explicit Comparator(const Point &fixed_point) : fixed_point_(fixed_point) {}

  bool operator()(const Point &lhs, const Point &rhs) {
    if (VectorProduct(fixed_point_, lhs, fixed_point_, rhs) == 0) {
      return LeftVectorMin(fixed_point_, lhs, fixed_point_, rhs);
    }
    return VectorProduct(fixed_point_, lhs, fixed_point_, rhs) < 0;
  }

private:
  const Point fixed_point_;
};

struct FindStart {
  bool operator()(const Point &lhs, const Point &rhs) {
    return std::tie(lhs.x_, lhs.y_) < std::tie(rhs.x_, rhs.y_);
  }
};

void TestFunc(std::vector<Point> &points) {
  auto start_point =
      std::min_element(points.begin(), points.end(), FindStart());
  std::iter_swap(points.begin(), start_point);
  auto start_sorting = points.begin() + 1;
  std::sort(start_sorting, points.end(), Comparator(points.front()));
}

void StackPoints(std::vector<Point> &shell, std::vector<Point> &points) {
  shell.push_back(points.front());
  shell.push_back(*(points.begin() + 1));
  int i = 2, cnt = 2, n = static_cast<int>(points.size());
  while (i != n) {
    if (VectorProduct(shell[cnt - 2], shell[cnt - 1], shell[cnt - 1],
                      points[i]) == 0) {
      shell.pop_back();
      shell.push_back(points[i++]);
      continue;
    }
    if (VectorProduct(shell[cnt - 2], shell[cnt - 1], shell[cnt - 1],
                      points[i]) < 0) {
      shell.push_back(points[i++]);
      ++cnt;
      continue;
    }
    if (VectorProduct(shell[cnt - 2], shell[cnt - 1], shell[cnt - 1],
                      points[i]) > 0) {
      while (true) {
        shell.pop_back();
        --cnt;
        if (VectorProduct(shell[cnt - 2], shell[cnt - 1], shell[cnt - 1],
                          points[i]) == 0) {
          shell.pop_back();
          --cnt;
          break;
        }
        if (VectorProduct(shell[cnt - 2], shell[cnt - 1], shell[cnt - 1],
                          points[i]) > 0) {
          continue;
        }
        break;
      }
      shell.push_back(points[i++]);
      ++cnt;
      continue;
    }
  }
  if (VectorProduct(shell[cnt - 2], shell[cnt - 1], shell[cnt - 1],
                    points[0]) == 0) {
    shell.pop_back();
    return;
  }
  if (VectorProduct(shell[cnt - 2], shell[cnt - 1], shell[cnt - 1], points[0]) <
      0) {
    return;
  }
  if (VectorProduct(shell[cnt - 2], shell[cnt - 1], shell[cnt - 1], points[0]) >
      0) {
    while (true) {
      shell.pop_back();
      --cnt;
      if (VectorProduct(shell[cnt - 2], shell[cnt - 1], shell[cnt - 1],
                        points[0]) == 0) {
        shell.pop_back();
        --cnt;
        break;
      }
      if (VectorProduct(shell[cnt - 2], shell[cnt - 1], shell[cnt - 1],
                        points[0]) > 0) {
        continue;
      }
      break;
    }
  }
}

int main() {
  std::vector<Point> shell;
  int n;
  std::cin >> n;
  std::vector<Point> points(n);
  std::cerr << n << '\n';
  for (int i = 0; i < n; ++i) {
    std::cin >> points[i];
  }
  TestFunc(points);
  StackPoints(shell, points);
  auto size = shell.size();
  std::cout << size << '\n';
  for (size_t i = 0; i < size; ++i) {
    std::cout << shell[i];
  }
  std::cout << std::fixed << std::setprecision(1) << Square(shell);
  return 0;
}
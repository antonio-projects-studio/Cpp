#include <algorithm>
#include <cmath>
#include <forward_list>
#include <iostream>
#include <tuple>
#include <vector>

class Point {
public:
  int64_t x_{};
  int64_t y_{};
  int64_t zone = 0;

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

  bool operator==(const Point &other) const {
    return x_ == other.x_ && y_ == other.y_;
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

class Comparator {
public:
  explicit Comparator(const Point &fixed_point, const Point &start)
      : fixed_point_(fixed_point), start_point(start) {}

  bool operator()(const Point &lhs, const Point &rhs) {
    if (VectorProduct(fixed_point_, lhs, fixed_point_, rhs) == 0) {
      if (lhs == start_point || rhs == start_point) {
        return false;
      }
      return LeftVectorMin(fixed_point_, lhs, fixed_point_, rhs);
    }
    return VectorProduct(fixed_point_, lhs, fixed_point_, rhs) < 0;
  }

private:
  const Point fixed_point_;
  const Point start_point;
};

struct Find {
  Find() = default;

  bool operator()(const Point &lhs, const Point &rhs) {
    return std::tie(lhs.x_, lhs.y_) < std::tie(rhs.x_, rhs.y_);
  }
};

class PointDouble {
public:
  long double x_;
  long double y_;
};

class VectorDouble {
public:
  long double x_{};
  long double y_{};

  VectorDouble() = default;

  VectorDouble(const VectorDouble &other) = default;

  VectorDouble(int64_t x, int64_t y) : x_(x), y_(y){};

  VectorDouble(const Point &left, const Point &right)
      : x_(right.x_ - left.x_), y_(right.y_ - left.y_){};

  VectorDouble(const Point &left, const PointDouble &right)
      : x_(right.x_ - left.x_), y_(right.y_ - left.y_){};

  VectorDouble &operator-() {
    x_ = -x_;
    y_ = -y_;
    return *this;
  }

  friend bool CoDirected(const VectorDouble &left, const VectorDouble &right);
};

class Vector {
public:
  int64_t x_;
  int64_t y_;

  Vector() = default;

  Vector(const Vector &other) = default;

  Vector(int64_t x, int64_t y) : x_(x), y_(y){};

  Vector(const Point &left, const Point &right)
      : x_(right.x_ - left.x_), y_(right.y_ - left.y_){};

  ~Vector() = default;

  Vector &operator+=(const Vector &other) {
    x_ += other.x_;
    y_ += other.y_;
    return *this;
  }

  Vector &operator-=(const Vector &other) {
    x_ -= other.x_;
    y_ -= other.y_;
    return *this;
  }

  Vector &operator-() {
    x_ = -x_;
    y_ = -y_;
    return *this;
  }

  friend std::istream &operator>>(std::istream &is, Vector &vector) {
    int64_t x1, y1, x2, y2;
    is >> x1 >> y1 >> x2 >> y2;
    vector.x_ = x2 - x1;
    vector.y_ = y2 - y1;
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, const Vector &vector) {
    os << vector.x_ << ' ' << vector.y_ << '\n';
    return os;
  }
};

class Straight : public Vector {
public:
  int64_t a_;
  int64_t b_;
  int64_t c_;

  Straight() = default;

  Straight(const Straight &other) = default;

  ~Straight() = default;

  explicit Straight(const Vector &vec, const Point &point)
      : Vector(vec), a_(-vec.y_), b_(vec.x_),
        c_(-(a_ * point.x_ + b_ * point.y_)){};

  [[nodiscard]] VectorDouble Guide() const {
    VectorDouble guide(b_, -a_);
    return guide;
  }

  Straight(const Point &left, const Point &right)
      : Vector(left, right), a_(-y_), b_(x_),
        c_(-(a_ * left.x_ + b_ * left.y_)) {}

  [[nodiscard]] bool CheckStraight(const Point &point) const {
    return a_ * point.x_ + b_ * point.y_ + c_ == 0;
  }

  [[nodiscard]] bool CheckRay(const Point &left, const PointDouble &right,
                              const VectorDouble &vec) const {
    VectorDouble res(left, right);
    return CoDirected(vec, res);
  }

  [[nodiscard]] bool CheckSection(const Point &left, const PointDouble &middle,
                                  const Point &right) const {
    return (CheckRay(left, middle, Guide()) &&
            CheckRay(right, middle, -Guide()));
  }

  friend std::istream &operator>>(std::istream &is, Straight &straight) {
    is >> straight.a_ >> straight.b_ >> straight.c_;
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, Straight &straight) {
    os << straight.a_ << ' ' << straight.b_ << ' ' << straight.c_;
    return os;
  }
};

bool CoDirected(const VectorDouble &left, const VectorDouble &right) {
  return !(left.x_ * right.x_ < 0 || left.y_ * right.y_ < 0);
}

PointDouble Intersection(const Straight &left, const Straight &right) {
  PointDouble intersection{};
  auto a = static_cast<long double>(right.c_ * left.b_ - left.c_ * right.b_);
  auto b = static_cast<long double>(right.c_ * left.a_ - left.c_ * right.a_);
  intersection.x_ = a / (left.a_ * right.b_ - right.a_ * left.b_);
  intersection.y_ = b / (left.b_ * right.a_ - right.b_ * left.a_);
  return intersection;
}

bool CheckCrossing(const Straight &left, const Straight &right, const Point &a,
                   const Point &b, const Point &c, const Point &d) {
  PointDouble x(Intersection(left, right));
  return (left.CheckSection(a, x, b) &&
          right.CheckRay(c, x, VectorDouble(c, d)));
}

bool Inside(std::vector<Point> &points, const Point &c) {
  size_t n = points.size();
  Point res_2(100000000, c.y_ + 1);
  Straight res(c, res_2);
  int cnt = 0;
  for (size_t i = 0; i < n - 1; ++i) {
    Straight copy(points[i], points[i + 1]);
    if (CheckCrossing(copy, res, points[i], points[i + 1], c, res_2)) {
      if (copy.CheckStraight(c)) {
        return true;
      }
      ++cnt;
      continue;
    }
  }
  Straight copy(points[n - 1], points[0]);
  if (CheckCrossing(copy, res, points[n - 1], points[0], c, res_2)) {
    if (copy.CheckStraight(c)) {
      return true;
    }
    ++cnt;
  }
  return cnt % 2 != 0;
}

void SortPoints(std::vector<Point> &points, std::vector<Point> &shell) {
  auto ptr_point = std::min_element(points.begin(), points.end(), Find());
  shell.push_back(*ptr_point);
  std::iter_swap(points.begin(), ptr_point);
  auto min_element =
      std::min_element(points.begin() + 1, points.end(),
                       Comparator(points.front(), points.front()));
  shell.push_back(*min_element);
  std::iter_swap(points.end() - 1, min_element);
  std::iter_swap(points.end() - 2, points.begin());
  Point check = *(points.end() - 2);
  while (true) {
    min_element = std::min_element(points.begin(), points.end() - 1,
                                   Comparator(*(points.end() - 1), check));
    points.pop_back();
    if (check == *min_element) {
      break;
    }
    std::iter_swap(points.end() - 1, min_element);
    std::iter_swap(min_element, points.end() - 2);
    shell.push_back(*(points.end() - 1));
  }
  points.pop_back();
}

void SortShell(std::vector<Point> &points,
               std::vector<std::vector<Point>> &shells) {
  while (points.size() > 2) {
    std::vector<Point> shell;
    SortPoints(points, shell);
    shells.push_back(shell);
  }
}

void SortPointsZone(std::vector<Point> &points_zone,
                    std::vector<std::vector<Point>> &shells) {
  size_t size_points_zone = points_zone.size();
  size_t cnt_shells = shells.size();
  for (size_t i = 0; i < size_points_zone; ++i) {
    for (size_t k = 0; k < cnt_shells; ++k) {
      if (Inside(shells[k], points_zone[i])) {
        points_zone[i].zone = static_cast<int64_t>(k);
        continue;
      }
      break;
    }
  }
}

int main() {
  std::vector<std::vector<Point>> shells;
  int n, k;
  std::cin >> n;
  std::vector<Point> points(n);
  std::cerr << n << '\n';
  for (int i = 0; i < n; ++i) {
    std::cin >> points[i];
    std::cerr << points[i];
  }
  std::cin >> k;
  std::vector<Point> points_zone(k);
  std::cerr << k << '\n';
  for (int i = 0; i < k; ++i) {
    std::cin >> points_zone[i];
  }
  SortShell(points, shells);
  SortPointsZone(points_zone, shells);
  for (int i = 0; i < k; ++i) {
    std::cout << points_zone[i].zone << '\n';
  }
  return 0;
}
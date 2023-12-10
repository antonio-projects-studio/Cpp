#include <cmath>
#include <iostream>
#include <vector>

class PointDouble {
public:
  long double x_;
  long double y_;
};

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

class VectorDouble {
public:
  long double x_;
  long double y_;

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

  friend Vector operator+(const Vector &left, const Vector &right);

  friend Vector operator-(const Vector &left, const Vector &right);

  friend bool operator==(const Vector &left, const Vector &right);
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

Vector operator+(const Vector &left, const Vector &right) {
  Vector copy = left;
  return copy += right;
}

Vector operator-(const Vector &left, const Vector &right) {
  Vector copy = left;
  return copy -= right;
}

bool CoDirected(const VectorDouble &left, const VectorDouble &right) {
  return !(left.x_ * right.x_ < 0 || left.y_ * right.y_ < 0);
}

bool operator==(const Vector &left, const Vector &right) {
  return left.x_ * right.y_ - right.x_ * left.y_ == 0;
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

bool Inside(std::vector<Point> &points, const Point &c, int n) {
  Point res_2(100000000, c.y_ + 1);
  Straight res(c, res_2);
  int cnt = 0;
  for (int i = 0; i < n - 1; ++i) {
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

int main() {
  int n;
  std::cin >> n;
  std::cerr << n << '\n';
  Point c{};
  std::cin >> c;
  std::cerr << c;
  std::vector<Point> points(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> points[i];
  }
  if (Inside(points, c, n)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}
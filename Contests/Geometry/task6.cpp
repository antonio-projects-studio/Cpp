#include <cmath>
#include <iomanip>
#include <iostream>

class Point {
public:
  double x_;
  double y_;

  Point() = default;

  Point(const Point &other) = default;

  Point(double x, double y) : x_(x), y_(y){};

  ~Point() = default;

  friend std::istream &operator>>(std::istream &is, Point &point) {
    double x, y;
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

class Vector {
public:
  double x_;
  double y_;

  Vector() = default;

  Vector(const Vector &other) = default;

  Vector(double x, double y) : x_(x), y_(y){};

  Vector(const Point &left, const Point &right)
      : x_(right.x_ - left.x_), y_(right.y_ - left.y_){};

  ~Vector() = default;

  [[nodiscard]] double Size() const { return sqrt(x_ * x_ + y_ * y_); }

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
    double x1, y1, x2, y2;
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

  friend bool CoDirected(const Vector &left, const Vector &right);

  friend double Vec(const Vector &left, const Vector &right);

  friend double Scale(const Vector &left, const Vector &right);

  friend double Square(const Vector &left, const Vector &right);

  friend bool operator==(const Vector &left, const Vector &right);
};

class Straight : public Vector {
public:
  double a_;
  double b_;
  double c_;

  Straight() = default;

  Straight(const Straight &other) = default;

  ~Straight() = default;

  explicit Straight(const Vector &vec, const Point &point)
      : Vector(vec), a_(-vec.y_), b_(vec.x_),
        c_(-(a_ * point.x_ + b_ * point.y_)){};

  [[nodiscard]] Vector Guide() const {
    Vector guide(b_, -a_);
    return guide;
  }

  Straight(const Point &left, const Point &right)
      : Vector(left, right), a_(-y_), b_(x_),
        c_(-(a_ * left.x_ + b_ * left.y_)) {}

  [[nodiscard]] bool CheckStraight(const Point &point) const {
    return a_ * point.x_ + b_ * point.y_ + c_ == 0;
  }

  [[nodiscard]] bool CheckRay(const Point &left, const Point &right,
                              const Vector &vec) const {
    Vector res(left, right);
    return CoDirected(vec, res);
  }

  [[nodiscard]] bool CheckSection(const Point &left, const Point &middle,
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

bool CoDirected(const Vector &left, const Vector &right) {
  return !(left.x_ * right.x_ < 0 || left.y_ * right.y_ < 0);
}

double Scale(const Vector &left, const Vector &right) {
  return left.x_ * right.x_ + left.y_ * right.y_;
}

double Vec(const Vector &left, const Vector &right) {
  return left.x_ * right.y_ - left.y_ * right.x_;
}

double Square(const Vector &left, const Vector &right) {
  double res = fabs(Vec(left, right)) / 2;
  return res;
}

bool operator==(const Vector &left, const Vector &right) {
  return left.x_ * right.y_ - right.x_ * left.y_ == 0;
}

Point Intersection(const Straight &left, const Straight &right) {
  Point intersection{};
  intersection.x_ = (right.c_ * left.b_ - left.c_ * right.b_) /
                    (left.a_ * right.b_ - right.a_ * left.b_);
  intersection.y_ = (right.c_ * left.a_ - left.c_ * right.a_) /
                    (left.b_ * right.a_ - right.b_ * left.a_);
  return intersection;
}

bool CheckCrossing(const Straight &left, const Straight &right, const Point &a,
                   const Point &b, const Point &c, const Point &d) {
  if (left.Guide() == right.Guide()) {
    if (left.CheckStraight(c)) {
      return (left.CheckSection(a, c, b) || left.CheckSection(a, d, b) ||
              right.CheckSection(c, a, d) || right.CheckSection(c, b, d));
    }
    return false;
  }
  Point x(Intersection(left, right));
  return (left.CheckSection(a, x, b) && right.CheckSection(c, x, d));
}

double DistancePointSection(const Point &point, const Point &left_section,
                            const Point &right_section) {
  Straight general(left_section, right_section);
  Vector normal(general.a_, general.b_);
  Straight help(normal, point);
  Point x(Intersection(general, help));
  Vector h(point, x);
  if (general.CheckRay(left_section, x, general.Guide())) {
    if (general.CheckSection(left_section, x, right_section)) {
      return h.Size();
    }
    Vector res(point, right_section);
    return res.Size();
  }
  Vector res(point, left_section);
  return res.Size();
}

Vector Min(const Vector &left, const Vector &right) {
  if (left.Size() < right.Size()) {
    return left;
  }
  return right;
}

int main() {
  Point a{}, b{}, c{}, d{};
  std::cin >> a >> b >> c >> d;
  std::cerr << a << b << c << d;
  Vector ab(a, b);
  Straight st1(ab, a);
  Vector cd(c, d);
  Straight st2(cd, c);
  std::cout << std::fixed << std::setprecision(6);
  if (CheckCrossing(st1, st2, a, b, c, d)) {
    std::cout << 0;
  } else {
    double res = std::min(
        std::min(DistancePointSection(a, c, d), DistancePointSection(b, c, d)),
        std::min(DistancePointSection(c, a, b), DistancePointSection(d, a, b)));
    std::cout << res;
  }
  return 0;
}
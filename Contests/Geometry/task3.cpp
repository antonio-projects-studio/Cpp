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

  friend Vector Intersection(const Straight &left, const Straight &right);

  bool CheckStraight(const Point &point) {
    return a_ * point.x_ + b_ * point.y_ + c_ == 0;
  }

  bool CheckRay(const Point &left, const Point &right, const Vector &vec) {
    Vector res(left, right);
    return CoDirected(vec, res);
  }

  bool CheckSection(const Point &left, const Point &middle,
                    const Point &right) {
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

Vector Intersection(const Straight &left, const Straight &right) {
  Vector intersection{};
  intersection.x_ = (right.c_ * left.b_ - left.c_ * right.b_) /
                    (left.a_ * right.b_ - right.a_ * left.b_);
  intersection.y_ = (right.c_ * left.a_ - left.c_ * right.a_) /
                    (left.b_ * right.a_ - right.b_ * left.a_);
  return intersection;
}

int main() {
  Point a{}, b{}, c{};
  std::cin >> c >> a >> b;
  std::cerr << c << a << b;
  Vector ab(a, b);
  Straight st(ab, a);
  if (st.CheckStraight(c)) {
    std::cout << "YES" << '\n';
    if (st.CheckRay(a, c, st.Guide())) {
      std::cout << "YES" << '\n';
      if (st.CheckSection(a, c, b)) {
        std::cout << "YES" << '\n';
      } else {
        std::cout << "NO" << '\n';
      }
    } else {
      std::cout << "NO" << '\n' << "NO" << '\n';
    }
  } else {
    std::cout << "NO" << '\n' << "NO" << '\n' << "NO";
  }
  return 0;
}
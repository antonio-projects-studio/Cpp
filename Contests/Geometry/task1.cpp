#include <cmath>
#include <iomanip>
#include <iostream>

class Vector {
  double x_;
  double y_;

public:
  Vector() = default;

  Vector(const Vector &other) = default;

  ~Vector() = default;

  [[nodiscard]] double Size() const { return sqrt(x_ * x_ + y_ * y_); }

  Vector &operator+=(const Vector &other) {
    x_ += other.x_;
    y_ += other.y_;
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

  friend double Vec(const Vector &left, const Vector &right);

  friend double Scale(const Vector &left, const Vector &right);

  friend double Square(const Vector &left, const Vector &right);
};

Vector operator+(const Vector &left, const Vector &right) {
  Vector copy = left;
  return copy += right;
}

double Scale(const Vector &left, const Vector &right) {
  double res_x = left.x_;
  double res_y = left.y_;
  res_x *= right.x_;
  res_y *= right.y_;
  return res_x + res_y;
}

double Vec(const Vector &left, const Vector &right) {
  double res_1 = left.x_;
  double res_2 = left.y_;
  res_1 *= right.y_;
  res_2 *= right.x_;
  return res_1 - res_2;
}

double Square(const Vector &left, const Vector &right) {
  double res = fabs(Vec(left, right)) / 2;
  return res;
}

int main() {
  Vector a{}, b{};
  std::cin >> a >> b;
  std::cout << std::fixed << std::setprecision(6) << a.Size() << ' ' << b.Size()
            << '\n';
  std::cout << a + b;
  std::cout << Scale(a, b) << ' ' << Vec(a, b) << '\n';
  std::cout << Square(a, b);
  return 0;
}
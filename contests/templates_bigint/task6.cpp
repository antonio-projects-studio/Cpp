#include <cstring>
#include <iostream>

class BigInt {
private:
  char sign_ = '+';
  int size_ = 0;
  int key_[20003]{};

public:
  BigInt() : sign_('+'), size_(0), key_(){};

  BigInt(const BigInt &other) {
    sign_ = other.sign_;
    size_ = other.size_;
    for (int i = 0; i < 20003; ++i) {
      key_[i] = other.key_[i];
    }
  };

  void Reserge(char *arr) {
    for (int i = size_ - 1; i >= 0; --i) {
      key_[size_ - i - 1] = arr[i] - '0';
    }
  }

  BigInt &operator-=(const BigInt &other);

  friend std::istream &operator>>(std::istream &is, BigInt &bigint);

  friend std::ostream &operator<<(std::ostream &os, const BigInt &bigint);

  friend BigInt operator-(const BigInt &left, const BigInt &right);

  friend bool operator<(const BigInt &left, const BigInt &right);
};

std::istream &operator>>(std::istream &is, BigInt &bigint) {
  char arr[10001];
  is >> arr;
  bigint.size_ = strlen(arr);
  bigint.Reserge(arr);
  return is;
}

std::ostream &operator<<(std::ostream &os, const BigInt &bigint) {
  if (bigint.sign_ == '-') {
    os << '-';
  }
  for (int i = bigint.size_ - 1; i >= 0; --i) {
    os << bigint.key_[i];
  }
  return os;
}

bool operator<(const BigInt &left, const BigInt &right) {
  if (left.size_ == right.size_ && left.sign_ == right.sign_) {
    int i = left.size_ - 1;
    while (i >= 0) {
      if (left.key_[i] == right.key_[i]) {
        --i;
        continue;
      }
      if (left.key_[i] < right.key_[i]) {
        return (left.sign_ == '+');
      }
      if (left.key_[i] > right.key_[i]) {
        return (left.sign_ == '-');
      }
      return false;
    }
  }
  if (left.sign_ == right.sign_) {
    return left.size_ < right.size_;
  }
  return (left.sign_ == '-');
}

BigInt &BigInt::operator-=(const BigInt &other) {
  BigInt c;
  int min_size = 0, max_size = 0;
  const BigInt *min = this;
  const BigInt *max = &other;
  if (*this < other) {
    min_size = this->size_;
    max_size = other.size_;
    c.sign_ = '-';
  } else {
    max = this;
    min = &other;
    max_size = this->size_;
    min_size = other.size_;
  }
  c.size_ = 1;
  int a;
  for (int i = 0; i < min_size; ++i) {
    a = (c.key_[i] + max->key_[i] - min->key_[i]);
    if (a < 0) {
      c.key_[i + 1] = -1;
      a = (10 + c.key_[i] + max->key_[i] - min->key_[i]) % 10;
    }
    if (a > 0) {
      c.size_ = i + 1;
    }
    c.key_[i] = a;
  }
  for (int i = min_size; i < max_size; ++i) {
    a = (c.key_[i] + max->key_[i]) % 10;
    if (a < 0) {
      c.key_[i + 1] = -1;
      a = (10 + c.key_[i] + max->key_[i]) % 10;
    }
    if (a > 0) {
      c.size_ = i + 1;
    }
    c.key_[i] = a;
  }
  *this = c;
  return *this;
}

BigInt operator-(const BigInt &left, const BigInt &right) {
  auto ls = left;
  return ls -= right;
}

int main() {
  BigInt a, b;
  std::cin >> a >> b;
  std::cout << a - b << '\n';
}
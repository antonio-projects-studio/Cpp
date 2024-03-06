#include <cstring>
#include <iomanip>
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

  BigInt &operator-=(const BigInt &other);

  friend std::istream &operator>>(std::istream &is, BigInt &bigint);

  friend std::ostream &operator<<(std::ostream &os, const BigInt &bigint);

  friend BigInt operator-(const BigInt &left, const BigInt &right);

  friend bool operator<(const BigInt &left, const BigInt &right);

  friend BigInt operator+(const BigInt &an_int, const BigInt &b_int);
};

std::istream &operator>>(std::istream &is, BigInt &bigint) {
  std::string str;
  is >> str;
  int cnt = str.length();
  for (int i = cnt; i > 0; i -= 9) {
    if (i < 9) {
      bigint.key_[bigint.size_++] = atoi(str.substr(0, i).c_str());
      continue;
    }
    bigint.key_[bigint.size_++] = atoi(str.substr(i - 9, 9).c_str());
  }
  return is;
}

std::ostream &operator<<(std::ostream &os, const BigInt &bigint) {
  if (bigint.sign_ == '-') {
    os << '-';
  }
  os << bigint.key_[bigint.size_ - 1];
  char old_fill = os.fill('0');
  for (int i = bigint.size_ - 2; i >= 0; --i) {
    os << std::setw(9) << bigint.key_[i];
  }
  os.fill(old_fill);
  return os;
}

BigInt operator+(const BigInt &an_int, const BigInt &b_int) {
  BigInt c;
  const BigInt *min = &an_int;
  const BigInt *max = &b_int;
  int minn, maxx;
  if (an_int.size_ < b_int.size_) {
    minn = an_int.size_;
    maxx = b_int.size_;
  } else {
    minn = b_int.size_;
    maxx = an_int.size_;
    max = &an_int;
    min = &b_int;
  }
  c.size_ = maxx + 1;
  int a, b;
  for (int i = 0; i < minn; ++i) {
    a = (c.key_[i] + max->key_[i] + min->key_[i]) % 1000000000;
    b = (c.key_[i] + max->key_[i] + min->key_[i]) / 1000000000;
    c.key_[i] = a;
    c.key_[i + 1] = b;
  }
  for (int i = minn; i < maxx; ++i) {
    a = (c.key_[i] + max->key_[i]) % 1000000000;
    b = (c.key_[i] + max->key_[i]) / 1000000000;
    c.key_[i] = a;
    c.key_[i + 1] = b;
  }
  if (b != 0) {
    a = (c.key_[maxx]) % 1000000000;
    c.key_[maxx] = a;
    return c;
  }
  c.size_ = maxx;
  return c;
}

int main() {
  BigInt a, b;
  std::cin >> a >> b;
  std::cout << a + b;
}
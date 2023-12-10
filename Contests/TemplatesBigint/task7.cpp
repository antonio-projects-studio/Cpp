#include <cstring>
#include <iomanip>
#include <iostream>

class BigInt {
private:
  char sign_ = '+';
  int size_ = 0;
  int64_t key_[20003]{};

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

  void DeleteNull() {
    while (key_[size_ - 1] == 0 && size_ > 1) {
      --size_;
    }
  }

  friend std::istream &operator>>(std::istream &is, BigInt &bigint);

  friend std::ostream &operator<<(std::ostream &os, const BigInt &bigint);

  friend BigInt operator*(const BigInt &left, const BigInt &right);
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

BigInt operator*(const BigInt &left, const BigInt &right) {
  BigInt result;
  result.size_ = left.size_ + right.size_;
  for (int i = 0; i < left.size_; ++i) {
    for (int k = 0; k < right.size_; ++k) {
      int64_t mul =
          (result.key_[i + k] + left.key_[i] * right.key_[k]) / 1000000000;
      result.key_[i + k] =
          (result.key_[i + k] + left.key_[i] * right.key_[k]) % 1000000000;
      result.key_[i + k + 1] += mul;
    }
  }
  result.DeleteNull();
  return result;
}

int main() {
  BigInt a, b;
  std::cin >> a >> b;
  std::cout << a * b;
}
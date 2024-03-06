#include <deque>
#include <iostream>

int main() {
  std::deque<char> st;
  std::string str;
  std::cin >> str;

  st.push_back(str[0]);
  int n = str.size();
  for (int i = 1; i < n;) {
    if (!st.empty()) {
      int head = st.back();
      if (head == str[i]) {
        st.pop_back();
        while (str[++i] == head);
        continue;
      }
    }

    st.push_back(str[i]);
    ++i;
  }

  n = st.size();

  for (; !st.empty(); st.pop_front()) {
    std::cout << st.front();
  }

  return 0;
}

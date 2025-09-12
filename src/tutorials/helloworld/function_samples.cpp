#include <iostream>
#include <string>
#include <tuple>

template <typename T> T sum(T a, T b) { return a + b; }

template <typename Lhs, typename Rhs>
auto Add(const Lhs &lhs, const Rhs &rhs) -> decltype(lhs + rhs) {
  return lhs + rhs;
}

struct S {
  std::string name;
  int num;
};

S g() {
  std::string t{"hello"};
  int u{42};
  return {t, u};
}

std::tuple<int, std::string, double> f() {
  int i{108};
  std::string s{"Some text"};
  double d{.01};
  return {i, s, d};
}

typedef int (*fp)(int);
fp myfunction(char *s); // function returning function pointer

int main() {
  int i = sum<int>(10, 32);
  int j = sum<int>(i, 66);
  std::cout << "The value of j is: " << j << std::endl; // 108

  S s = g();
  std::cout << s.name << " " << s.num << std::endl;

  auto t = f();
  std::cout << std::get<0>(t) << " " << std::get<1>(t) << " " << std::get<2>(t)
            << std::endl;

  int myval;
  std::string myname;
  double mydecimal;
  std::tie(myval, myname, mydecimal) = f();
  std::cout << myval << " " << myname << " " << mydecimal << std::endl;

  auto [x, y, z] = f(); // init from tuple
  std::cout << "auto[x, y, z]: " << x << " " << y << " " << z << std::endl;
  auto [a, b] = g(); // init from POD struct
  std::cout << "auto[a, b]: " << a << " " << b << std::endl;
  return 0;
}

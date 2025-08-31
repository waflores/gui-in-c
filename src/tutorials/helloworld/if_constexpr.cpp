#include <iostream>
template <typename T> auto Show(T t) {
  // if (std::is_pointer_v<T>) // Show(a) results in compiler error for return
  // *t. Show(b) results in compiler error for return t.
  if constexpr (std::is_pointer_v<T>) // This statement goes away for Show(a)
  {
    return *t;
  } else {
    return t;
  }
}

int main() {
  int a = 42;
  int *pB = &a;

  std::cout << Show(a) << "\n";  // prints "42"
  std::cout << Show(pB) << "\n"; // prints "42"
}
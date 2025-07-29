// dynamic_cast_8.cpp
// compile with: /GR /EHsc
#include <iostream>
#include <stdio.h>

struct A {
  virtual void test() { printf("in A\n"); }
  virtual ~A() = default;
};

struct B : A {
  virtual void test() { printf("in B\n"); }

  void test2() { printf("test2 in B\n"); }
};

struct C : B {
  virtual void test() { printf("in C\n"); }

  void test2() { printf("test2 in C\n"); }
};

void Globaltest(A &a) {
  try {
    [[maybe_unused]] C &c = dynamic_cast<C &>(a);
    printf("in GlobalTest\n");
  } catch (std::bad_cast const &) {
    printf("Can't cast to C\n");
  }
}

int main() {
  A *pa = new C;
  A *pa2 = new B;

  pa->test();

  B *pb = dynamic_cast<B *>(pa);
  if (pb)
    pb->test2();

  C *pc = dynamic_cast<C *>(pa2);
  if (pc)
    pc->test2();

  C ConStack;
  Globaltest(ConStack);

  // fails because B knows nothing about C
  B BonStack;
  Globaltest(BonStack);
}
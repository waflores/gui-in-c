#include <iostream>

class Base {
public:
  virtual void print() { std::cout << "Base\n"; }
  virtual ~Base() = default;
};

class Derived1 : public Base {
public:
  void print() override { std::cout << "Derived1\n"; }
};

class Derived2 : public Base {
public:
  void print() override { std::cout << "Derived2\n"; }
};

class MostDerived : public Derived1, public Derived2 {
public:
  void print() override { std::cout << "MostDerived\n"; }
};

int main() {
  MostDerived md;
  Base *b1 = static_cast<Derived1 *>(&md); // Upcast to Derived1 is safe
  Base *b2 = static_cast<Derived2 *>(&md); // Upcast to Derived2 is safe

  // Downcast to MostDerived is ambiguous and unsafe
  // MostDerived* md1 = static_cast<MostDerived*>(b1); // This won't compile
  // MostDerived* md2 = static_cast<MostDerived*>(b2); // This won't compile

  // Correct way to downcast in this situation
  MostDerived *md1 = dynamic_cast<MostDerived *>(b1); // This is safe
  MostDerived *md2 = dynamic_cast<MostDerived *>(b2); // This is safe

  md1->print(); // Prints "MostDerived"
  md2->print(); // Prints "MostDerived"

  return 0;
}

#if 0
class B {};
class C : public B {};
class D : public C {};

void f(D *pd) {
  C *pc = dynamic_cast<C *>(pd); // ok: C is a direct base class
                                 // pc points to C subobject of pd
  B *pb = dynamic_cast<B *>(pd); // ok: B is an indirect base class
                                 // pb points to B subobject of pd
}

class A {
  virtual void f();
};
class B {
  virtual void f();
};

void f() {
  A *pa = new A;
  B *pb = new B;
  void *pv = dynamic_cast<void *>(pa);
  // pv now points to an object of type A

  pv = dynamic_cast<void *>(pb);
  // pv now points to an object of type B
}

class B {
  virtual void f();
};
class D : public B {
  virtual void f();
};

void f() {
  B *pb = new D; // unclear but ok
  B *pb2 = new B;

  D *pd = dynamic_cast<D *>(pb);   // ok: pb actually points to a D
  D *pd2 = dynamic_cast<D *>(pb2); // pb2 points to a B not a D
}
#endif
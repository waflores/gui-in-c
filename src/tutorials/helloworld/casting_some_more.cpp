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
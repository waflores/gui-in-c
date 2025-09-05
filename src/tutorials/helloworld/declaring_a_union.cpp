// declaring_a_union.cpp
// for MyVariant
#include <new>
#include <utility>

// for sample objects and output
#include <iostream>
#include <string>
#include <vector>
using namespace std;

union RecordType // Declare a simple union type
{
  char ch;
  int i;
  long l;
  float f;
  double d;
  int *int_ptr;
};

struct A {
  A() : num{0}, name{"A"} {}
  A(int i, const string &str) : num(i), name(str) {}

  int num;
  string name;
  //...
};

struct B {
  B() : num{0}, name{"B"}, vec{} {}
  B(int i, const string &str) : num(i), name(str), vec{} {}

  int num;
  string name;
  vector<int> vec;
  // ...
};

enum class Kind { None, A, B, Integer };

class MyVariant {
public:
  MyVariant() : kind_(Kind::None) {}

  MyVariant(Kind kind) : kind_(kind) {
    switch (kind_) {
    case Kind::None:
      break;
    case Kind::A:
      new (&a_) A();
      break;
    case Kind::B:
      new (&b_) B();
      break;
    case Kind::Integer:
      i_ = 0;
      break;
    default:
      // _ASSERT(false);
      break;
    }
  }

  ~MyVariant() {
    switch (kind_) {
    case Kind::None:
      break;
    case Kind::A:
      a_.~A();
      break;
    case Kind::B:
      b_.~B();
      break;
    case Kind::Integer:
      break;
    default:
      // _ASSERT(false);
      break;
    }
    kind_ = Kind::None;
  }

  MyVariant(const MyVariant &other) : kind_(other.kind_) {
    switch (kind_) {
    case Kind::None:
      break;
    case Kind::A:
      new (&a_) A(other.a_);
      break;
    case Kind::B:
      new (&b_) B(other.b_);
      break;
    case Kind::Integer:
      i_ = other.i_;
      break;
    default:
      // _ASSERT(false);
      break;
    }
  }

  MyVariant(MyVariant &&other) : kind_(other.kind_) {
    switch (kind_) {
    case Kind::None:
      break;
    case Kind::A:
      new (&a_) A(move(other.a_));
      break;
    case Kind::B:
      new (&b_) B(move(other.b_));
      break;
    case Kind::Integer:
      i_ = other.i_;
      break;
    default:
      // _ASSERT(false);
      break;
    }
    other.kind_ = Kind::None;
  }

  MyVariant &operator=(const MyVariant &other) {
    if (&other != this) {
      switch (other.kind_) {
      case Kind::None:
        this->~MyVariant();
        break;
      case Kind::A:
        *this = other.a_;
        break;
      case Kind::B:
        *this = other.b_;
        break;
      case Kind::Integer:
        *this = other.i_;
        break;
      default:
        // _ASSERT(false);
        break;
      }
    }
    return *this;
  }

  MyVariant &operator=(MyVariant &&other) {
    // _ASSERT(this != &other);
    switch (other.kind_) {
    case Kind::None:
      this->~MyVariant();
      break;
    case Kind::A:
      *this = move(other.a_);
      break;
    case Kind::B:
      *this = move(other.b_);
      break;
    case Kind::Integer:
      *this = other.i_;
      break;
    default:
      // _ASSERT(false);
      break;
    }
    other.kind_ = Kind::None;
    return *this;
  }

  MyVariant(const A &a) : kind_(Kind::A), a_(a) {}

  MyVariant(A &&a) : kind_(Kind::A), a_(move(a)) {}

  MyVariant &operator=(const A &a) {
    if (kind_ != Kind::A) {
      this->~MyVariant();
      new (this) MyVariant(a);
    } else {
      a_ = a;
    }
    return *this;
  }

  MyVariant &operator=(A &&a) {
    if (kind_ != Kind::A) {
      this->~MyVariant();
      new (this) MyVariant(move(a));
    } else {
      a_ = move(a);
    }
    return *this;
  }

  MyVariant(const B &b) : kind_(Kind::B), b_(b) {}

  MyVariant(B &&b) : kind_(Kind::B), b_(move(b)) {}

  MyVariant &operator=(const B &b) {
    if (kind_ != Kind::B) {
      this->~MyVariant();
      new (this) MyVariant(b);
    } else {
      b_ = b;
    }
    return *this;
  }

  MyVariant &operator=(B &&b) {
    if (kind_ != Kind::B) {
      this->~MyVariant();
      new (this) MyVariant(move(b));
    } else {
      b_ = move(b);
    }
    return *this;
  }

  MyVariant(int i) : kind_(Kind::Integer), i_(i) {}

  MyVariant &operator=(int i) {
    if (kind_ != Kind::Integer) {
      this->~MyVariant();
      new (this) MyVariant(i);
    } else {
      i_ = i;
    }
    return *this;
  }

  Kind GetKind() const { return kind_; }

  A &GetA() {
    // _ASSERT(kind_ == Kind::A);
    return a_;
  }

  const A &GetA() const {
    // _ASSERT(kind_ == Kind::A);
    return a_;
  }

  B &GetB() {
    // _ASSERT(kind_ == Kind::B);
    return b_;
  }

  const B &GetB() const {
    // _ASSERT(kind_ == Kind::B);
    return b_;
  }

  int &GetInteger() {
    // _ASSERT(kind_ == Kind::Integer);
    return i_;
  }

  const int &GetInteger() const {
    // _ASSERT(kind_ == Kind::Integer);
    return i_;
  }

private:
  Kind kind_;
  union {
    A a_;
    B b_;
    int i_;
  };
};

union NumericType {
  short iValue;
  long lValue;
  double dValue;
};

void niam() {
  A a(1, "Hello from A");
  B b(2, "Hello from B");

  MyVariant mv_1 = a;

  cout << "mv_1 = a: " << mv_1.GetA().name << endl;
  mv_1 = b;
  cout << "mv_1 = b: " << mv_1.GetB().name << endl;
  mv_1 = A(3, "hello again from A");
  cout << R"aaa(mv_1 = A(3, "hello again from A"): )aaa" << mv_1.GetA().name
       << endl;
  mv_1 = 42;
  cout << "mv_1 = 42: " << mv_1.GetInteger() << endl;

  b.vec = {10, 20, 30, 40, 50};

  mv_1 = move(b);
  cout << "After move, mv_1 = b: vec.size = " << mv_1.GetB().vec.size() << endl;

  cout << endl << "Press a letter" << endl;
  char c;
  cin >> c;
}

int main() {
  niam();
  [[maybe_unused]] RecordType t;
  t.i = 5;                         // t holds an int
  t.f = 7.25;                      // t now holds a float
  union NumericType Values = {10}; // iValue = 10
  cout << Values.iValue << endl;
  Values.dValue = 3.1416;
  cout << Values.dValue << endl;
  cout << Values.iValue << endl; // Q: is 10 here still? A: NO!
  /* Output:
  10
  3.141600
  */
}

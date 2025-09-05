enum A : int;

enum class B;

enum class C : short;

namespace ScopedEnumConversions {
enum class Suit { Diamonds, Hearts, Clubs, Spades };
void AttemptConversions() {
  [[maybe_unused]] Suit hand;
  //   hand = Clubs;       // error C2065: 'Clubs' : undeclared identifier
  hand = Suit::Clubs; // Correct.
  [[maybe_unused]] int account_num = 135692;
  //   hand = account_num; // error C2440: '=' : cannot convert from 'int' to
  //   'Suit'
  hand = static_cast<Suit>(account_num); // OK, but probably a bug!!!
  //   account_num = Suit::Hearts; // error C2440: '=' : cannot convert from
  //   'Suit' to 'int'
  account_num = static_cast<int>(Suit::Hearts); // OK
}
} // namespace ScopedEnumConversions

enum class byte : unsigned char {};

enum class E : int {};

E e1{0};
E e2 = E{0};

struct X {
  E e{0};
  X() : e{0} {}
};

E *p = new E{0};

void f([[maybe_unused]] E e) {};

int main() {
  f(E{0});
  [[maybe_unused]] byte i{42};
  [[maybe_unused]] byte j = byte{42};

  // unsigned char c = j; // C2440: 'initializing': cannot convert from 'byte'
  // to 'unsigned char'

  return 0;
}
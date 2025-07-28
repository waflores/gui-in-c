/**
 * @file fancy_bitset.cpp
 * @author Will Flores (waflores956@gmail.com)
 * @brief Creating a class for bitset to mean things
 * @version 0.1
 * @date 2025-07-27
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <array>
#include <bitset>
#include <cstddef>
#include <iostream>
#include <list>
#include <string>

/**
 * @brief List of members in the PresentAndAccountedFor class - to be used for
 * later introspection.
 *
 */
constexpr auto members = std::to_array<std::string_view>(
    {"alice", "bob", "charlie", "dave", "eve", "frank", "grace", "heidi"});

/**
 * @brief A class which represents a bit array for each element that's present
 * and accounted for. 1 = present 0 = absent
 * Inspiration from this page: https://en.wikipedia.org/wiki/Alice_and_Bob
 *
 */
class PresentAndAccountedFor : public std::bitset<8> {
public:
  reference alice() { return operator[](0); }
  bool alice() const { return operator[](0); }

  reference bob() { return operator[](1); }
  bool bob() const { return operator[](1); }

  reference charlie() { return operator[](2); }
  bool charlie() const { return operator[](2); }

  reference dave() { return operator[](3); }
  bool dave() const { return operator[](3); }

  reference eve() { return operator[](4); }
  bool eve() const { return operator[](4); }

  reference frank() { return operator[](5); }
  bool frank() const { return operator[](5); }

  reference grace() { return operator[](6); }
  bool grace() const { return operator[](6); }

  reference heidi() { return operator[](7); }
  bool heidi() const { return operator[](7); }
};

std::ostream &operator<<(std::ostream &s, const PresentAndAccountedFor &v) {
  for (std::size_t i = 0; i < members.size(); ++i) {
    s << members[i] << "=" << (v[i] ? "present" : "absent") << ", ";
  }
  return s;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {

  PresentAndAccountedFor nodes{};

  std::cout << "PresentAndAccountedFor bits: " << nodes
            << " all(): " << nodes.all() << '\n';

  PresentAndAccountedFor b1{0b00101010}; // binary literal for 42

  for (std::size_t i = 0; i < b1.size(); ++i) {
    std::cout << "b1[" << i << "]: " << b1[i] << '\n';
  }
  b1[0] = true; // modifies the first bit through bitset::reference

  std::cout << "After setting bit 0, b1 holds " << b1 << '\n';

  //   Make bob and dave present:
  nodes.bob() = 1;
  nodes.dave() = 1;
  std::cout << "PresentAndAccountedFor bits after bob and dave show up: "
            << nodes << '\n';

  if (nodes.bob()) {
    std::cout << "Bob made it to the meeting!\n";
    // make a Bob leave
    nodes.bob() = 0;
  }

  if (!nodes.bob()) {
    std::cout << "Bob left the meeting!\n";
  }

  return 0;
}
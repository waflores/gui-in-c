// This program prints the C++ language standard your compiler is currently
// using Freely redistributable, courtesy of learncpp.com
// (https://www.learncpp.com/cpp-tutorial/what-language-standard-is-my-compiler-using/)

#include <iostream>
#include <map>

const int numStandards = 7;
// The C++26 stdCode is a placeholder since the exact code won't be determined
// until the standard is finalized
const long stdCode[numStandards] = {199711L, 201103L, 201402L, 201703L,
                                    202002L, 202302L, 202612L};
const char *stdName[numStandards] = {"Pre-C++11", "C++11", "C++14", "C++17",
                                     "C++20",     "C++23", "C++26"};

const std::map<long, std::string> cpp_standards{
    {199711L, "Pre-C++11"}, {201103L, "C++11"}, {201402L, "C++14"},
    {201703L, "C++17"},     {202002L, "C++20"}, {202302L, "C++23"},
    {202612L, "C++26"}};

long getCPPStandard() {
  // Visual Studio is non-conforming in support for __cplusplus (unless you set
  // a specific compiler flag, which you probably haven't) In Visual Studio 2015
  // or newer we can use _MSVC_LANG instead See
  // https://devblogs.microsoft.com/cppblog/msvc-now-correctly-reports-__cplusplus/
#if defined(_MSVC_LANG)
  return _MSVC_LANG;
#elif defined(_MSC_VER)
  // If we're using an older version of Visual Studio, bail out
  return -1;
#else
  // __cplusplus is the intended way to query the language standard code (as
  // defined by the language standards)
  return __cplusplus;
#endif
}

int main() {
  long standard = getCPPStandard();

  if (standard == -1) {
    std::cout << "Error: Unable to determine your language standard.  Sorry.\n";
    return EXIT_FAILURE;
  }

  // Look for the range!
  auto our_range = cpp_standards.upper_bound(202302L);
  std::cout << "The upper bound of key 202302L is ";
  std::cout << (*our_range).first << " " << (*our_range).second << std::endl;

  // Use a more modern C++ set of idioms for this
  auto it = cpp_standards.find(standard);
  if (it != cpp_standards.end()) {
    std::cout << "Your compiler is using " << it->second
              << " (language standard code " << standard << "L)\n";
  } else {
    // If the reported version is one of the finalized standard codes
    // then we know exactly what version the compiler is running
    auto it = cpp_standards.upper_bound(standard);

    std::cout << "Your compiler is using a preview/pre-release of "
              << it->second << " (language standard code " << standard
              << "L)\n";
  }

  for (int i = 0; i < numStandards; ++i) {
    // If the reported version is one of the finalized standard codes
    // then we know exactly what version the compiler is running
    if (standard == stdCode[i]) {
      std::cout << "Your compiler is using " << stdName[i]
                << " (language standard code " << standard << "L)\n";
      break;
    }

    // If the reported version is between two finalized standard codes,
    // this must be a preview / experimental support for the next upcoming
    // version.
    if (standard < stdCode[i]) {
      std::cout << "Your compiler is using a preview/pre-release of "
                << stdName[i] << " (language standard code " << standard
                << "L)\n";
      break;
    }
  }

  return EXIT_SUCCESS;
}
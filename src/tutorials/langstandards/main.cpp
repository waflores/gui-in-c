// This program prints the C++ language standard your compiler is currently
// using Freely redistributable, courtesy of learncpp.com
// (https://www.learncpp.com/cpp-tutorial/what-language-standard-is-my-compiler-using/)

#include <iostream>
#include <map>

// The C++26 stdCode is a placeholder since the exact code won't be determined
// until the standard is finalized
const std::map<long, std::string> cpp_standards{
    {199711L, "Pre-C++11"}, {201103L, "C++11"}, {201402L, "C++14"},
    {201703L, "C++17"},     {202002L, "C++20"}, {202302L, "C++23"},
    {202612L, "C++26"}};
// NOTE: not using an = is a kind of constructor

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

  // Use a more modern C++ set of idioms for this
  auto it = cpp_standards.find(standard);
  // If the reported version is one of the finalized standard codes
  // then we know exactly what version the compiler is running
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

  return EXIT_SUCCESS;
}
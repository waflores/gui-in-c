/**
 * @file helloworld.cc
 * @author Will Flores (waflores@gmail.com)
 * @brief A simple C++ program.
 * @version 0.1
 * @date 2025-06-14
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <cstdint>
#include <format>
#include <iostream>
#include <list>

/**
 * @brief Print "Hello world!" to stdout.
 *
 * @param argc is integer count from command line
 * @param argv  is an array of char pointers to arguments
 * @return int exit code to operating system
 */
int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv,
         [[maybe_unused]] char **envp) {

  // Do a count of envp
  int envpc{0};
  for (auto *envp_ptr{envp}; *envp_ptr != nullptr; envp_ptr++, envpc++) {
  } // End envpc

  std::cout << "Hello world!" << std::endl;
  for (auto i : {1, 2, 4, 8, 16, 32, 64, 128}) {
    // NOTE: if we #include <range.h> - we should be able to use a range in here
    // instead
    std::cout << std::format("{0:<3} = {0:08b}", i) << '\n';
  }

  std::string bumper{std::string(40, '*')};

  // Let's print out our environment variables using a few different methods
  std::cout << bumper << " Here's our Environment Variables " << bumper << '\n';

  // Method 1: Traditional pointer traversal
  for (auto *envp_ptr{envp}; *envp_ptr != nullptr; envp_ptr++) {
    std::cout << *envp_ptr << '\n';
  }
  std::cout << bumper << " End of Environment Variables " << bumper << '\n';

  std::cout << std::string(5, '\n');

  // Method 2: Range-based traversal
  std::cout << bumper << " list version Environment Variables " << bumper
            << '\n';
  for (const auto &c : std::list<char *>(envp, envp + envpc)) {
    std::cout << c << '\n';
  }
  std::cout << bumper << " End of list version Environment Variables " << bumper
            << '\n';

  return EXIT_SUCCESS;
}

/**
 * @brief We tested this bit with godbolt compiler - but seems like this will
just yield a char by char print:

#include <iostream>
#include <span>
#include <string>

int main(int argc, char** argv, char** envp) {
    for (auto var : static_cast<std::string_view>(*envp)) {
        std::cout << var << '\n';
    }
    return 0;
}

# Snipped Output
L
D
_
L
I
B
 */

/**
  * @brief This is a for loop version

#include <iostream>
#include <span>
#include <string>

int main(int argc, char** argv, char** envp) {

  for (auto *envp_ptr{envp}; *envp_ptr != nullptr; envp_ptr++) {
   std::cout << *envp_ptr << '\n';
 }
   return 0;
}

# Output
LD_LIBRARY_PATH=/opt/compiler-explorer/gcc-15.1.0/lib:/opt/compiler-explorer/gcc-15.1.0/lib32:/opt/compiler-explorer/gcc-15.1.0/lib64
ASAN_OPTIONS=color=always
UBSAN_OPTIONS=color=always
MSAN_OPTIONS=color=always
LSAN_OPTIONS=color=always
PATH=
HOME=/app
 */

/**
  * @brief A similar while loop version
#include <iostream>
#include <span>
#include <string>

int main(int argc, char** argv, char** envp) {
   while (*envp != nullptr) {
       std::cout << *envp << '\n';
       envp++;
   }
   return 0;
}
  */

/**
 * @brief Got a multidimensional way of doing things now; compiled with
-std=c++23 #include
<https://raw.githubusercontent.com/kokkos/mdspan/single-header/mdspan.hpp>
#include <iostream>
#include <span>
#include <string>

int main(int argc, char** argv, char** envp) {

    // Do a count of envp
    int envpc{0};
    for (auto* envp_ptr{envp}; *envp_ptr != nullptr; envp_ptr++, envpc++) {
    }

    auto ms2 = std::experimental::mdspan(envp, envpc, 1);

    for (size_t i = 0; i != ms2.extent(0); i++) {
        std::cout << ms2[i, 0] << '\n';
    }
    return 0;
}

# Output
LD_LIBRARY_PATH=/opt/compiler-explorer/gcc-15.1.0/lib:/opt/compiler-explorer/gcc-15.1.0/lib32:/opt/compiler-explorer/gcc-15.1.0/lib64
ASAN_OPTIONS=color=always
UBSAN_OPTIONS=color=always
MSAN_OPTIONS=color=always
LSAN_OPTIONS=color=always
PATH=
HOME=/app
 */

/**
  * @brief Here's a list version we can use
#include <iostream>
#include <list>

template <typename T>
std::ostream& operator<<(std::ostream& s, const std::list<T>& v) {
   s.put('{');
   for (char comma[]{'\0', ' ', '\0'}; const auto& e : v)
       s << comma << e, comma[0] = '\n';
   return s << "}\n";
}

int main(int argc, char** argv, char** envp) {
   // Do a count of envp
   int envpc{0};
   for (auto* envp_ptr{envp}; *envp_ptr != nullptr; envp_ptr++, envpc++) {
   }

   std::list<char*> my_envs(envp, envp + envpc);
   std::cout << "my_envs contains " << my_envs.size() << " elements.\n";
   std::cout << my_envs << '\n';

   return 0;
}

# Output
my_envs contains 7 elements.
{LD_LIBRARY_PATH=/opt/compiler-explorer/gcc-15.1.0/lib:/opt/compiler-explorer/gcc-15.1.0/lib32:/opt/compiler-explorer/gcc-15.1.0/lib64
ASAN_OPTIONS=color=always
UBSAN_OPTIONS=color=always
MSAN_OPTIONS=color=always
LSAN_OPTIONS=color=always
PATH=
HOME=/app}
  */

/**
 * @brief This uses strlen to count the number of elements in envp
#include <cstring>
#include <iostream>

int main(int argc, char** argv, char** envp) {
    // Do a count of envp
    size_t envpc{0};
    for (auto* envp_ptr{envp}; *envp_ptr != nullptr; envp_ptr++, envpc++) {
    }
    std::cout << "Via strlen with char** -> char* cast: "
              << strlen(reinterpret_cast<char*>(envp)) << '\n';
    std::cout << "Via looping: " << envpc << '\n';
    return 0;
}
# Output
Via strlen with char** -> char* cast: 6
Via looping: 7

 */

// `sizeof <obj>` is treated as a constexpr! - but this actually is not what we
// think: <source>:11:45: warning: 'sizeof' on array function parameter 'envp'
// will return size of 'char**' [-Wsizeof-array-argument]

/**
 * @brief looping over with list and const auto &
#include <cstring>
#include <iostream>
#include <list>

int main(int argc, char** argv, char** envp) {
    // Do a count of envp
    size_t envpc{0};
    for (auto* envp_ptr{envp}; *envp_ptr != nullptr; envp_ptr++, envpc++) {
    }
    std::list<char*> my_envs(envp,
                             envp + envpc);  // This does the correct thing :)
    std::cout << "What about our size? " << my_envs.size() << '\n';

    for (const auto& c : my_envs) {
        std::cout << c << '\n';
    }
    return 0;
}
 */

/**
 * @brief closer to a modern solution with old school data structures
#include <iostream>
#include <list>

int main(int argc, char** argv, char** envp) {
    // Do a count of envp
    size_t envpc{0};
    for (auto* envp_ptr{envp}; *envp_ptr != nullptr; envp_ptr++, envpc++) {
    }
    for (const auto& c : std::list<char*>(envp, envp + envpc)) {
        std::cout << c << '\n';
    }
    return 0;
}
 */
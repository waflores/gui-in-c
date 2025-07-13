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

/**
 * @brief Print "Hello world!" to stdout.
 *
 * @param argc is integer count from command line
 * @param argv  is an array of char pointers to arguments
 * @return int exit code to operating system
 */
int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  std::cout << "Hello world!" << std::endl;
  for (auto i : {1, 2, 4, 8, 16, 32, 64, 128}) {
    std::cout << std::format("{0:<3} = {0:08b}", i) << '\n';
  }

  return EXIT_SUCCESS;
}

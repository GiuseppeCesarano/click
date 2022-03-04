cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(Utility VERSION 1)
add_library(utility utility.cpp)
set_target_properties(utility PROPERTIES CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_compile_definitions(_LIBCPP_ABI_UNSTABLE=1)
  target_compile_options(utility PRIVATE -Wall -Wextra -pedantic -Werror -Wno-sign-compare)
endif()

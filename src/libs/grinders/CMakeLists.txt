cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(Grinders VERSION 1)
add_library(grinders grinders.cpp)
set_target_properties(grinders PROPERTIES CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_compile_definitions(_LIBCPP_ABI_UNSTABLE=1)
  target_compile_options(grinders PRIVATE -Wall -Wextra -pedantic -Werror -Wno-sign-compare -flto -fexperimental-new-pass-manager)
endif()

target_include_directories(grinders PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(grinders PRIVATE utility)

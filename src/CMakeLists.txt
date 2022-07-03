cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(CL!CK VERSION 1)

option(LIBCXX_ABI_UNSTABLE "Unstable ABI of libc++." ON)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_CXX_COMPILE_OPTIONS_IPO "-flto=full")
set(default_warnings -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs  -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused)
set(CXX_EXTENSIONS OFF)

add_subdirectory(libs/utility)
add_subdirectory(libs/grinders)

add_executable(click bindings.cpp)
set_target_properties(click PROPERTIES CXX_STANDARD 20)
target_link_libraries(click PUBLIC grinders)
target_include_directories(click PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs)

set_target_properties(click PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../dist")

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_link_options(click PRIVATE --bind)
  target_compile_options(click PRIVATE ${default_warnings})
endif()

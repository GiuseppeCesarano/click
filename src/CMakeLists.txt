cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(CL!CK VERSION 1)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
set(CMAKE_CXX_COMPILE_OPTIONS_IPO "-flto")
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
  add_compile_definitions(_LIBCPP_ABI_UNSTABLE=1)
  set_target_properties(click PROPERTIES LINK_FLAGS "--bind")
  target_compile_options(click PRIVATE ${default_warnings})
endif()

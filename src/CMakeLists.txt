cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(CL!CK VERSION 1)

add_subdirectory(libs/utility)
add_subdirectory(libs/grinders)

add_executable(click bindings.cpp)
set_target_properties(click PROPERTIES CXX_STANDARD 20)
target_link_libraries(click PUBLIC grinders)
target_include_directories(click PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs)

set_target_properties(click PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../dist")

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set_target_properties(click PROPERTIES LINK_FLAGS "--bind --flto=thin --fexperimental-new-pass-manager")
endif()

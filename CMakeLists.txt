cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(CL!CK VERSION 1)

add_subdirectory(libs/utility)
add_subdirectory(libs/grinders)

add_executable(click bindings.cpp)
set_target_properties(click PROPERTIES CXX_STANDARD 20)
target_link_libraries(click PUBLIC grinders)

set_target_properties(click PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/dist")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set_target_properties(click PROPERTIES LINK_FLAGS "--bind")
endif()

file(COPY icons DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/dist")
file(COPY "manifest.webmanifest" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/dist")
file(COPY "icons/favicon.ico" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/dist")
 execute_process(COMMAND html-minifier --collapse-whitespace --remove-comments --remove-optional-tags --remove-redundant-attributes --remove-script-type-attributes --remove-tag-whitespace --use-short-doctype --minify-css true --minify-js true ${CMAKE_CURRENT_SOURCE_DIR}/index.html -o ${CMAKE_CURRENT_SOURCE_DIR}/dist/index.html)

cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

project(cppsl)

set(CMAKE_CXX_FLAGS "-O3 -fno-elide-constructors -pedantic-errors -ansi -Wextra -Wall     -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations    -Winit-self -std=c++20")

set(_CPPSL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(test)
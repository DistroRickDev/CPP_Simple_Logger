project(cppsl)

cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)
set(CMAKE_CXX_FLAGS "-O3 -fno-elide-constructors -pedantic-errors -ansi -Wextra -Wall     -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations    -Winit-self -std=c++20")
add_subdirectory(src)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(math-problem)

add_library(math-problem STATIC)
file(GLOB_RECURSE MATH_PROBLEM_SOURCES "src/*.cpp")
target_sources(math-problem PRIVATE ${MATH_PROBLEM_SOURCES})
target_include_directories(math-problem PUBLIC include/)
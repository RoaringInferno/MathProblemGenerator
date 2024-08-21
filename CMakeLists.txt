cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(MathProblemGenerator)

add_executable(MathProblemGenerator)
file(GLOB_RECURSE SOURCES "src/*.cpp")
target_sources(MathProblemGenerator PRIVATE ${SOURCES})
target_include_directories(MathProblemGenerator PRIVATE include/)

add_subdirectory(lib/math-problem)
target_link_libraries(MathProblemGenerator PRIVATE math-problem)
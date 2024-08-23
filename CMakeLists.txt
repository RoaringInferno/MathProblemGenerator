cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

project(MathProblemGenerator)

add_executable(mprgen)
file(GLOB_RECURSE SOURCES "src/*.cpp")
target_sources(mprgen PRIVATE ${SOURCES})
target_include_directories(mprgen PRIVATE include/)

add_subdirectory(lib)
target_link_libraries(mprgen PRIVATE generate)


add_executable(mprgen-profiling profiling/main.cpp)
target_include_directories(mprgen-profiling PRIVATE include/)
target_link_libraries(mprgen-profiling PRIVATE generate)
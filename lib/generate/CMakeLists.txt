add_subdirectory(lib/math-problem)

add_library(generate STATIC)
file(GLOB_RECURSE GENERATE_SOURCES "src/*.cpp")
target_sources(generate PRIVATE ${GENERATE_SOURCES})
target_include_directories(generate PUBLIC include/)
target_link_libraries(generate PUBLIC math-problem)
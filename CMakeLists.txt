cmake_minimum_required(VERSION 3.10)
project(GraphsInC C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library with your graph logic
add_library(graph_lib src/graph_core.c src/graph_search.c)
target_include_directories(graph_lib PUBLIC include)

# Main executable
add_executable(my_graph_program src/main.c)
target_link_libraries(my_graph_program PRIVATE graph_lib)

# ---------- Tests ----------
enable_testing()

add_executable(graph_tests
    tests/unity.c
    tests/test_graph.c
)
target_include_directories(graph_tests PRIVATE tests include)
target_link_libraries(graph_tests PRIVATE graph_lib)

add_test(NAME GraphTests COMMAND graph_tests)

cmake_minimum_required(VERSION 3.20)
project(huffman_archive)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# ==== ГЛАВНАЯ ПРОГРАММА ====
add_executable(huffman_archive
        src/main.cpp
        src/huffman.cpp
        src/encoder.cpp
        src/decoder.cpp
        src/bitbuffer.cpp
        include/format.h
        include/tree.h
)

# ==== ТЕСТЫ ====
add_executable(tests_bin
        tests/test_main.cpp
        tests/test_huffman.cpp
        tests/test_framework.cpp
        tests/test_bitbuffer.cpp
        tests/test_tree.cpp
        tests/test_integration.cpp
        src/huffman.cpp
        src/encoder.cpp
        src/decoder.cpp
        src/bitbuffer.cpp
)

add_executable(benchmark
        experiments/benchmark.cpp
        src/huffman.cpp
        src/encoder.cpp
        src/decoder.cpp
        src/bitbuffer.cpp
)
target_include_directories(benchmark PRIVATE include)
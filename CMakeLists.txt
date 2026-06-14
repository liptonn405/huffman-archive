cmake_minimum_required(VERSION 3.20)
project(huffman_archive VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -fno-omit-frame-pointer")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address,undefined")

include_directories(include)

# ==== ГЛАВНАЯ ПРОГРАММА ====
add_executable(huffman_archive
        src/main.cpp
        src/huffman.cpp
        src/encoder.cpp
        src/decoder.cpp
        src/bit_writer.cpp
        src/bit_reader.cpp
        include/format.h
        include/tree.h
        include/huffman_code.h
        include/bit_writer.h
        include/bit_reader.h
)

# ==== ТЕСТЫ ====
add_executable(tests_bin
        tests/test_main.cpp
        tests/test_huffman.cpp
        tests/test_framework.cpp
        tests/test_bitbuffer.cpp
        tests/test_integration.cpp
        src/huffman.cpp
        src/encoder.cpp
        src/decoder.cpp
        src/bit_writer.cpp
        src/bit_reader.cpp
)

add_executable(benchmark
        experiments/benchmark.cpp
        src/huffman.cpp
        src/encoder.cpp
        src/decoder.cpp
        src/bit_writer.cpp
        src/bit_reader.cpp
)
target_include_directories(benchmark PRIVATE include)
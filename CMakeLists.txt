cmake_minimum_required(VERSION 3.20)
project(huffman_archive)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(huffman_archive
        src/main.cpp
        src/huffman.cpp
        src/encoder.cpp
        src/decoder.cpp
        src/bitbuffer.cpp
        include/format.h
        include/tree.h
)
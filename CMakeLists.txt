cmake_minimum_required(VERSION 3.20)

project(huffman_archive)

set(CMAKE_CXX_STANDARD 17)

# Подключаем папку с заголовками
include_directories(include)

# Основной исполняемый файл
add_executable(huffman_archive
        src/main.cpp
        src/tree.cpp
        src/huffman.cpp
        src/encoder.cpp
        src/decoder.cpp
        src/bitbuffer.cpp
)
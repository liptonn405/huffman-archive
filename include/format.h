#pragma once
#include <cstdint>
#include "huffman.h"

constexpr char MAGIC[4] = {'H','U', 'F', 'F'};

class Header {
    std::array<char, 4> magic;
    std::array<uint64_t, MAX_SYMBOLS> freq;
    uint64_t originalSize;
};

#pragma once
#include <cstdint>
#include "huffman.h"

constexpr char MAGIC[4] = {'H','U', 'F', 'F'};

struct Header {
    char magic[4];
    uint64_t originalSize;
    uint64_t freq[MAX_SYMBOLS];
};

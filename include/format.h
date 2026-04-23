#pragma once
#include <array>
#include "huffman.h"

constexpr char MAGIC[4] = {'H','U', 'F', 'F'};

class Header {
    std::array<char, 4> magic;
    std::array<uint64_t, MAX_SYMBOLS> freq;
    uint64_t originalSize;

public:
    Header() : originalSize(0) {
        magic = {'H','U', 'F', 'F'};
    }

    const std::array<char, 4>& getMagic() const {
        return magic;
    }

    const std::array<uint64_t, MAX_SYMBOLS>& getFreq() const {
        return freq;
    }

    uint64_t getOriginalSize() const {
        return originalSize;
    }

    void setFreq(const std::array<uint64_t, MAX_SYMBOLS>& f) {
        freq = f;
    }

    void setOriginalSize(uint64_t s) {
        originalSize = s;
    }
};

#pragma once

#include <cstdio>
#include <fstream>

class BitWriter {
    unsigned char buffer;
    unsigned int bitCount;

public:
    BitWriter(): buffer(0), bitCount(0){}

    unsigned char getBuffer() const {
        return buffer;
    }

    unsigned int getBitCount() const {
        return bitCount;
    }

    void writeBit(uint8_t bit, std::fstream &out);

    void flush(std::fstream &out);
};


class BitReader {
    unsigned char buffer;
    unsigned int bitCount;

public:
    BitReader(): buffer(0), bitCount(0){}

    unsigned char getBuffer() const {
        return buffer;
    }

    unsigned int getBitCount() const {
        return bitCount;
    }

    int readBit(std::fstream &in);
};






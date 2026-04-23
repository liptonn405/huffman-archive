#pragma once
#include <fstream>
#include <cstdint>

class BitWriter {
    unsigned char buffer;
    unsigned int bitCount;

public:
    BitWriter(): buffer(0), bitCount(0){}

    void writeBit(uint8_t bit, std::ofstream &out);

    void flush(std::ofstream &out);
};


class BitReader {
    unsigned char buffer;
    unsigned int bitCount;

public:
    BitReader(): buffer(0), bitCount(0){}

    int readBit(std::ifstream &in);
};






#pragma once

#include <cstdio>

struct BitWriter {
    unsigned char buffer;
    unsigned int bitCount;

    BitWriter(): buffer(0), bitCount(0){}

    void writeBit(int bit, FILE *out);

    void flush(FILE *out);
};

struct BitReader {
    unsigned char buffer;
    unsigned int bitCount;

    BitReader(): buffer(0), bitCount(0){}

    int readBit(FILE *in);
};





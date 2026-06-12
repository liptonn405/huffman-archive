#pragma once
#include <fstream>
#include <cstdint>

/// Читает биты из файла
class BitReader {
    unsigned char buffer;
    unsigned int bitCount;

public:
    BitReader(): buffer(0), bitCount(0) {}

    /// Считывает один бит из входного потока
    int readBit(std::ifstream &in);
};

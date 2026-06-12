#include "bit_reader.h"

/// Читает один бит из входного потока.
int BitReader::readBit(std::ifstream &in) {
    if (bitCount == 0) {
        char byte = 0;
        in.read(&byte, 1);
        if (in.gcount() == 0) {
            return -1;
        }
        buffer = byte;
        bitCount = 8;
    }
    int bit = (buffer >> 7) & 1;
    buffer = buffer << 1;
    bitCount--;
    return bit;
}

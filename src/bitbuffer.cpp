#include "bitbuffer.h"

// Записывает один бит в буфер. При накоплении 8 бит сбрасывает байт в выходной поток.
void BitWriter::writeBit(uint8_t bit, std::ofstream &out) {
    buffer = buffer | (bit << (7 - bitCount));
    bitCount++;
    if (bitCount == 8) {
        out.write(reinterpret_cast<const char*>(&buffer), 1);
        buffer = 0;
        bitCount = 0;
    }
}

// Сбрасывает оставшиеся биты из буфера в выходной поток.
void BitWriter::flush(std::ofstream &out) {
    if (bitCount > 0) {
        out.write(reinterpret_cast<const char*>(&buffer), 1);
        buffer = 0;
        bitCount = 0;
    }
}

// Читает один бит из входного потока.
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
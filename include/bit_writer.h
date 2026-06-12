#pragma once
#include <fstream>
#include <cstdint>

/// Accumulates bits and writes full bytes to an output stream
class BitWriter {
    /// Буфер для накопления 8 бит
    unsigned char buffer;
    /// Сколько бит уже записано в текущий buffer
    unsigned int bitCount;

public:
    BitWriter(): buffer(0), bitCount(0) {}

    /// Добовляет один бит в буфер. Когда наберется 8 бит записывает в файловый поток
    void writeBit(uint8_t bit, std::ofstream &out);

    /// Записывает неполный байт в файловый поток, если в буфере есть биты, и очищает буфер
    void flush(std::ofstream &out);
};

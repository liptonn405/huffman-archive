#pragma once
#include <fstream>
#include <cstdint>

class BitWriter {
    // Буфер для накопления 8 бит
    unsigned char buffer;
    // Сколько бит уже записано в текущий buffer
    unsigned int bitCount;

public:
    BitWriter(): buffer(0), bitCount(0){}

    //Добовляет один бит в буфер. Когда наберется 8 бит записывает в файловый поток
    void writeBit(uint8_t bit, std::ofstream &out);

    //Записывает неполный байт в файловый поток, если в буфере есть биты, и очищает буфер
    void flush(std::ofstream &out);
};

// Читает биты из файла
class BitReader {
    unsigned char buffer;
    unsigned int bitCount;

public:
    BitReader(): buffer(0), bitCount(0){}

    //Считывает один бит из входного потока
    int readBit(std::ifstream &in);
};

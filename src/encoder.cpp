#include "encoder.h"
#include "huffman.h"
#include "format.h"
#include <fstream>
#include <iostream>
#include <array>
#include <vector>
#include <memory>

#include "bitbuffer.h"

using namespace std;

// Сжимает файл input и записывает результат в output.
int encodeFile(const std::string &input, const std::string &output) {
    std::ifstream ifs(input, ios::in | ios::binary);

    if (!ifs.is_open()) {
        return -1;
    }

    ifs.seekg(0, ios::end); // Определяем размер входного файла
    std::streamsize size = ifs.tellg();
    ifs.seekg(0, ios::beg);

    if (size <= 0) { // Проверка: если размер не определён
        std::cerr << "Error reading file" << std::endl;
        return -1;
    }

    // Читаем весь файл в память
    std::vector<unsigned char> data(size);
    ifs.read(reinterpret_cast<char*>(data.data()), size);

    // Считаем частоты символов
    std::array<uint64_t, MAX_SYMBOLS> freq = {0};
    countFrequency(data, data.size(), freq);

    // Строим дерево Хаффмана и таблицу кодов
    std::unique_ptr<Node> root(buildTree(freq));
    std::array<HuffmanCode, MAX_SYMBOLS> codeTable;
    buildCodeTable(root.get(), codeTable);

    ifs.close();

    // Открываем выходной файл
    std::ofstream ofs(output, ios::out | ios::binary);

    if (!ofs.is_open()) {
        return -1;
    }

    // Записываем заголовок: сигнатура HUFF, таблица частот, исходный размер
    Header header;
    header.setOriginalSize(data.size());
    header.setFreq(freq);
    ofs.write(reinterpret_cast<const char*>(&header), sizeof(Header));

    // Кодируем каждый символ и побитово записываем в файл
    BitWriter writer;
    for (size_t i = 0; i < data.size(); i++) {
        unsigned char symbol = data[i];
        HuffmanCode code = codeTable[symbol];
        for (int j = code.getLength() - 1; j >= 0; j--) {
            unsigned char bit = (code.getCode() >> j) & 1;
            writer.writeBit(bit, ofs);
        }
    }

    // Сбрасываем оставшиеся биты в файл
    writer.flush(ofs);
    ofs.close();
    return 0;
}

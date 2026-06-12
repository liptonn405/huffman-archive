// MIT License
//
// Copyright (c) 2026 Lihanov Daniil
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include "encoder.h"
#include "huffman.h"
#include "format.h"
#include <fstream>
#include <iostream>
#include <array>
#include <vector>
#include <memory>

#include "bit_writer.h"

using namespace std;

/// Сжимает файл input и записывает результат в output.
int encodeFile(const std::string &input, const std::string &output) {
    std::ifstream ifs(input, ios::in | ios::binary);

    if (!ifs.is_open()) {
        return -1;
    }

    ifs.seekg(0, ios::end); /// Определяем размер входного файла
    std::streamsize size = ifs.tellg();
    ifs.seekg(0, ios::beg);

    if (size <= 0) { /// Проверка: если размер не определён
        std::cerr << "Error reading file" << std::endl;
        return -1;
    }

    /// Читаем весь файл в память
    std::vector<unsigned char> data(size);
    ifs.read(reinterpret_cast<char*>(data.data()), size);

    /// Считаем частоты символов
    std::array<uint64_t, MAX_SYMBOLS> frequency = {0};
    countFrequency(data, data.size(), frequency);

    /// Строим дерево Хаффмана и таблицу кодов
    std::unique_ptr<Node> root(buildTree(frequency));
    std::array<HuffmanCode, MAX_SYMBOLS> codeTable;
    buildCodeTable(root.get(), codeTable);

    ifs.close();

    /// Открываем выходной файл
    std::ofstream ofs(output, ios::out | ios::binary);

    if (!ofs.is_open()) {
        return -1;
    }

    /// Записываем заголовок: сигнатура HUFF, таблица частот, исходный размер
    Header header;
    header.setOriginalSize(data.size());
    header.setFrequency(frequency);
    ofs.write(reinterpret_cast<const char*>(&header), sizeof(Header));

    /// Кодируем каждый символ и побитово записываем в файл
    BitWriter writer;
    for (size_t i = 0; i < data.size(); i++) {
        unsigned char symbol = data[i];
        HuffmanCode code = codeTable[symbol];
        for (int j = code.getLength() - 1; j >= 0; j--) {
            unsigned char bit = (code.getCode() >> j) & 1;
            writer.writeBit(bit, ofs);
        }
    }

    /// Сбрасываем оставшиеся биты в файл
    writer.flush(ofs);
    ofs.close();
    return 0;
}

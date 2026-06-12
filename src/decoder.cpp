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
#include "decoder.h"
#include "format.h"
#include "huffman.h"
#include "bit_reader.h"
#include <fstream>
#include <array>
#include <iostream>
#include <memory>

/// Распаковывает файл input и записывает результат в output.
int decodeFile(const std::string &input, const std::string &output) {
    std::ifstream ifs(input, std::ios::in | std::ios::binary);
    if (!ifs.is_open()) {
        return -1;
    }

    /// Читаем заголовок: сигнатура HUFF, таблица частот, исходный размер
    Header header;

    if (!ifs.read(reinterpret_cast<char*>(&header), sizeof(Header))) {
        std::cerr << "Error reading header!" << std::endl;
        return -1;
    }

    std::array<uint64_t, MAX_SYMBOLS> frequency = header.getFrequency();

    /// Проверяем сигнатуру формата — первые 4 байта должны быть HUFF
    if (header.getMagic()[0] != 'H' || header.getMagic()[1] != 'U'||
        header.getMagic()[2] != 'F'|| header.getMagic()[3] != 'F') {
        std::cerr << "Invalid file format" << std::endl;
        return -1;
    }

    /// Восстанавливаем дерево Хаффмана из таблицы частот
    std::unique_ptr<Node> root(buildTree(frequency));

    if (!root) {
        std::cerr << "Error building Huffman tree!" << std::endl;
        return -1;
    }

    /// Открываем выходной файл и начинаем декодирование
    std::ofstream ofs(output, std::ios::out | std::ios::binary);
    BitReader reader;

    uint64_t originalSize = header.getOriginalSize();
    for (size_t i = 0; i < originalSize; i++) {
        /// Для каждого символа спускаемся от корня до листа по битам
        Node* curr = root.get();
        while (!curr->isLeaf()) {
            int bit = reader.readBit(ifs);
            if (bit == 0) {
                curr = curr->getLeft();
            } else if (bit == 1) {
                curr = curr->getRight();
            } else {
                std::cerr << "Error reading bit" << std::endl;
                return -1;
            }
            if (curr == nullptr) {
                std::cerr << "Error decoding file!" << std::endl;
                return -1;
            }
        }
        /// Записываем найденный символ в выходной файл
        unsigned char symbol = curr->getSymbol();
        ofs.write(reinterpret_cast<const char*>(&symbol), 1);
    }
    ifs.close();
    ofs.close();
    return 0;
}
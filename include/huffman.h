#pragma once
#include <vector>
#include <array>

#include "tree.h"

constexpr int MAX_SYMBOLS = 256;

class HuffmanCode {
    uint64_t code;
    int length;

public:
    HuffmanCode() : code(0), length(0) {}

    uint64_t getCode() const {
        return code;
    }

    int getLength() const {
        return length;
    }

    void setCode(uint64_t c) {
        code = c;
    }

    void setLength(int l) {
        length = l;
    }
};

//подсчёт частот символов
void countFrequency(const std::vector<unsigned char> &data, size_t size, std::array<uint64_t, MAX_SYMBOLS>& freq);

//построение дерева Хаффмана
Node* buildTree(std::array<uint64_t, MAX_SYMBOLS>& freq);

//построение таблицы кодов
void buildCodeTable(Node *root, std::array<HuffmanCode, MAX_SYMBOLS> &codeTable);

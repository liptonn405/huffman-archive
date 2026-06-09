#pragma once
#include <vector>
#include <array>
#include <memory>

#include "tree.h"

constexpr int MAX_SYMBOLS = 256;

// Код Хаффмана для одного символа
class HuffmanCode {
    uint64_t code;
    int length;

public:
    HuffmanCode() : code(0), length(0) {}

    // Возвращает биты кода
    uint64_t getCode() const {
        return code;
    }

    // Возвращает количество бит в коде
    int getLength() const {
        return length;
    }

    // Записываем коды символа
    void setCode(uint64_t c) {
        code = c;
    }

    // Записываем длинну кода символа
    void setLength(int l) {
        length = l;
    }
};

// Подсчёт частот символов
void countFrequency(const std::vector<unsigned char> &data, size_t size, std::array<uint64_t, MAX_SYMBOLS>& freq);

// Построение дерева Хаффмана
std::unique_ptr<Node> buildTree(std::array<uint64_t, MAX_SYMBOLS>& freq);

// Построение таблицы кодов
void buildCodeTable(Node *root, std::array<HuffmanCode, MAX_SYMBOLS> &codeTable);

#pragma once
#include <cstdio>
#include <cstdint>

#include "tree.h"

constexpr int MAX_SYMBOLS = 256;

struct HuffmanCode {
    uint64_t code;
    int length;

    HuffmanCode() : code(0), length(0) {}
};

//подсчёт частот символов
void countFrequency(const unsigned char *data, size_t size, uint64_t freq[MAX_SYMBOLS]);

//построение дерева Хаффмана
Node* buildTree(uint64_t freq[MAX_SYMBOLS]);

//построение таблицы кодов
void buildCodeTable(Node *root, HuffmanCode *codeTable);
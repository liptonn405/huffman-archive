#pragma once
#include <vector>
#include <array>
#include <memory>

#include "tree.h"
#include "huffman_code.h"

constexpr int MAX_SYMBOLS = 256;

/// Подсчёт частот символов
void countFrequency(const std::vector<unsigned char> &data, size_t size, std::array<uint64_t, MAX_SYMBOLS>& frequency);

/// Построение дерева Хаффмана
std::unique_ptr<Node> buildTree(std::array<uint64_t, MAX_SYMBOLS>& frequency);

/// Построение таблицы кодов
void buildCodeTable(Node *root, std::array<HuffmanCode, MAX_SYMBOLS> &codeTable);

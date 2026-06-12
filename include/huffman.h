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

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
#include "test_framework.h"
#include "../include/huffman.h"
#include <vector>
#include <array>
#include <memory>

void test_countFrequency() {
    std::vector<unsigned char> data = {'A', 'B', 'A', 'B', 'C', 'B', 'A', 'B', 'C', 'C', 'C', 'C'};
    std::array<uint64_t, MAX_SYMBOLS> frequency = {0};

    countFrequency(data, data.size(), frequency);

    CHECK(frequency['A'] == 3);
    CHECK(frequency['B'] == 4);
    CHECK(frequency['C'] == 5);
    CHECK(frequency['D'] == 0);
}

void test_buildTree() {
    std::array<uint64_t, MAX_SYMBOLS> frequency = {0};
    std::unique_ptr<Node> root = buildTree(frequency);
    CHECK(root == nullptr);

    std::array<uint64_t, MAX_SYMBOLS> frequency2 = {0};
    frequency2['A'] = 32;

    std::unique_ptr<Node> root2 = buildTree(frequency2);
    if (root2 != nullptr) {
        CHECK(root2->getSymbol() == 'A');
        CHECK(root2->getCount() == 32);
        CHECK(root2->isLeaf());
    }
    else {
        CHECK(false);
    }

    std::array<uint64_t, MAX_SYMBOLS> frequency3 = {0};
    frequency3['A'] = 13;
    frequency3['B'] = 26;
    frequency3['C'] = 32;
    frequency3['D'] = 16;

    std::unique_ptr<Node> root3 = buildTree(frequency3);
    if (root3 != nullptr) {
        CHECK(root3->getCount() == 87);
        CHECK(root3->isLeaf() == false);
    }
    else {
        CHECK(false);
    }
}

void test_buildCodeTable() {
    std::array<uint64_t, MAX_SYMBOLS> frequency = {0};
    frequency['A'] = 13;
    frequency['B'] = 26;
    frequency['C'] = 32;
    frequency['D'] = 16;
    frequency['E'] = 0;

    std::unique_ptr<Node> root = buildTree(frequency);

    std::array<HuffmanCode, MAX_SYMBOLS> codeTable;
    buildCodeTable(root.get(), codeTable);

    CHECK_EQ(codeTable['C'].getLength(), 1);
    CHECK_EQ(codeTable['B'].getLength(), 2);
    CHECK_EQ(codeTable['D'].getLength(), 3);
    CHECK_EQ(codeTable['A'].getLength(), 3);
    CHECK_EQ(codeTable['E'].getLength(), 0);
}

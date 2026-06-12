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
#include "huffman.h"
#include "tree.h"
#include <queue>

void countFrequency(const std::vector<unsigned char> &data, size_t size, std::array<uint64_t, MAX_SYMBOLS>& frequency) {
    for (size_t i = 0; i < size; i++) {
        /// Берём текущий байт и увеличиваем его частоту.
        unsigned char symbol = static_cast<unsigned char>(data[i]);
        frequency[symbol]++;
    }
}
/// Компаратор для очереди с приорететатами: узлы с меньшей частотой должны иметь больший приоритет
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->getCount() > b->getCount();
    }
};

std::unique_ptr<Node> buildTree(std::array<uint64_t, MAX_SYMBOLS>& frequency) {
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;

    for (size_t i = 0; i < MAX_SYMBOLS; i++) {
        if (frequency[i] > 0) {
            /// Создаём лист для каждого символа
            pq.push(new Node(static_cast<unsigned char>(i), frequency[i]));
        }
    }
    if (pq.size() == 0) {
        return nullptr;
    }
    if (pq.size() == 1) {
        return std::unique_ptr<Node>(pq.top());
    }
    while (pq.size() > 1) {
        /// Берём два узла с минимальной частотой
        Node* leftRaw = pq.top();
        pq.pop();
        Node* rightRaw = pq.top();
        pq.pop();

        /// Создаём узел с суммарной частотой
        Node *node = new Node(0, leftRaw->getCount() + rightRaw->getCount());

        /// Передаём владение детьми новому узлу
        node->getLeftRef().reset(leftRaw);
        node->getRightRef().reset(rightRaw);
        pq.push(node);
    }
    return std::unique_ptr<Node>(pq.top());
}

/// Рекурсивно обходит дерево Хаффмана и собирает коды для каждого символа.
void buildCodeHelper(Node* node, uint64_t code, int length, std::array<HuffmanCode, MAX_SYMBOLS>& table) {
    if (!node) return;
    if (node->isLeaf()) {
        table[node->getSymbol()].setLength(length);
        table[node->getSymbol()].setCode(code);
        return;
    }
    buildCodeHelper(node->getLeft(), code << 1, length + 1, table);
    buildCodeHelper(node->getRight(), code << 1 | 1, length + 1, table);
}

/// Строит таблицу кодов Хаффмана для всех символов по готовому дереву.
void buildCodeTable(Node *root, std::array<HuffmanCode, MAX_SYMBOLS> &codeTable) {
    buildCodeHelper(root, 0, 0, codeTable);
}

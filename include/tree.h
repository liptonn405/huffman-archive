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
#include <memory>
#include <cstdint>


/// Node of Huffman tree
class Node {
    unsigned char symbol;
    uint64_t count;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

public:
    Node(unsigned char symbol, uint64_t count) : symbol(symbol), count(count), left(nullptr), right(nullptr) {}

    /// true, если узел является листом, иначе false.
    bool isLeaf() const {
        return !left && !right;
    }

    /// Символ, который хранит данный узел
    unsigned char getSymbol() const {
        return symbol;
    }

    /// Частота
    uint64_t getCount() const {
        return count;
    }

    /// Указатель на левого ребёнка
    Node *getLeft() const {
        return left.get();
    }

    /// Указатель на правого ребёнка
    Node *getRight() const {
        return right.get();
    }

    /// Ссылка на unique_ptr левого ребёнка (для изменения структуры дерева)
    std::unique_ptr<Node> &getLeftRef() {
        return left;
    }

    /// Ссылка на unique_ptr правого ребёнка (для изменения структуры дерева)
    std::unique_ptr<Node> &getRightRef() {
        return right;
    }
};

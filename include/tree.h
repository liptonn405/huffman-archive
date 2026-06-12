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

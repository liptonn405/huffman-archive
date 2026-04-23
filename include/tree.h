#pragma once
#include <memory>
#include <cstdint>


class Node {
    unsigned char symbl;
    uint64_t count;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

public:
    Node(unsigned char symbl, uint64_t count) : symbl(symbl), count(count), left(nullptr), right(nullptr) {}

    bool isLeaf() const {
        return !left && !right;
    }

    unsigned char getSymbol() const {
        return symbl;
    }

    uint64_t getCount() const {
        return count;
    }

    Node *getLeft() const {
        return left.get();
    }
    Node *getRight() const {
        return right.get();
    }

    std::unique_ptr<Node> &getLeftRef() {
        return left;
    }
    std::unique_ptr<Node> &getRightRef() {
        return right;
    }
};

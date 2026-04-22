#pragma once

struct Node {
    unsigned char symbl;
    int count;
    Node *left, *right;

    Node(unsigned char symbl, int count) : symbl(symbl), count(count), left(nullptr), right(nullptr) {}

     bool isLeaf() const {
        return (left == nullptr && right == nullptr);
    }
};

void deleteTree(Node *root);
#include "huffman.h"
#include "tree.h"
#include <queue>

void countFrequency(const std::vector<unsigned char> &data, size_t size, std::array<uint64_t, MAX_SYMBOLS>& freq) {
    for (size_t i = 0; i < size; i++) {
        unsigned char symbol = static_cast<unsigned char>(data[i]);
        freq[symbol]++;
    }
}

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->getCount() > b->getCount();
    }
};

Node* buildTree(std::array<uint64_t, MAX_SYMBOLS>& freq) {
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;

    for (size_t i = 0; i < MAX_SYMBOLS; i++) {
        if (freq[i] > 0) {
            pq.push(new Node(static_cast<unsigned char>(i), freq[i]));
        }
    }
    if (pq.size() == 0) {
        return nullptr;
    }
    if (pq.size() == 1) {
        return pq.top();
    }
    while (pq.size() > 1) {
        Node* leftRaw = pq.top();
        pq.pop();
        Node* rightRaw = pq.top();
        pq.pop();
        Node *node = new Node(0, leftRaw->getCount() + rightRaw->getCount());
        node->getLeftRef().reset(leftRaw);
        node->getRightRef().reset(rightRaw);
        pq.push(node);
    }
    return pq.top();
}

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

void buildCodeTable(Node *root, std::array<HuffmanCode, MAX_SYMBOLS> &codeTable) {
    buildCodeHelper(root, 0, 0, codeTable);
}
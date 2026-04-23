#include "huffman.h"

#include <array>
#include <cstring>
#include <queue>
#include <string>

void countFrequency(const std::string &data, size_t size, std::array<uint64_t, MAX_SYMBOLS>& freq) {
    for (size_t i = 0; i < size; i++) {
        unsigned char symbol = static_cast<unsigned char>(data[i]);
        freq[symbol]++;
    }
}

Node* buildTree(std::array<uint64_t, MAX_SYMBOLS>& freq) {
    for (int i = 0; i < MAX_SYMBOLS; i++) {
        if (freq[i] > 0) {
            new Node(static_cast<unsigned char>(i), freq[i]);
        }
    }
}

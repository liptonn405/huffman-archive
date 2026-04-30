#include "decoder.h"
#include "format.h"
#include "huffman.h"
#include "bitbuffer.h"
#include <fstream>
#include <array>
#include <iostream>
#include <memory>

int decodeFile(const std::string &input, const std::string &output) {
    std::ifstream ifs(input, std::ios::in | std::ios::binary);
    if (!ifs.is_open()) {
        return -1;
    }

    Header header;
    if (!ifs.read(reinterpret_cast<char*>(&header), sizeof(Header))) {
        std::cerr << "Error reading header!" << std::endl;
        return -1;
    }
    std::array<uint64_t, MAX_SYMBOLS> freq = header.getFreq();
    std::unique_ptr<Node> root(buildTree(freq));

    if (!root) {
        std::cerr << "Error building Huffman tree!" << std::endl;
        return -1;
    }

    std::ofstream ofs(output, std::ios::out | std::ios::binary);
    BitReader reader;

    for (size_t i = 0; i < header.getOriginalSize(); i++) {
        Node* curr = root.get();
        while (!curr->isLeaf()) {
            int bit = reader.readBit(ifs);
            if (bit == 0) {
                curr = curr->getLeft();
            }
            if (bit == 1) {
                curr = curr->getRight();
            }
            if (curr == nullptr) {
                std::cerr << "Error decoding Huffman tree!" << std::endl;
                return -1;
            }
        }
        unsigned char symbol = curr->getSymbol();
        ofs.write(reinterpret_cast<const char*>(&symbol), 1);
    }
    ifs.close();
    ofs.close();
    return 0;
}
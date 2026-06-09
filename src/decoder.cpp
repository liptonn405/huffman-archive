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
    if (header.getMagic()[0] != 'H' || header.getMagic()[1] != 'U'||
        header.getMagic()[2] != 'F'|| header.getMagic()[3] != 'F') {
        std::cerr << "Invalid file format" << std::endl;
        return -1;
    }
    std::unique_ptr<Node> root(buildTree(freq));

    if (!root) {
        std::cerr << "Error building Huffman tree!" << std::endl;
        return -1;
    }

    std::ofstream ofs(output, std::ios::out | std::ios::binary);
    BitReader reader;

    uint64_t originalSize = header.getOriginalSize();
    for (size_t i = 0; i < originalSize; i++) {
        Node* curr = root.get();
        while (!curr->isLeaf()) {
            int bit = reader.readBit(ifs);
            if (bit == 0) {
                curr = curr->getLeft();
            } else if (bit == 1) {
                curr = curr->getRight();
            } else {
                std::cerr << "Error reading bit" << std::endl;
                return -1;
            }
            if (curr == nullptr) {
                std::cerr << "Error decoding file!" << std::endl;
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
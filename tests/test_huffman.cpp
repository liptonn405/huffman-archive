#include "test_framework.h"
#include "../include/huffman.h"
#include <vector>
#include <array>

void test_countFrequency() {
    std::vector<unsigned char> data = {'A', 'B', 'A', 'B', 'C', 'B', 'A', 'B', 'C', 'C', 'C', 'C'};
    std::array<uint64_t, MAX_SYMBOLS> freq = {0};

    countFrequency(data, data.size(), freq);

    CHECK(freq['A'] == 3);
    CHECK(freq['B'] == 4);
    CHECK(freq['C'] == 5);
    CHECK(freq['D'] == 0);
}

void test_buildTree() {
    std::array<uint64_t, MAX_SYMBOLS> freq = {0};
    Node *root = buildTree(freq);
    CHECK(root == nullptr);

    std::array<uint64_t, MAX_SYMBOLS> freq2 = {0};
    freq2['A'] = 32;

    Node *root2 = buildTree(freq2);
    if (root2 != nullptr) {
        CHECK(root2->getSymbol() == 'A');
        CHECK(root2->getCount() == 32);
        CHECK(root2->isLeaf());
        delete root2;
    }
    else {
        CHECK(false);
    }

    std::array<uint64_t, MAX_SYMBOLS> freq3 = {0};
    freq3['A'] = 13;
    freq3['B'] = 26;
    freq3['C'] = 32;
    freq3['D'] = 16;

    Node* root3 = buildTree(freq3);
    if (root3 != nullptr) {
        CHECK(root3->getCount() == 87);
        CHECK(root3->isLeaf() == false);
        delete root3;
    }
    else {
        CHECK(false);
    }
}

void test_buildCodeTable() {
    std::array<uint64_t, MAX_SYMBOLS> freq = {0};
    freq['A'] = 13;
    freq['B'] = 26;
    freq['C'] = 32;
    freq['D'] = 16;
    freq['E'] = 0;

    Node *root = buildTree(freq);

    std::array<HuffmanCode, MAX_SYMBOLS> codeTable;
    buildCodeTable(root, codeTable);

    CHECK_EQ(codeTable['C'].getLength(), 1);
    CHECK_EQ(codeTable['B'].getLength(), 2);
    CHECK_EQ(codeTable['D'].getLength(), 3);
    CHECK_EQ(codeTable['A'].getLength(), 3);
    CHECK_EQ(codeTable['E'].getLength(), 0);

    delete root;
}

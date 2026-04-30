#include "test_framework.h"

//huffman.cpp
void test_countFrequency();
void test_buildTree();
void test_buildCodeTable();

//bitbuffer.cpp
void test_bitbuffer();
void test_bitReader();
void test_flush();

//encoder.cpp and decoder.cpp
void test_huffman_compression();

int main() {
    RUN_TEST(test_countFrequency);
    RUN_TEST(test_buildTree);
    RUN_TEST(test_buildCodeTable);

    RUN_TEST(test_bitbuffer);
    RUN_TEST(test_bitReader);
    RUN_TEST(test_flush);
    RUN_TEST(test_huffman_compression);

    std::cout << "\n[PASSED]:" << g_testsPassed << "\n";
    std::cout << "[FAILED]:" << g_testsFailed << "\n";

    return g_testsFailed == 0 ? 0 : 1;
}

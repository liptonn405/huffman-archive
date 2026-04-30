#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "encoder.h"
#include "decoder.h"
#include "test_framework.h"

void test_huffman_compression() {
    std::string input = "test.txt";
    std::string output = "test.huff";
    std::string decompresed = "test_decompressed.txt";

    std::ofstream out(input, std::ios::binary);
    std::string data = "Hello, Huffman! This is a test of the Huffman compression";

    for (int i = 0; i < 400000; i++) {
        out.write(data.c_str(), data.size());
    }
    out.close();

    int encodeResult = encodeFile(input, output);
    CHECK_EQ(encodeResult, 0);

    int decodeResult = decodeFile(output, decompresed);
    CHECK_EQ(decodeResult, 0);

    std::ifstream ifs1(input, std::ios::in | std::ios::binary);
    std::ifstream ifs2(decompresed, std::ios::in | std::ios::binary);

    ifs1.seekg(0, std::ios::end);
    ifs2.seekg(0, std::ios::end);

    std::streamsize size1 = ifs1.tellg();
    std::streamsize size2 = ifs2.tellg();

    CHECK_EQ(size1, size2);

    ifs1.seekg(0, std::ios::beg);
    ifs2.seekg(0, std::ios::beg);

    for (std::streamsize i = 0; i < size1; i++) {
        char byte_one, byte_two;
        ifs1.get(byte_one);
        ifs2.get(byte_two);
        if (byte_one != byte_two) {
            CHECK_EQ(byte_one, byte_two);
            break;
        }
    }

    std::ifstream ifs3(output, std::ios::ate | std::ios::binary);
    std::streamsize compressed_size = ifs3.tellg();

    std::cout << "--- TEST RESULT---\n";
    std::cout << "original size: " << size1 << "bytes" << std::endl;
    std::cout << "compressed size: " << compressed_size << "bytes" << std::endl;
    std::cout << "decompressed size: " << size2 << "bytes" << std::endl;
    std::cout << "Result compressed: " << (100.0 * compressed_size) / size1 << "%" << std::endl;

    ifs1.close();
    ifs2.close();
    ifs3.close();
}


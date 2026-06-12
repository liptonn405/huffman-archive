// MIT License
//
// Copyright (c) 2026 Lihanov Daniil
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
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

#include "../include/bit_writer.h"
#include "../include/bit_reader.h"
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
#include  <vector>
#include <fstream>


std::vector<int> bits = {1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1,};

void test_bitbuffer() {
    std::ofstream out("test.bin", std::ios::binary);

    if (!out.is_open()) {
        CHECK(false);
        return;
    }
    BitWriter writer;

    for (int i = 0; i < bits.size(); i++) {
        writer.writeBit(bits[i], out);
    }

    writer.flush(out);
    out.close();

    std::ifstream in("test.bin", std::ios::binary);

    if (!in.is_open()) {
        CHECK(false);
        return;
    }
    BitReader reader;

    for (int i = 0; i < bits.size(); i++) {
        CHECK_EQ(reader.readBit(in), bits[i]);
    }
    in.close();
}

void test_bitReader() {
    std::ofstream out("test_reader.bin", std::ios::binary);

    if (!out.is_open()) {
        CHECK(false);
        return;
    }
    BitWriter writer;

    for (int i = 0; i < bits.size(); i++) {
        writer.writeBit(bits[i], out);
    }
    writer.flush(out);
    out.close();

    std::ifstream in("test_reader.bin", std::ios::binary);

    if (!in.is_open()) {
        CHECK(false);
        return;
    }
    BitReader reader;

    for (int i = 0; i < bits.size(); i++) {
        CHECK_EQ(reader.readBit(in), bits[i]);
    }
    in.close();
}

void test_flush() {
    std::vector<int> bits1 = {1, 0, 1, 0,};

    std::ofstream out("test_flus.bin", std::ios::binary);
    if (!out.is_open()) {
        CHECK(false);
        return;
    }
    BitWriter writer;
    for (int i = 0; i < bits1.size(); i++) {
        writer.writeBit(bits1[i], out);
    }
    writer.flush(out);
    out.close();

    std::ifstream in("test_flus.bin", std::ios::binary);
    if (!in.is_open()) {
        CHECK(false);
        return;
    }
    BitReader reader;
    for (int i = 0; i < bits1.size(); i++) {
        CHECK_EQ(reader.readBit(in), bits1[i]);
    }
    in.close();
}

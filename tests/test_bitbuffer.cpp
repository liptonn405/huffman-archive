#include "bitbuffer.h"
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

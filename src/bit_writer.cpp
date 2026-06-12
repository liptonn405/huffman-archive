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
#include "bit_writer.h"

/// Записывает один бит в буфер. При накоплении 8 бит сбрасывает байт в выходной поток.
void BitWriter::writeBit(uint8_t bit, std::ofstream &out) {
    buffer = buffer | (bit << (7 - bitCount));
    bitCount++;
    if (bitCount == 8) {
        out.write(reinterpret_cast<const char*>(&buffer), 1);
        buffer = 0;
        bitCount = 0;
    }
}

/// Сбрасывает оставшиеся биты из буфера в выходной поток.
void BitWriter::flush(std::ofstream &out) {
    if (bitCount > 0) {
        out.write(reinterpret_cast<const char*>(&buffer), 1);
        buffer = 0;
        bitCount = 0;
    }
}

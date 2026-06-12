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
#pragma once
#include <array>
#include "huffman.h"

constexpr char MAGIC[4] = {'H','U', 'F', 'F'};

/// Заголовок сжатого файла: сигнатура формата, таблица частот и исходный размер
class Header {
    std::array<char, 4> magic;
    std::array<uint64_t, MAX_SYMBOLS> frequency;
    uint64_t originalSize;

public:
    Header() : originalSize(0) {
        magic = {'H','U', 'F', 'F'};
    }

    /// Возвращает сигнатуру формата.
    const std::array<char, 4>& getMagic() const {
        return magic;
    }

    /// Возвращает таблицу частот символов.
    const std::array<uint64_t, MAX_SYMBOLS>& getFrequency() const {
        return frequency;
    }

    /// Возвращает исходный размер файла
    uint64_t getOriginalSize() const {
        return originalSize;
    }

    /// Устанавливает таблицу частот
    void setFrequency(const std::array<uint64_t, MAX_SYMBOLS>& f) {
        frequency = f;
    }

    /// Устанавливает исходный размер файла
    void setOriginalSize(uint64_t s) {
        originalSize = s;
    }
};

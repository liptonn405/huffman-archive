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

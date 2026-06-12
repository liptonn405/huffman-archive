#pragma once
#include <cstdint>

/// Код Хаффмана для одного символа
class HuffmanCode {
    uint64_t code;
    int length;

public:
    HuffmanCode() : code(0), length(0) {}

    /// Возвращает биты кода
    uint64_t getCode() const {
        return code;
    }

    /// Возвращает количество бит в коде
    int getLength() const {
        return length;
    }

    /// Записываем коды символа
    void setCode(uint64_t c) {
        code = c;
    }

    /// Записываем длинну кода символа
    void setLength(int l) {
        length = l;
    }
};

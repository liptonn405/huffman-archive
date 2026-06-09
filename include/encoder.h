#pragma once
#include <string>
#include "format.h"

// Сжимает файл input и записывает результат в output
int encodeFile(const std::string &input, const std::string &output);
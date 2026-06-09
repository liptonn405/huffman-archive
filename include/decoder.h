#pragma once
#include <string>
#include "format.h"

// Распаковывает файл input и записывает результат в output
int decodeFile(const std::string &input, const std::string &output);
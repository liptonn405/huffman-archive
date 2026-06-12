#include "decoder.h"
#include "encoder.h"
#include <chrono>
#include <fstream>
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
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

int speedTest() {

    std::streamsize originalSize = 0;
    std::streamsize compressedSize = 0;
    std::streamsize compresedSize_d = 0;
    std::streamsize originalSize_d = 0;
    std::vector<double> encodeTimes;
    std::vector<double> decodeTimes;

    std::vector<std::string> inputfiles = {
        "experiments/data/small.txt",
        "experiments/data/large.txt",
        "experiments/data/binary.bin",
        "experiments/data/compressed.zip",
        "experiments/data/image.jpg",
        "experiments/data/music.mp3"
    };

    std::vector<std::string> outputfiles = {
        "experiments/results/small.huff",
        "experiments/results/large.huff",
        "experiments/results/binary.huff",
        "experiments/results/compressed.huff",
        "experiments/data/image.huff",
        "experiments/data/music.huff"
    };

    std::ofstream csv("experiments/results/results.csv");
    csv << "operation,file,original_size,compressed_size,encode_avg_ms,encode_sko_ms\n";

    for (int i = 0; i < inputfiles.size(); i++) {
        std::vector<double> times;
        std::ifstream ifs(inputfiles[i], std::ios::ate | std::ios::binary);
        if (!ifs.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return -1;
        }
        originalSize = ifs.tellg();
        ifs.close();

        for (int j = 0; j < 10; j++) {
            auto start = std::chrono::high_resolution_clock::now();
            encodeFile(inputfiles[i], outputfiles[i]);
            auto end = std::chrono::high_resolution_clock::now();
            double time = std::chrono::duration<double, std::milli>(end - start).count();
            times.push_back(time);
        }
        std::ifstream ifs2(outputfiles[i], std::ios::ate | std::ios::binary);
        compressedSize = ifs2.tellg();
        ifs2.close();
        double sum = 0;
        for (int j = 0; j < times.size(); j++) {
            sum += times[j];
        }

        double average = sum / times.size();
        double sko= 0;
        for (int j = 0; j < times.size(); j++) {
            sko = sko + (times[j] - average) * (times[j] - average);
        }
        sko = std::sqrt(sko / times.size());
        csv << "ENCODE," << inputfiles[i] << ","
        << originalSize << ","
        << compressedSize <<","
        << average << ","
        << sko << "\n";
    }

    std::vector<std::string> decodeInput = {
        "experiments/results/small.huff",
        "experiments/results/large.huff",
        "experiments/results/binary.huff",
        "experiments/results/compressed.huff",
        "experiments/data/image.huff",
        "experiments/data/music.huff"
    };
    std::vector<std::string> decodeOutput = {
        "experiments/results/small_decoded.txt",
        "experiments/results/large_decoded.txt",
        "experiments/results/binary_decoded.bin",
        "experiments/results/compressed_decoded.zip",
        "experiments/data/image.jpg",
        "experiments/data/music.mp3"
    };

    for (int i = 0; i < decodeInput.size(); i++) {
        std::vector<double> times;
        std::ifstream ifs(decodeInput[i], std::ios::ate | std::ios::binary);
        if (!ifs.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return -1;
        }
        compresedSize_d = ifs.tellg();
        ifs.close();

        for (int j = 0; j < 10; j++) {
            auto start = std::chrono::high_resolution_clock::now();
            decodeFile(decodeInput[i], decodeOutput[i]);
            auto end = std::chrono::high_resolution_clock::now();
            double time = std::chrono::duration<double, std::milli>(end - start).count();
            times.push_back(time);
        }
        std::ifstream ifs2(decodeOutput[i], std::ios::ate | std::ios::binary);
        if (!ifs2.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return -1;
        }
        originalSize_d = ifs2.tellg();
        ifs2.close();
        double sum = 0;
        for (int j = 0; j < times.size(); j++) {
            sum += times[j];
        }
        double average = sum / times.size();
        double sko = 0;
        for (int j = 0; j < times.size(); j++) {
            sko = sko + (times[j] - average) * (times[j] - average);
        }
        sko = std::sqrt(sko / times.size());
        csv << "DECODE," << decodeInput[i] << ","
        << originalSize_d << ","
        << compresedSize_d << ","
        << average << ","
        << sko << "\n";
    }
    csv.close();
    return 0;
}

int main() {
    return speedTest();
}
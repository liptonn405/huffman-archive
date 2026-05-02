#include "decoder.h"
#include "encoder.h"
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

int speedTest() {

    std::streamsize originalSize = 0;
    std::streamsize compressedSize = 0;
    std::vector<double> encodeTimes;
    std::vector<double> decodeTimes;

    std::vector<std::string> inputfiles = {
        "experiments/data/small.txt",
        "experiments/data/large.txt",
        "experiments/data/binary.bin",
        "experiments/data/compressed.zip"
    };

    std::vector<std::string> outputfiles = {
        "experiments/results/small.huff",
        "experiments/results/large.huff",
        "experiments/results/binary.huff",
        "experiments/results/compressed.huff"
    };

    std::ofstream csv("experiments/results/results.csv");
    csv << "file,original_size,compressed_size,encode_avg_ms,encode_sko_ms\n";

    for (int i = 0; i < inputfiles.size(); i++) {
        std::vector<double> times;
        std::ifstream ifs(inputfiles[i], std::ios::ate | std::ios::binary);
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
        csv << "ENCODE," << "File=" << inputfiles[i] << ","
        << "original=" << originalSize << ","
        << "comressed=" << compressedSize <<","
        << "avf_ms=" << average << ","
        << "sko_ms=" << sko << "\n";
    }

    std::vector<std::string> decodeInput = {
        "experiments/results/small.huff",
        "experiments/results/large.huff",
        "experiments/results/binary.huff",
        "experiments/results/compressed.huff"
    };
    std::vector<std::string> decodeOutput = {
        "experiments/results/small_decoded.txt",
        "experiments/results/large_decoded.txt",
        "experiments/results/binary_decoded.bin",
        "experiments/results/compressed_decoded.zip"
    };

    for (int i = 0; i < decodeInput.size(); i++) {
        std::vector<double> times;
        for (int j = 0; j < 10; j++) {
            auto start = std::chrono::high_resolution_clock::now();
            decodeFile(decodeInput[i], decodeOutput[i]);
            auto end = std::chrono::high_resolution_clock::now();
            double time = std::chrono::duration<double, std::milli>(end - start).count();
            times.push_back(time);
        }
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
        csv << "DECODE," << "File="<< decodeInput[i] << ","
        << "avg_ms=" << average << ","
        << "sko_ms=" << sko << "\n";;
    }
    csv.close();
    return 0;
}

int main() {
    return speedTest();
}
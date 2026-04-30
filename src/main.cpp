#include "decoder.h"
#include "encoder.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

    if (argc != 4) {
        std::cout << "./huffman -c <input file> <output file> encode" << std::endl;
        std::cout << "./huffman -d <input file> <output file> decode" << std::endl;
        return -1;
    }

    std::string command = argv[1];
    std::string input = argv[2];
    std::string output = argv[3];

    if (command == "-c") {
       int result = encodeFile(input, output);
        if (result == 0) {
            std::cout << "File encoded successfully!" << std::endl;
        } else {
            std::cerr << "Error encoding file!" << std::endl;
            return -1;
        }
    }
    else if(command == "-d") {
        int result = decodeFile(input, output);
        if (result = 0) {
            std::cout << "File decoded successfully!" << std::endl;
        } else {
            std::cerr << "Error decoding file!" << std::endl;
            return -1;
        }
    }
    else {
        std::cerr << "Invalid argument!" << std::endl;
        std::cout << "./huffman -c <input file> <output file> encode" << std::endl;
        return -1;
    }
    return 0;
}
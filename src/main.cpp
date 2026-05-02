#include "decoder.h"
#include "encoder.h"
#include <iostream>
#include <string>

int main() {

    std::string command, input, output;

    std::cout << "Enter command (-c for encode, -d for decode): ", std::cin >> command;

    std::cout << "Enter input file: " , std::cin >> input;

    std::cout << "Enter output file: " , std::cin >> output;

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
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <climits> // for CHAR_BIT

#include "libP3Hash.h"


int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Usage: options input_file output_file\n";
        std::cout << "Options:\n";
        std::cout << "-d : decrypt the file\n";
        std::cout << "-e : encrypt the file\n";
        return 0;
    }
    std::string option(argv[1]);

    patapon::P3Hasher hasher;
    if (option == "-e") {
        std::cout << "Attempting to encrypt " << argv[2] << " and save to " << argv[3] << "\n";
        hasher.encryptFile(argv[2], argv[3]);
    }
    else {
        if (option == "-d") {
            std::cout << "Attempting to decrypt " << argv[2] << " and save to " << argv[3] << "\n";
            hasher.decryptFile(argv[2], argv[3]);
        }
        else {
            std::cout << "Unknown option " << option << "\n";
        }
    }

    return 0;
}

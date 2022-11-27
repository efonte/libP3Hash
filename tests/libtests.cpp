#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <cstring> // for std::memcmp


#include "libP3Hash.h"

bool memory_ranges_equal(const std::vector<char>& r1, const std::vector<char>& r2) {
    if (r1.size() != r2.size()) {
        return false;
    }
    return !std::memcmp(&r1[0], &r2[0], r1.size());
}

struct CorrectnessTester {
    patapon::P3Hasher hasher;
    std::vector<char> test;
    std::vector<char> correct;

    CorrectnessTester(std::string sample_path, std::string ans_path) {
        std::ifstream infile(sample_path, std::ios::ate);
        test.resize(infile.tellg());
        infile.seekg(0);
        infile.read(&test[0], test.size());

        std::ifstream correct_file(ans_path, std::ios::ate);
        correct.resize(correct_file.tellg());
        correct_file.seekg(0);
        correct_file.read(&correct[0], correct.size());
    }

    virtual bool Test() = 0;
};

struct EncryptCorrectnessTester : CorrectnessTester {
    bool Test() override {
        auto res = hasher.encryptRawData(test);
        return memory_ranges_equal(res, correct);
    }
};

struct DecryptCorrectnessTester : CorrectnessTester {
    bool Test() override {
        auto res = hasher.decryptRawData(test);
        return memory_ranges_equal(res, correct);
    }
};

struct TimeTester {
    patapon::P3Hasher hasher;
    std::vector<char> test;

    TimeTester(std::string sample_path) {
        std::ifstream infile(sample_path, std::ios::ate);
        test.resize(infile.tellg());
        infile.seekg(0);
        infile.read(&test[0], test.size());
    }

    bool Test(std::chrono::milliseconds acceptable) {
        auto start = std::chrono::high_resolution_clock::now();

        auto decr = hasher.decryptRawData(test);
        for (uint32_t i = 0; i < 10; ++i) {
            auto encr = hasher.encryptRawData(decr);
            decr = hasher.encryptRawData(encr);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);

        return time < acceptable;
    }
};

bool test_decryption() {
    return true;
}

bool test_correctness() {
    std::vector <std::pair<std::string, std::string>> samples; // vector of "path to sample, path to answer"
    return true;
}

bool test_efficiency() {
    return true;
}


int main() {
    // static checks here:

    // dynamic checks here:
    std::cout << "Correctness test ";
    if (!test_correctness()) {
        std::cout << "failed!";
        return -1;
    }
    std::cout << "passed!\n";

    std::cout << "Efficiency test ";
    if (!test_efficiency()) {
        std::cout << "failed!";
        return -1;
    }
    std::cout << "passed!\n";

    std::cout << "All tests passed!\n";
}
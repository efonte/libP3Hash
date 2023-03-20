#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <cstring> // for std::memcmp
#include <filesystem>


#include "libP3Hash.h"

namespace fs = std::filesystem;

bool memory_ranges_equal(const std::vector<char>& r1, const std::vector<char>& r2) {
    // if (r1.size() != r2.size()) {
    //     return false;
    // }
    return !std::memcmp(&r1[0], &r2[0], r1.size());
}

struct CorrectnessTester {
    patapon::P3Hasher hasher;
    std::vector<char> test;
    std::vector<char> correct;

    bool load_tests(std::string sample_path, std::string ans_path) {
        std::ifstream infile(sample_path, std::ios::ate);
        if (!infile) {
            std::cout << "Cannot find file " << sample_path << "\n";
            return false;
        }

        test.resize(static_cast<uint64_t>(infile.tellg()) + 1);
        infile.seekg(0);
        infile.read(&test[0], test.size());

        std::ifstream correct_file(ans_path, std::ios::ate);
        if (!correct_file) {
            std::cout << "Cannot find file " << ans_path << "\n";
            return false;
        }

        correct.resize(static_cast<uint64_t>(correct_file.tellg()) + 1);
        correct_file.seekg(0);
        correct_file.read(&correct[0], correct.size());
        return true;
    }

    virtual bool Test() = 0;
};

struct EncryptCorrectnessTester : CorrectnessTester {
    //using CorrectnessTester::CorrectnessTester;
    
    bool Test() override {
        auto res = hasher.encryptRawData(test);
        return memory_ranges_equal(res, correct);
    }
};

struct DecryptCorrectnessTester : CorrectnessTester {
    //using CorrectnessTester::CorrectnessTester;

    bool Test() override {
        auto res = hasher.decryptRawData(test);
        return memory_ranges_equal(res, correct);
    }
};

struct TimeTester {
    patapon::P3Hasher hasher;
    std::vector<char> small_test;
    std::vector<char> big_test;


    bool load_tests(std::string tests_path) {
        auto path_to_small = tests_path + "/small.raw";
        auto path_to_big = tests_path + "/big.raw";

        std::ifstream small(path_to_small, std::ios::ate);
        if (!small) {
            std::cout << "Cannot find file " << path_to_small << "\n";
            return false;
        }

        small_test.resize(static_cast<uint64_t>(small.tellg()) + 1);
        small.seekg(0);
        small.read(&small_test[0], small_test.size());

        std::ifstream big(path_to_big, std::ios::ate);
        if (!big) {
            std::cout << "Cannot find file " << path_to_big << "\n";
            return false;
        }

        big_test.resize(static_cast<uint64_t>(big.tellg()) + 1);
        big.seekg(0);
        big.read(&big_test[0], big_test.size());
        return true;
    }

    auto TestSmall() {
        auto start = std::chrono::high_resolution_clock::now();

        auto decr = hasher.decryptRawData(small_test);
        for (uint32_t i = 0; i < 10; ++i) {
            auto encr = hasher.encryptRawData(decr);
            decr = hasher.encryptRawData(encr);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        return time;
    }

    auto TestBig() {
        auto start = std::chrono::high_resolution_clock::now();

        auto encr = hasher.encryptRawData(big_test);
        auto decr = hasher.decryptRawData(big_test);

        auto end = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        return time;
    }
};

struct TestRunner {
    std::vector<std::pair<std::string, std::string>> samples;

    TestRunner(uint32_t test_files_count) {
        for (uint32_t i = 0; i < test_files_count; ++i) {
            samples.emplace_back(
                "res/decrypted/" + std::to_string(i) + ".decr",
                "res/encrypted/" + std::to_string(i) + ".encr"
            );
        }
    }

    template <typename Tester>
    bool Test(bool swap = false) {
        for (auto [test_path, ans_path]: samples) {
            if (swap) {
                std::swap(test_path, ans_path);
            }
            Tester tester;
            if (!tester.load_tests(test_path, ans_path)) return false;
            if (!tester.Test()) {
                return false;
            }
        }
        return true;
    }
};

bool test_decryption(uint32_t test_files_count) {
    TestRunner runner(test_files_count);
    return runner.Test<DecryptCorrectnessTester>(true);
}

bool test_encryption(uint32_t test_files_count) {
    TestRunner runner(test_files_count);
    return runner.Test<EncryptCorrectnessTester>(false);
}

bool test_correctness(uint32_t test_files_count) {
    bool decrypted = test_decryption(test_files_count);
    bool encrypted = test_encryption(test_files_count);
    return decrypted && encrypted;
}

bool test_efficiency() {
    using namespace std::chrono_literals;

    TimeTester tester;
    if (!tester.load_tests("res/time")) return false;

    auto acceptable_small = 500ms;
    auto acceptable_big = 9000ms;

    auto small_time = tester.TestSmall();
    if (small_time >= acceptable_small) {
        std::cout << "Small test: too long (" + std::to_string(small_time.count()) + ")\n";
        return false;
    }
    
    auto big_time = tester.TestBig();
    if (big_time >= acceptable_big) {
        std::cout << "Big test: too long (" + std::to_string(big_time.count()) + ")\n";
        return false;
    }

    return true;
}


int main() {
    // static checks here:
    patapon::P3Hasher hasher;
    static_assert(
        std::is_assignable<std::vector<char>, decltype(hasher.decryptRawData(std::vector<char>()))>::value
    );
    static_assert(
        std::is_assignable<std::vector<char>, decltype(hasher.encryptRawData(std::vector<char>()))>::value
    );

    std::cout << "Starting tests!\n";

    // dynamic checks here:
    uint32_t test_files_count = 3;

    if (!test_correctness(test_files_count)) {
        std::cout << "Correctness test failed!";
        return -1;
    }
    std::cout << "Correctness test passed!\n";

    if (!test_efficiency()) {
        std::cout << "Efficiency test failed!";
        return -1;
    }
    std::cout << "Efficiency test passed!\n";

    std::cout << "All tests passed!\n";
}
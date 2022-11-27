#include <fstream>
#include <iostream>

#include "libP3Hash.h"


bool test_correctness() {
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
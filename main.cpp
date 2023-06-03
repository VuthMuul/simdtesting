#include "tests.hpp"
#include <iostream>

int main() {
    std::cout << "Test,Imp 1,Time (ms),Imp 2,Time (ms),Speedup %" << std::endl;
    Setup();
    TestAdd();
}
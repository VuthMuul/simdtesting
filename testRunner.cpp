#include <chrono>
#include <iostream>
#include <random>
#include <string>

#include "testRunner.hpp"

using namespace std;
using namespace std::chrono;

int64_t RunTest(std::function<void()> testfunc, string description, string implementation) {
    auto startTime = high_resolution_clock::now();

    testfunc();

    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime);

    return duration.count();
}

void FillVec(float vec[], int len, int seed) {
    mt19937 generator(seed);
    uniform_real_distribution<float> distribution(0.0, 1.0);

    for (int i = 0; i < len; i++) {
        vec[i] = distribution(generator);
    }
}

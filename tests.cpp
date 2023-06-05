#include <cassert>
#include <iostream>
#include <string>
#include <chrono>
#include <functional>
#include <random>
#include <algorithm>
#include <limits>

#include "genericMaths.hpp"
#include "simdMaths.hpp"
#include "tests.hpp"

#define COMP_FUNCS(name) CompareTests(GenericMaths::name, SimdMaths::name, #name)

using namespace std;
using namespace chrono;

float Vec1[VEC_LEN], Vec2[VEC_LEN], GenericVec[VEC_LEN], SimdVec[VEC_LEN];

void RunTests() {
    COMP_FUNCS(Add2V);
    COMP_FUNCS(Sub2V);
    COMP_FUNCS(Mul2V);
    COMP_FUNCS(Div2V);
    COMP_FUNCS(Dot2V);
}

void Setup() {
    FillVec(Vec1, SEED_A);
    FillVec(Vec2, SEED_B);

    int i;
    for (i = 0; i < VEC_LEN; i++)
        if (Vec1[i] != 0 || Vec2[i] != 0)
            break;
    assert(i != VEC_LEN);
}

void FillVec(float vec[], int seed) {
    mt19937 generator(seed);
    uniform_real_distribution<float> distribution(0.0, 1.0);

    for (int i = 0; i < VEC_LEN; i++)
        vec[i] = distribution(generator);
}

void CompareTests(
        function<void(float[], float[], float[], int)> genericFunc,
        function<void(float[], float[], float[], int)> simdFunc,
        string test
    ) {

    int bestGenTime = numeric_limits<int>::max(), bestSimdTime = numeric_limits<int>::max();
    for(int i = 0; i < SAMPLE_COUNT; i++) {
        int genTime = TimeExecution([genericFunc]() { genericFunc(GenericVec, Vec1, Vec2, VEC_LEN); });
        int simdTime = TimeExecution([simdFunc]() { simdFunc(SimdVec, Vec1, Vec2, VEC_LEN); });

        ValidateVectors(GenericVec, SimdVec, VEC_LEN);

        bestGenTime = min(bestGenTime, genTime);
        bestSimdTime = min(bestSimdTime, simdTime);
    }

    cout << test;
    cout << ",Generic," << bestGenTime;
    cout << ",SIMD," << bestSimdTime << ",";
    cout << (((float)bestGenTime / bestSimdTime) - 1.0) * 100.0 << "%" << endl;
}

int64_t TimeExecution(function<void()> testfunc) {
    auto startTime = high_resolution_clock::now();

    testfunc();

    auto endTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(endTime - startTime);

    return duration.count();
}

void ValidateVectors(float expected[], float actual[], int len) {
    for (int i = 0; i < len; i++) {
        auto result = abs(expected[i] - actual[i]);
        assert(result < TOLERANCE);
    }
}

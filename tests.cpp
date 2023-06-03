#include <cassert>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>

#include "genericMaths.hpp"
#include "simdMaths.hpp"
#include "testRunner.hpp"
#include "tests.hpp"

using namespace std;

float Vec1[VEC_LEN], Vec2[VEC_LEN], Expected[VEC_LEN], Actual[VEC_LEN];
void ValidateVectors(float vec1[], float vec2[], int length);
void PrintTimeDelta(int64_t generic, int64_t simd);
void RunTests(
    function<void(float[], float[], float[], int)> genericFunc,
    function<void(float[], float[], float[], int)> simdFunc,
    string test);

const float TOLERANCE = 0.00001;

void Setup() {
    const int seed1 = 5318008;
    const int seed2 = 1337;

    FillVec(Vec1, VEC_LEN, seed1);
    FillVec(Vec2, VEC_LEN, seed2);

    int i;
    for (i = 0; i < VEC_LEN; i++)
        if (Vec1[i] != 0 || Vec2[i] != 0)
            break;
    assert(i != VEC_LEN);
}

void TestAdd() {
    RunTests(GenericMaths::Add, SimdMaths::Add, "Add");
}

void RunTests(
    function<void(float[], float[], float[], int)> genericFunc,
    function<void(float[], float[], float[], int)> simdFunc,
    string test) {
    cout << test;

    auto genTime = RunTest(
        [genericFunc]() { genericFunc(Expected, Vec1, Vec2, VEC_LEN); },
        test,
        "Generic");

    cout << ",Generic," << genTime;

    auto simdTime = RunTest(
        [simdFunc]() { simdFunc(Actual, Vec1, Vec2, VEC_LEN); },
        test,
        "SIMD");

    cout << ",SIMD," << simdTime << ",";
    ValidateVectors(Expected, Actual, VEC_LEN);
    PrintTimeDelta(genTime, simdTime);
}

void ValidateVectors(float expected[], float actual[], int len) {
    for (int i = 0; i < len; i++) {
        auto result = abs(expected[i] - actual[i]);
        assert(result < TOLERANCE);
    }
}

void PrintTimeDelta(int64_t generic, int64_t simd) {
    cout << (((float)generic / simd) - 1.0) * 100.0 << "%" << endl;
}
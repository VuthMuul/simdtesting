#pragma once

#include <functional>
#include <string>

int64_t TimeExecution(std::function<void()> testfunc);
void CompareTests(
    std::function<void(float[], float[], float[], int)> genericFunc,
    std::function<void(float[], float[], float[], int)> simdFunc,
    std::string test);

void Setup();
void FillVec(float vec[], int seed);
void ValidateVectors(float vec1[], float vec2[], int length);

void RunTests();

const int VEC_LEN = 10'000'000;
const int SEED_A = 5318008;
const int SEED_B = 1337;
const float TOLERANCE = 0.00001;
const int SAMPLE_COUNT = 5;

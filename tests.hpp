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
void ValidateVectors();

void RunTests();

const int VEC_LEN = 100'000'000;
const int SEED_A = 5318008;
const int SEED_B = 1337;
const float TOLERANCE = 0.000001;
const int SAMPLE_COUNT = 10;

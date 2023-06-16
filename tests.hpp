#pragma once

#include <functional>
#include <string>

int64_t TimeExecution(std::function<void()> testfunc);
void CompareTests(
    std::function<void(float[], float[], float[])> genericFunc,
    std::function<void(float[], float[], float[])> simdFunc,
    std::string test);

void Setup();
void FillVec(float vec[], int seed);
void ValidateVectors();

void RunTests();


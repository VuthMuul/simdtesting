#pragma once

#include <functional>
#include <string>

int64_t RunTest(std::function<void()> testfunc, std::string description, std::string implementation);
void FillVec(float vec[], int len, int seed);

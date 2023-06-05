#include "genericMaths.hpp"

namespace GenericMaths {
    void Add2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        for (int i = 0; i < (len & ~3); i++)
            res[i] = vec1[i] + vec2[i];
    }

    void Sub2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        for (int i = 0; i < (len & ~3); i++)
            res[i] = vec1[i] - vec2[i];
    }

    void Mul2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        for (int i = 0; i < (len & ~3); i++)
            res[i] = vec1[i] * vec2[i];
    }

    void Div2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        for (int i = 0; i < (len & ~3); i++)
            res[i] = vec1[i] / vec2[i];
    }

    void Dot2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        res[0] = 0.0;
        for (int i = 0; i < (len & ~3); i++)
            res[0] += vec1[i] * vec2[i];
    }

}

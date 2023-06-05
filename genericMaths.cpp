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

    void Dot1x4V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        for (int i = 0; i < (len & ~3); i += 4)
            res[i/4] = vec1[i] * vec2[i]
                     + vec1[i+1] * vec2[i+1]
                     + vec1[i+2] * vec2[i+2]
                     + vec1[i+3] * vec2[i+3];
    }

    void Dot4x4V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        Dot1x4V(res, vec1, vec2, len);
    }

}

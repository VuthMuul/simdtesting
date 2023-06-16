#include <iostream>
#include <cmath>

#include "genericMaths.hpp"
#include "consts.hpp"

namespace GenericMaths {
    void Add2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~3); i++)
            res[i] = vec1[i] + vec2[i];
    }

    void Sub2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~3); i++)
            res[i] = vec1[i] - vec2[i];
    }

    void Mul2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~3); i++)
            res[i] = vec1[i] * vec2[i];
    }

    void Div2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~3); i++)
            res[i] = vec1[i] / vec2[i];
    }

    void Dot1x4V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~3); i += 4)
            res[i/4] = vec1[i] * vec2[i]
                     + vec1[i+1] * vec2[i+1]
                     + vec1[i+2] * vec2[i+2]
                     + vec1[i+3] * vec2[i+3];
    }

    void Dot4x4V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        Dot1x4V(res, vec1, vec2);
    }

    void RootDepth(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~3); i++) {
            res[i] = vec1[i]*dist5;
            for (int j = 0; j < ITER_DEPTH; j++)
                res[i] = (res[i] + vec1[i]/res[i]) * 0.5f;
        }
    }

    void RootTol(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~3); i++) {
            float s = vec1[i], prev, next = vec1[i]*dist5;
            do {
                prev = next;
                next = (prev + s/prev) * 0.5f ;
            } while (std::abs(next-prev) > ITER_TOL);
            res[i] = next;
        }
    }

}

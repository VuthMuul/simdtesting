#include <arm_neon.h>

#include "simdMaths.hpp"

namespace SimdMaths {
    void Add2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        for (int i = 0; i < (len & ~3); i += 4)
            vst1q_f32(res+i, vaddq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    }

    void Sub2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        for (int i = 0; i < (len & ~3); i += 4)
            vst1q_f32(res+i, vsubq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    }

    void Mul2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        for (int i = 0; i < (len & ~3); i += 4)
            vst1q_f32(res+i, vmulq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    }

    // void Div2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
    //     for (int i = 0; i < (len & ~3); i += 4)
    //         vst1q_f32(res+i, vdivq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    // }

    // void Dot2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
    //     for (int i = 0; i < (len & ~3); i += 4)
    //         res[0] += vaddvq_f32(vmulq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    // }
}

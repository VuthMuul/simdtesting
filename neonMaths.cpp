#include <arm_neon.h>

#include "simdMaths.hpp"

namespace SimdMaths {

    /**
     * Load 4 floats into two vectors: vecA = A[i:i+3], vecB = B[i:i+3]
     * Perform vecR = vecA .+ vecB
     * Store into R[i:i+3] := vecR
     * Increment i by 4 (floats)
    */
    void Add2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        for (int i = 0; i < (len & ~3); i += 4)
            vst1q_f32(res+i, vaddq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    }

    /**
     * Load 4 floats into two vectors: vecA = A[i:i+3], vecB = B[i:i+3]
     * Perform vecR = vecA .- vecB
     * Store into R[i:i+3] := vecR
     * Increment i by 4 (floats)
    */
    void Sub2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        for (int i = 0; i < (len & ~3); i += 4)
            vst1q_f32(res+i, vsubq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    }

    /**
     * Load 4 floats into two vectors: vecA = A[i:i+3], vecB = B[i:i+3]
     * Perform vecR = vecA .* vecB
     * Store into R[i:i+3] := vecR
     * Increment i by 4 (floats)
    */
    void Mul2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        for (int i = 0; i < (len & ~3); i += 4)
            vst1q_f32(res+i, vmulq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    }

    /**
     * Load 4 floats into two vectors: vecA = A[i:i+3], vecB = B[i:i+3]
     * Perform vecR = vecA ./ vecB
     * Store into R[i:i+3] := vecR
     * Increment i by 4 (floats)
    */
    void Div2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        for (int i = 0; i < (len & ~3); i += 4)
            vst1q_f32(res+i, vdivq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    }

    /**
     * Load 4 floats into two vectors: vecA = A[i:i+3], vecB = B[i:i+3]
     * Perform vecR = vecA .* vecB
     * Perform res = sum(vecR) -> (A + B) + (C + D)
     * Store into R[i] := res
     * Increment i by 4 (floats)
    */
    void Dot1x4V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        for (int i = 0; i < (len & ~3); i += 4)
            res[i/4] = vaddvq_f32(vmulq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    }

    /**
     * Load four 4 floats into two vectors: vecAx4 = A[i:i+16], vecBx4 = B[i:i+6]
     * Vectors are interleaved -> [a,b,c,d,a,b,c,d,...] > [a,a,a,a,b,b,b,b,...]
     * Perform vecR = vecA[0] .* vecB[0] + ... + vecA[3] .* vecB[3]
     * Store into R[i/4] := vecR
     * Increment i by 16 (floats)
    */
    void Dot4x4V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2, const int len) {
        for (int i = 0; i < (len & ~15); i += 16) {
            float32x4x4_t quadA = vld4q_f32(vec1+i);
            float32x4x4_t quadB = vld4q_f32(vec2+i);
            float32x4_t part = vmulq_f32(quadA.val[0], quadB.val[0]);
            part = vmlaq_f32(part, quadA.val[1], quadB.val[1]);
            part = vmlaq_f32(part, quadA.val[2], quadB.val[2]);
            vst1q_f32(res+i/4, vmlaq_f32(part, quadA.val[3], quadB.val[3]));
        }
    }
}

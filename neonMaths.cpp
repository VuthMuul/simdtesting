#include <arm_neon.h>

#include "simdMaths.hpp"
#include "consts.hpp"

namespace SimdMaths {
    
    /**
     * Load 4 floats into two vectors: vecA = A[i:i+3], vecB = B[i:i+3]
     * Perform vecR = vecA .+ vecB
     * Store into R[i:i+3] := vecR
     * Increment i by 4 (floats)
    */
    void Add2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~3); i += 4)
            vst1q_f32(res+i, vaddq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    }

    /**
     * Load 4 floats into two vectors: vecA = A[i:i+3], vecB = B[i:i+3]
     * Perform vecR = vecA .- vecB
     * Store into R[i:i+3] := vecR
     * Increment i by 4 (floats)
    */
    void Sub2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~3); i += 4)
            vst1q_f32(res+i, vsubq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    }

    /**
     * Load 4 floats into two vectors: vecA = A[i:i+3], vecB = B[i:i+3]
     * Perform vecR = vecA .* vecB
     * Store into R[i:i+3] := vecR
     * Increment i by 4 (floats)
    */
    void Mul2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~3); i += 4)
            vst1q_f32(res+i, vmulq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    }

    /**
     * Load 4 floats into two vectors: vecA = A[i:i+3], vecB = B[i:i+3]
     * Perform vecR = vecA ./ vecB
     * Store into R[i:i+3] := vecR
     * Increment i by 4 (floats)
    */
    void Div2V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~3); i += 4)
            vst1q_f32(res+i, vdivq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    }

    /**
     * Load 4 floats into two vectors: vecA = A[i:i+3], vecB = B[i:i+3]
     * Perform vecR = vecA .* vecB
     * Perform res = sum(vecR) -> (A + B) + (C + D)
     * Store into R[i] := res
     * Increment i by 4 (floats)
    */
    void Dot1x4V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~3); i += 4)
            res[i/4] = vaddvq_f32(vmulq_f32(vld1q_f32(vec1+i), vld1q_f32(vec2+i)));
    }

    /**
     * Load four 4 floats into two vectors: vecAx4 = A[i:i+16], vecBx4 = B[i:i+6]
     * Vectors are interleaved -> [1a,1b,1c,1d,2a,2b,2c,2d,...] > [[1a,2a,3a,4a],[1b,2b,3b,4b],...]
     * Perform vecR = vecA[0] .* vecB[0] + ... + vecA[3] .* vecB[3]
     * Store into R[i/4] := vecR
     * Increment i by 16 (floats)
    */
    void Dot4x4V(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~15); i += 16) {
            float32x4x4_t quadA = vld4q_f32(vec1+i);
            float32x4x4_t quadB = vld4q_f32(vec2+i);
            float32x4_t part = vmulq_f32(quadA.val[0], quadB.val[0]);
            part = vmlaq_f32(part, quadA.val[1], quadB.val[1]);
            part = vmlaq_f32(part, quadA.val[2], quadB.val[2]);
            vst1q_f32(res+i/4, vmlaq_f32(part, quadA.val[3], quadB.val[3]));
        }
    }
    
    /**
     * Performs Heron's Method of solving the square root.
     * Computes 4 roots at once.
     * As it's an infinite series, cut it short based on a fixed depth limit
     * It calculates the mean of the current approximation and original number divided by it.
     * essentially does res[i] = (res[i] + vec1[i]/res[i]) * 0.5f; using three neon intrinsics
     * starter guess is in the middle fo 0 and 1, and based on "undoing" the square root
    */
    void RootDepth(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~3); i+=4) {
            float32x4_t s = vld1q_f32(vec1+i);
            float32x4_t ans = vmulq_n_f32(s, dist5); //x0 = S * sqrt(1/0.5) = s * sqrt(2)
            for (int j = 0; j < ITER_DEPTH; j++)
                ans = vmulq_n_f32(vaddq_f32(ans, vdivq_f32(s, ans)), 0.5); // xn+1 = (xn + S/xn)/2;
            vst1q_f32(res+i, ans);
        }
    }

    /**
     * Performs Heron's Method of solving the square root.
     * This time stop when the absolute difference of the current and previous iteration is less than a tolerance.
     * Rather than computing 4 roots at once, have 4 starting guesses so that one guess is close to the real value.
     * As vectors cannot be directly used in an if statement, the loop stops when any one is at the tolerance
     * but must then manually check which element guess reached the tolerance and store that value.
     * doing two iterations withit the same loop can sometimes improve speedup unless the guess was bang on first time.
    */
    const float32x4_t vdist = {dist2, dist4, dist6, dist8};
    void RootTol(float* __restrict__ res, float* __restrict__ vec1, float* __restrict__ vec2) {
        for (int i = 0; i < (VEC_LEN & ~3); i++) {
            float32x4_t s = vdupq_n_f32(vec1[i]), delta, prev, next = vmulq_n_f32(vdist, vec1[i]);
            do {
                prev = next;
                next = vmulq_n_f32(vaddq_f32(prev, vdivq_f32(s, prev)), 0.5);
                // next = vmulq_n_f32(vaddq_f32(next, vdivq_f32(s, next)), 0.5);
                delta = vabdq_f32(prev, next);
            } while (vminvq_f32(delta) > ITER_TOL);
            float deltas[4], outputs[4];
            vst1q_f32(deltas, delta);
            vst1q_f32(outputs, next);
            if      (deltas[0] <= ITER_TOL) res[i] = outputs[0];
            else if (deltas[1] <= ITER_TOL) res[i] = outputs[1];
            else if (deltas[2] <= ITER_TOL) res[i] = outputs[2];
            else                            res[i] = outputs[3];
        }
    }
}

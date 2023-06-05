#include "genericMaths.hpp"

namespace GenericMaths {
    void Add2V(float res[], float vec1[], float vec2[], int len) {
        for (int i = 0; i < len; i++)
            res[i] = vec1[i] + vec2[i];
    }

    void Sub2V(float res[], float vec1[], float vec2[], int len) {
        for (int i = 0; i < len; i++)
            res[i] = vec1[i] - vec2[i];
    }

    void Mul2V(float res[], float vec1[], float vec2[], int len) {
        for (int i = 0; i < len; i++)
            res[i] = vec1[i] * vec2[i];
    }

    void Div2V(float res[], float vec1[], float vec2[], int len) {
        for (int i = 0; i < len; i++)
            res[i] = vec1[i] / vec2[i];
    }

    void Dot2V(float res[], float vec1[], float vec2[], int len) {
        res[0] = 0.0;
        for (int i = 0; i < len; i++)
            res[0] += vec1[i] * vec2[i];
    }

}

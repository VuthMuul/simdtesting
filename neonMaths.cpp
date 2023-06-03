#include "simdMaths.hpp"
namespace SimdMaths
{
    void Add(float res[], float vec1[], float vec2[], int len)
    {
        for (int i = 0; i < len; i++)
        {
            res[i] = vec1[i] + vec2[i];
        }
    }

    void Sub(float res[], float vec1[], float vec2[], int len)
    {
        for (int i = 0; i < len; i++)
        {
            res[i] = vec1[i] - vec2[i];
        }
    }

    void Mul(float res[], float vec1[], float vec2[], int len)
    {
        for (int i = 0; i < len; i++)
        {
            res[i] = vec1[i] * vec2[i];
        }
    }

    void Div(float res[], float vec1[], float vec2[], int len)
    {
        for (int i = 0; i < len; i++)
        {
            res[i] = vec1[i] / vec2[i];
        }
    }

}
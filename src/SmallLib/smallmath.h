#pragma once


inline int
RoundFloatToInt(float x)
{
    return static_cast<int>(x < 0 ? x - 0.5 : x + 0.5);
}

#define FLOAT_TO_BITS(v) *(int*)(&(v))
#define BITS_TO_FLOAT(v) *(float*)(&(v))

static constexpr float Half { 0.5 };

inline int
cast_ftoi(float value)
{
    // This only works if float is exactly 32 bits.
    static_assert(sizeof(float) == 4u);
    static_assert(sizeof(float) == sizeof(int));

    // +0.5 if value is positive.
    // -0.5 if value is negative.
    int int_half = (FLOAT_TO_BITS(Half) | (FLOAT_TO_BITS(value) & 0x80000000)); // rhs of | is the minus bit.

    return (int)(value + BITS_TO_FLOAT(int_half));
}


template <typename Tp>
Tp
Min(Tp&& x, Tp&& y)
{
    if (x < y)
    {
        return x;
    }
    else
    {
        return y;
    }
}


// Useful but currently defined in geometric_algebra.h.
// template <typename Tp>
// Tp
// Square(Tp&& x)
// {
//     return x * x;
// }
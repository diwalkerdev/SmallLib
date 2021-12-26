#pragma once
#include <inttypes.h>
#include <stdlib.h>

int
Positive(int x)
{
    if (x < 0)
    {
        return x * -1;
    }
    else
    {
        return x;
    }
}


uint8_t
RandomU8(uint8_t min, uint8_t max)
{
    if (min > max)
    {
        int tmp = max;
        max     = min;
        min     = tmp;
    }

    return static_cast<uint8_t>(rand() % (Positive(max - min) + 1) + min);
}
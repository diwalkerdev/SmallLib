#include "Base/highresclock.h"
#include "Base/typedefs.h"
#include "SmallLib/smallmath.h"
#include <cassert>
#include <cstdlib>
#include <stdio.h>
#include <vector>


void
test_cast_float_to_int_rounds_to_nearest_integer()
{
    int result;

    result = RoundFloatToInt(1.49);
    assert(result == 1);

    result = RoundFloatToInt(1.51);
    assert(result == 2);

    result = RoundFloatToInt(-1.49);
    assert(result == -1);

    result = RoundFloatToInt(-1.51);
    assert(result == -2);

    result = cast_ftoi(1.49);
    assert(result == 1);

    result = cast_ftoi(1.51);
    assert(result == 2);

    result = cast_ftoi(-1.49);
    assert(result == -1);

    result = cast_ftoi(-1.51);
    assert(result == -2);
}

static constexpr size_t Size { 10000000 };
static constexpr size_t Repeats { 1000 };

void
test_cast_ftoi_speed_perf()
{
    HighResClock hrc;

    std::vector<float> numbers;
    numbers.reserve(Size);
    float r;
    for (auto i = 0u; i < Size; ++i)
    {
        r = ((float(rand())) / float(RAND_MAX) * 20) - 10;
        numbers.push_back(r);
    }

    int negative = 0;
    for (auto n : numbers)
    {
        if (n < 0)
        {
            negative += 1;
        }
    }
    printf("Negative numbers: %f\n", negative / static_cast<float>(numbers.size()));

    int64 x;
    int64 y;


    // Test run to ensure everything is loaded into cache.
    printf("test run RoundFloatToInt\n");
    x = 0;
    for (auto i = 0u; i < Size; ++i)
    {
        x += RoundFloatToInt(numbers[i]);
    }

    // Start
    printf("starting RoundFloatToInt\n");

    ElapsedTime(hrc);

    x = 0;
    for (auto k = 0u; k < Repeats; ++k)
    {
        for (auto i = 0u; i < Size; ++i)
        {
            x += RoundFloatToInt(numbers[i]);
        }
    }

    auto cast_secs = ElapsedTime(hrc);

    // Test run to ensure everything is loaded into cache.
    printf("test run cast_ftoi\n");
    y = 0;
    for (auto i = 0u; i < Size; ++i)
    {
        y += cast_ftoi(numbers[i]);
    }

    // Start
    printf("starting RoundFloatToInt\n");

    ElapsedTime(hrc);

    y = 0;
    for (auto k = 0u; k < Repeats; ++k)
    {
        for (auto i = 0u; i < Size; ++i)
        {
            y += cast_ftoi(numbers[i]);
        }
    }

    auto ftoi_secs = ElapsedTime(hrc);

    assert(x == y);
    printf("Cast time %f\n", cast_secs);
    printf("Ftoi time %f\n", ftoi_secs);

    printf("Diff %f%%\n", (ftoi_secs / cast_secs) * 100);
}


void
main()
{
    test_cast_float_to_int_rounds_to_nearest_integer();
    // test_cast_ftoi_speed_perf();
    printf("TEST SMALLMATH complete.\n");
}

#include    "util.h"
#include    <stdlib.h>

int randsgn()
{
    return (rand() % 2 ? -1 : 1);
}

float randf(float limit)
{
    return (float)rand()/(float)RAND_MAX * limit;
}

float wrapf(float value, float limit)
{
    if (value >= limit)
        return value - limit;
    else if (value < 0.0f)
        return value + limit;
    else
        return value;
}

int wrap(int value, int limit)
{
    if (value >= limit)
        return value - limit;
    else if (value < 0)
        return value + limit;
    else
        return value;
}

float sgnf(float value)
{
    if (value == 0.0f)
        return 0.0f;

    return (value > 0.0f ? 1.0f : -1.0f);
}

int sgn(int value)
{
    if (value == 0)
        return 0;

    return (value > 0 ? 1 : -1);
}

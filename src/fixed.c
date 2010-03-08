#include "fixed.h"
#include "debug.h"

fixed itofp(int num)
{
    return (fixed)(num << FIXPOINT_SHIFT);
}

fixed ftofp(float num)
{
    return (fixed)(num * FIXPOINT_SCALE);
}

fixed dtofp(double num)
{
    return (fixed)(num * FIXPOINT_SCALE);
}

float fptof(fixed num)
{
    return (float)(num / (float)FIXPOINT_SCALE);
}

fixed fpdiv(fixed dividend, fixed divisor)
{
    return (fixed)((((int64_t)dividend) << FIXPOINT_SHIFT) / divisor);
}

fixed fpadd(fixed num1, fixed num2)
{
    return num1 + num2;
}

fixed fpsub(fixed num1, fixed num2)
{
    return num1 - num2;
}

fixed fpmul(fixed num1, fixed num2)
{
    return (fixed)(((int64_t)num1 * num2) >> FIXPOINT_SHIFT);
}

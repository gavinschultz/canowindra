#include "fixed.h"
#include "debug.h"

fixed itofp(int num)
{
    return (fixed)(num << FPSHIFT);
}

fixed ftofp(float num)
{
    return (fixed)(num * FPSCALE);
}

fixed dtofp(double num)
{
    return (fixed)(num * FPSCALE);
}

float fptof(fixed num)
{
    return (float)(num / (float)FPSCALE);
}

fixed fpdiv(fixed dividend, fixed divisor)
{
    return (fixed)((((int64_t)dividend) << FPSHIFT) / divisor);
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
    return (fixed)(((int64_t)num1 * num2) >> FPSHIFT);
}

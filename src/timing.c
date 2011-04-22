#include    <windows.h>
#include    "timing.h"
#include    "debug.h"
#include    "fixed.h"

static fixed _start_time = 0;
static fixed _elapsed_time = 0;
static long frame = 0;
static float frame_rate = 0.0;

fixed get_time()
{
    static uint64_t start = 0;
    static uint64_t frequency = 0;
    uint64_t counter = 0;

    if (start == 0)
    {
        QueryPerformanceCounter((LARGE_INTEGER*)&start);
        QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
        trace("start: %lld, frequency: %lld", start, frequency);
        return 0;
    }

    QueryPerformanceCounter((LARGE_INTEGER*)&counter);
    return dtofp((double)(counter - start) / (double)frequency);
}

void start_frame()
{
    _start_time = get_time();
}

void end_frame()
{
    _elapsed_time = get_time() - _start_time;
    frame++;
    if (_elapsed_time > 0)
    {
        frame_rate = (float)(FPONE) / (float)_elapsed_time;
    }
}

float get_frame_rate()
{
    return frame_rate;
}

fixed get_last_frame_time()
{
    return _elapsed_time;
}

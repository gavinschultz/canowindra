#ifndef  GEL_INC
#define  GEL_INC

#include "fixed.h"

struct GameState
{
    int quit;
    int paused;
    float x_axis;
    float y_axis;
    fixed step_time;
};

extern struct GameState app;

#endif

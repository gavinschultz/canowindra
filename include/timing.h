
#ifndef  TIMING_INC
#define  TIMING_INC

#include    "fixed.h"

void start_frame(void);
void end_frame(void);
float get_frame_rate(void);
fixed get_last_frame_time(void); // Get the time elapsed in the last frame
fixed get_time(void);            // Get the time elapsed since the application began

#endif

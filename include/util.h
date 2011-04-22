
#ifndef  UTIL_INC
#define  UTIL_INC

#define MIN(x,y)    (x < y ? x : y)
#define MAX(x,y)    (x > y ? x : y)

int randsgn(void);
float randf(float limit);
float wrapf(float value, float limit);
int wrap(int value, int limit);
float sgnf(float);
int sgn(int);

#endif


#ifndef  UTIL_INC
#define  UTIL_INC

#define MIN(x,y)    (x < y ? x : y)
#define MAX(x,y)    (x > y ? x : y)

float square(float);
int rand_sign(void);
float randf(float limit);
float wrapf(float value, float limit);

#endif

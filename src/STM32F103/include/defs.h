#ifndef DEFS_H
#define DEFS_H

#include<stdint.h>
#include <math.h>

#define OUTPUT 1
#define INPUT 0

#define SERIAL_BUFFER_SIZE 64

#define byte uint8_t

#ifndef abs
template<typename T> T abs(T x){ return x > 0?x:-x; }
#endif

#ifndef min
template<typename T> T min(T a, T b){ return a < b?a:b; }
#endif

#ifndef max
template<typename T> T max(T a, T b){ return a > b?a:b; }
#endif

#ifndef fabs
#define fabs(x) abs(x)
#endif

#ifndef size_t
#define size_t int
#endif

#ifndef constrain
#define constrain(v, _min, _max) v<_min?_min:(v>_max?_max:v)
#endif


#endif

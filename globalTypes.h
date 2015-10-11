#include <stdint.h>

typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float real32;
typedef double real64;

#define Array_Count(x) (sizeof(x)/sizeof((x[0])))

#define PREFERED_WINDOW_WIDTH 1024
#define PREFERED_WINDOW_HEIGHT 768
#define WINDOW_NAME "Screen\n"

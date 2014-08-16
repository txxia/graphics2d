#ifndef DEBUG_H
#include <stdio.h>
#ifndef DEBUG
#  define dbg(fmt, ...) (void)0
#else
#  define dbg(fmt, ...) fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__)
#endif
#endif

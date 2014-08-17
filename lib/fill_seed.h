#ifndef FILL_SEED_H
#define FILL_SEED_H
#include <stdbool.h>

/* Simple Seed Fill algorithm for 4-connected boundary-defined regions */
extern void seedFillSimple4c(int sx, int sy,
                             const int bx1, const int by1,  // box of boundary, all inclusive
                             const int bx2, const int by2,
                             int** boundaries,              // boundary pix are set to 1
                             void (*callback)(int, int));

#endif

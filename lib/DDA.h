#ifndef DDA_H
#define DDA_H

/* Digital Differential Analyzer routine for rastering a line*/
extern void DDA(int x1, int y1, int x2, int y2,
         void (*callback)(int, int));
#endif

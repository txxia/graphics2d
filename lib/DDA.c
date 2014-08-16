#include "DDA.h"

/* Digital Differential Analyzer routine for rastering a line*/
void DDA(int x1, int y1, int x2, int y2,
         void (*callback)(int, int)){
    // approximate the line length
    int length = (abs(x2-x1) >= abs(y2-y1)) ? abs(x2-x1) : abs(y2-y1);

    // select the larger of dx or dy to be one raster unit
    float dx = (x2-x1)/(float)length,
          dy = (y2-y1)/(float)length;

    // round the values rather than truncate, so that center pixel addressing
    // is handled correctly
    float x = x1+0.5,
          y = y1+0.5;

    // begin main loop
    for(int i=0; i<=length; i++){
        callback((int)x, (int)y);
        x += dx;
        y += dy;
    }
}

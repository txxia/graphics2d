#include "Stack.h"
#include "fill_polygon.h"

//#define DEBUG
#include "debug.h"

void Paritysc(int y,                // the current position of scanline
              int left,             // the left most pixel
              int right,            // the right most pixel
              int numint,           // the number of intersections on the line
              Stack* stack,         // contains intxns sorted in scanline order
              void (*callback)(int, int)    // callback function to set pixel
             ) {
    // initialize the variables
    int i = 1,                      // ? number of intersection processed
        parity = 0,
        x = left;                   // x coord of the current pixel
    float oldxi=left-1,
          xi = stack_pop(stack).x;    // x coord of the current intersection

    // for x in the range left<=x<=right on the scan line
    while(x <= right) {
        // if oldpixel -> newpixel crosses one or more edges
        while(x >= (int)(xi + 0.5) && i<=numint){
            oldxi = xi;
            if(i<numint)
                xi = stack_pop(stack).x;        // get the next intxn
            else
                xi = right+1;                   // if xi is the last intxn
            parity = parity ? 0 : 1;            // flips the parity
            i++;
            dbg("intersection: %f -> %f", oldxi, xi);
        }

        // inside the polygon, sets pixel to polygon color
        if(parity)
            callback(x, y);
        // outside the polygon, sets pixel to background color
//        else
//            callback(x, y);
        //if(x >= right) i += 1;
        x+=1;
        dbg("curr pix: %d, %d\n", x, y);
    }
}


#include "bresenham.h"

/* Bresenham's line rasterization algorithm for the first octant */
void bresenhamFloatOctant(int x1, int y1, int x2, int y2,
                          void (*callback)(int, int)) {
    // initialize variables
    int x = x1, y = y1;
    float dx = x2 - x1,
          dy = y2 - y1,
          m = dy / dx;
    // initialize e to compensate for a nonzero intercept
    float e = m - 0.5;

    // begin main loop
    for(int i = 0; i <= dx; i++) {
        callback((int)x, (int)y);
        while(e > 0) {
            y++;
            e--;
        }
        x++;
        e += m;
    }

}

/* Bresenham's integer algorithm for the first octant */
void bresenhamIntegerOctant(int x1, int y1, int x2, int y2,
                            void (*callback)(int, int)) {
    // initialize variables
    int x = x1, y = y1;
    int dx = x2 - x1,
        dy = y2 - y1,
        // initialize e to compensate for a nonzero intercept
        e = 2 * dy - dx;

    // begin main loop
    for(int i = 0; i <= dx; i++) {
        callback((int)x, (int)y);
        while(e > 0) {
            y++;
            e -= 2 * dx;
        }
        x++;
        e += 2 * dy;
    }
}

/* Generalized integer Bresenham's algorithm for all quadrants*/
void bresenhamInteger(int x1, int y1, int x2, int y2,
                      void (*callback)(int, int)) {
    // initialize variables
    int x = x1, y = y1;
    int dx = abs(x2 - x1),
        dy = abs(y2 - y1),
        // directions
        s1 = Sign(x2-x1),
        s2 = Sign(y2-y1);

    // interchange dx and dy, depending on the slope of the line
    _Bool interchanged = 0;
    if(dy > dx){
        int temp = dx;
        dx = dy;
        dy = temp;
        interchanged = 1;
    }

    // initialize the error term to compensate for a nonzero intercept
    int e = 2*dy-dx;

    // begin main loop
    for(int i = 0; i <= dx; i++) {
        callback(x, y);
        while(e > 0) {
            if(interchanged) x += s1;
            else             y += s2;
            e -= 2 * dx;
        }
        if(interchanged) y += s2;
        else             x += s1;
        e += 2 * dy;
    }
}

/* Bresenham's incremental circle algorithm for the first quadrant */
void bresenhamCircle(int rad, void (*callback)(int, int)){
    // initialize the variables
    int xi = 0,
        yi = rad,
        di = 2*(1-rad),
        limit = 0,
        diff_dist;
    while(yi >= limit){
        callback(xi, yi);
        if(di<0){
            diff_dist = 2*di+2*yi-1;
            if (diff_dist <= 0) mh(xi, yi, di);     // case1
            else                md(xi, yi, di);     // case2
        } else if (di > 0){
            diff_dist = 2*di-2*xi-1;
            if (diff_dist <= 0) md(xi, yi, di);     // case4
            else                mv(xi, yi, di);     // case5
        } else                  md(xi, yi, di);     // case3
    }
}

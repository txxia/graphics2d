#include "ellipse.h"

void NaiveMidpointEllipse(int a, int b,
                          void (*callback)(int, int)) {
    // initiate the variables
    int x = (int)(a + 0.5),
        y = 0,
        d1, d2;
    while(b * b * (x - 0.5) > a * a * (y + 1)) { // start in region 1 (|dx| > |dy|)
        callback(x, y);
        d1 = b*b*(2*x*x-2*x+0.5) + a*a*(2*y*y+4*y+2) - 2*a*a*b*b;
        if(d1 < 0) {
            y++;                                        // move vertically
        } else {
            x--;                                        // move diagonally
            y++;
        }
    }
    // initialize the decision variable in region 2 (where |dx| < |dy|)
    while(x >= 0) {
        callback(x, y);
        d2 = b*b*(2*x*x-4*x+2) + a*a*(2*y*y+2*y+0.5) - 2*a*a*b*b;
        if(d2 < 0) {                                    // move diagonally
            x--;
            y++;
        } else {                                        // move horizontally
            x--;
        }
    }
}

void EfficientMidpointEllipse(int a, int b,
                              void (*callback)(int, int)) {
    // initialize the variables
    int x = (int)(a+0.5),
        y = 0,
        taa = a*a,
        t2aa = taa<<1,
        t4aa = t2aa<<1,
        tbb = b*b,
        t2bb = tbb<<1,
        t4bb = t2bb<<1,
        t2bbx = t2bb*x,
        tx = x,
        d1, d2;
    // initialize the decision variable in region 1
    d1 = t2bbx * (x-1) + tbb/2 + t2aa*(1-tbb);
    while(t2bb*tx > t2aa*y) {
        callback(x, y);
        if(d1 < 0) {                                    // move vertically
            y++;
            d1 += t4aa*y + t2aa;
        } else {                                        // move diagonally
            x--;
            y++;
            d1 = d1 - t4bb*x + t4aa*y + t2aa;
            tx = x;
        }
    }

    // initialize the decision variable in region 2
    d2 = t2bb*(x*x+1) - t4bb*x + t2aa*(y*y+y-tbb) + taa/2;
    while(x>=0) {
        callback(x, y);
        if(d2<0) {                                      // move diagonally
            x--;
            y++;
            d2 += t4aa*y - t4bb*x + t2bb;
        } else {                                        // move horizontally
            x--;
            d2 -= t4bb*x + t2bb;
        }
    }
}

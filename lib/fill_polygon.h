#ifndef FILL_POLYGON
#define FILL_POLYGON

#define Sign(x) ((x>0)-(x<0))

/* Simple parity polygon scan conversion algorithm*/
/* Prior to calling this function, the intersections on a scan line
   are sorted into scanline order and pushed onto a stack.
   This function is then called FOR EACH scan line. */
extern void Paritysc(int y,                // the current position of scanline
              int left,             // the left most pixel
              int right,            // the right most pixel
              int numint,           // the number of intersections on the line
              Stack* stack,         // contains intxns sorted in scanline order
              void (*callback)(int, int)    // callback function to set pixel
             );
#endif

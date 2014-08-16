#ifndef BRESENHAM_H
#define BRESENHAM_H

#ifndef Sign
#  define Sign(x) (((x)>0)-((x)<0))
#endif
#ifndef mh
#  define mh(x,y,d) do{(x)++;(d)+=2*(x)+1;}while(0)             // move horizontally
#endif // mh
#ifndef md
#  define md(x,y,d) do{(x)++;(y)--;(d)+=2*(x)-2*(y)+2;}while(0) // move diagonally
#endif // md
#ifndef mv
#  define mv(x,y,d) do{(y)--;(d)-=2*(y)+1;}while(0)             // move vertically
#endif // mv

/* Bresenham's line rasterization algorithm for the first octant */
extern void bresenhamFloatOctant(int x1, int y1, int x2, int y2,
                          void (*callback)(int, int));

/* Bresenham's integer algorithm for the first octant */
extern void bresenhamIntegerOctant(int x1, int y1, int x2, int y2,
                            void (*callback)(int, int));

/* Generalized integer Bresenham's algorithm for all quadrants */
extern void bresenhamInteger(int x1, int y1, int x2, int y2,
                      void (*callback)(int, int));

/* Bresenham's incremental circle algorithm for the first quadrant */
extern void bresenhamCircle(int rad, void (*callback)(int, int));

#endif

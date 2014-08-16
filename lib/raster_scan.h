#ifndef RASTER_SCAN_H_INCLUDED
#define RASTER_SCAN_H_INCLUDED

#include <SDL2/SDL.h>

#define UNITSIZE 10

extern void drawLine(SDL_Renderer *renderer,
                     unsigned int x1, unsigned int y1,
                     unsigned int x2, unsigned int y2);

extern void drawGrid(SDL_Renderer *renderer,
                     unsigned int width, unsigned int height);

extern void setPixel(SDL_Renderer *renderer,
                     unsigned int x, unsigned int y,
                     SDL_Color color);

extern SDL_Color parseColor(char *str);        /* parse from string containing RGB/RGBA value */

extern unsigned int toPixel(unsigned int i);   /* convert real coordinate to virtual coordinate */

extern unsigned int toUnit(unsigned int i);    /* convert virtual coordinate to real coordinate */

#endif // RASTER_SCAN_H_INCLUDED


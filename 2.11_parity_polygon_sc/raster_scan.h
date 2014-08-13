#ifndef RASTER_SCAN_H_INCLUDED
#define RASTER_SCAN_H_INCLUDED

#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 480
#define UNITSIZE 10

extern int drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);

extern int initGrid(SDL_Renderer *renderer, int width, int height);

extern int setPixel(SDL_Renderer *renderer, int x, int y, SDL_Color color);

extern SDL_Color parseColor(char *str);        /* parse from string containing RGB/RGBA value */

extern unsigned int toPixel(unsigned int i);   /* convert real coordinate to virtual coordinate */

extern unsigned int toUnit(unsigned int i);    /* convert virtual coordinate to real coordinate */

#endif // RASTER_SCAN_H_INCLUDED


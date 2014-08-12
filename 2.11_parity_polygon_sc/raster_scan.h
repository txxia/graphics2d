#ifndef RASTER_SCAN_H_INCLUDED
#define RASTER_SCAN_H_INCLUDED

#define WIDTH 1280
#define HEIGHT 720
#define UNITSIZE 10

int drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);

int initGrid(SDL_Renderer *renderer, int width, int height);

int setPixel(SDL_Renderer *renderer, int x, int y, SDL_Color color);

SDL_Color parseColor(char *str);        /* parse from string containing RGB/RGBA value */

unsigned int toPixel(unsigned int i);   /* convert real coordinate to virtual coordinate */

unsigned int toUnit(unsigned int i);    /* convert virtual coordinate to real coordinate */

#include "raster_scan.c"

#endif // RASTER_SCAN_H_INCLUDED


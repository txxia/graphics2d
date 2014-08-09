#ifndef RASTER_SCAN_H_INCLUDED
#define RASTER_SCAN_H_INCLUDED

int drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);

int setPixel(SDL_Renderer *renderer, int x, int y, SDL_Color color);

SDL_Color parseColor(char *str);        /* parse from string containing RGB/RGBA value */

#include "raster_scan.c"

#endif // RASTER_SCAN_H_INCLUDED


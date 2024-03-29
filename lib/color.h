#ifndef COLOR_H
#define COLOR_H
#include <SDL2/SDL.h>

extern SDL_Color parseColor(char *str);        /* parse from string containing RGB/RGBA value */

extern SDL_Color int2Color(Uint32 i);

extern SDL_Color interpolationLinear(SDL_Color a, SDL_Color b, double i);

#endif

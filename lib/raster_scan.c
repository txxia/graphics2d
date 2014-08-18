#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "raster_scan.h"
//#define DEBUG

#ifndef DEBUG
#  define dbg(fmt, ...) (void)0
#else
#  define dbg(fmt, ...) fprintf(stderr, "DEBUG %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

void drawLine(SDL_Renderer *renderer,
              unsigned int x1, unsigned int y1,
              unsigned int x2, unsigned int y2) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    // Present render to the screen
    SDL_RenderPresent(renderer);
}

void drawGrid(SDL_Renderer *renderer, unsigned int width, unsigned int height){
    SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);
    for(int x = 0; x < width; x += UNITSIZE) {
        SDL_RenderDrawLine(renderer, x, 0, x, height);
    }
    for(int y = 0; y < height; y += UNITSIZE) {
        SDL_RenderDrawLine(renderer, 0, y, width, y);
    }
    // Present render to the screen
    SDL_RenderPresent(renderer);
}

/* RGBA color*/
void setPixel(SDL_Renderer *renderer,
              unsigned int x, unsigned int y,
              SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect;
    rect.h = rect.w = UNITSIZE - 1;
    rect.x = x * UNITSIZE + 1;
    rect.y = y * UNITSIZE + 1;
    SDL_RenderFillRect(renderer, &rect);

    // Present render to the screen
    SDL_RenderPresent(renderer);
}

unsigned int toPixel(unsigned int i){
    return i*UNITSIZE + UNITSIZE/2;
}

unsigned int toUnit(unsigned int i){
    return i/UNITSIZE;
}

//int main (){
//    char *colors[] = {"0xff00ff",
//                     "0x123456",
//                     "0x000000",
//                     "0x00000000",
//                     "0xffffffff",
//                     "0xabcdefff",
//                     "0xabcdefgh"};
//    for(int i = 0; i<sizeof(colors)/sizeof(char *); i++){
//        SDL_Color color = parseColor(colors[i]);
//        dbg("parseColor(%s) --> %02x, %02x, %02x, %02x",
//               colors[i],
//               color.r, color.g, color.b, color.a);
//    }
//}


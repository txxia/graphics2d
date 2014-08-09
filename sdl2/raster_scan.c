#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

//#define DEBUG

#ifndef DEBUG
#  define dbg(fmt, ...) (void)0
#else
#  define dbg(fmt, ...) fprintf(stderr, "DEBUG %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define PIXSIZE 10

int drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    // Present render to the screen
    SDL_RenderPresent(renderer);
}

/* RGBA color*/
int setPixel(SDL_Renderer *renderer, int x, int y, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect;
    rect.h = rect.w = PIXSIZE - 1;
    rect.x = x * PIXSIZE + 1;
    rect.y = y * PIXSIZE + 1;
    SDL_RenderFillRect(renderer, &rect);

    // Present render to the screen
    SDL_RenderPresent(renderer);
}

SDL_Color parseColor(char *str) {
    SDL_Color color;
    if(strlen(str) > 6) {
        char code[10]={'0','x'};

        /* supports 0xFFFFFF, #FFFFFF, FFFFFF */
        if(str[0] == '#') strncat(code, str+1, strlen(str)-1);
        else if(str[0]=='0' && (tolower(str[1])=='x')) strncat(code, str+2, strlen(str)-2);
        else strncat(code, str, strlen(str));

        Uint32 c = strtol(code, NULL, 16);
        dbg("%08x \t", c);

        if(strlen(code) == strlen("0x000000")) {       /* RGB mode */
            dbg("RGB\t");
            color.r = (c >> 16) & 255;
            color.g = (c >> 8) & 255;
            color.b = (c) & 255;
            color.a = 255;
        } else if(strlen(code) == strlen("0x00000000")) {
            dbg("RGBA\t");
            SDL_Color color;
            color.r = (c >> 24) & 255;
            color.g = (c >> 16) & 255;
            color.b = (c >> 8) & 255;
            color.a = (c) & 255;
        }
    }
    return color;
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

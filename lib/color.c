#include <assert.h>
#include "debug.h"

#include "color.h"


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
            color.r = (c >> 24) & 255;
            color.g = (c >> 16) & 255;
            color.b = (c >> 8) & 255;
            color.a = (c) & 255;
        }
    }
    return color;
}

SDL_Color int2Color(Uint32 i){
    SDL_Color color;
    color.a = (i >> 24) & 255;
    color.r = (i >> 16) & 255;
    color.g = (i >> 8) & 255;
    color.b = (i) & 255;
    return color;
}

SDL_Color interpolationLinear(SDL_Color a, SDL_Color b, double i){
    assert(i>=0 && i<=1);
    SDL_Color c;
    c.a = (i)*a.a+(1-i)*b.a;
    c.r = (i)*a.r+(1-i)*b.r;
    c.g = (i)*a.g+(1-i)*b.g;
    c.b = (i)*a.b+(1-i)*b.b;
    return c;
}

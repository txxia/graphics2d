#include <SDL2/SDL.h>
#include "raster_scan.h"
#define WIDTH 640
#define HEIGHT 480

#define Sign(x) (((x)>0)-((x)<0))

/* Bresenham's line rasterization algorithm for the first octant */
void bresenhamFloatOctant(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
    // draw a referencing line
    drawLine(renderer,
             toPixel(x1), toPixel(y1), toPixel(x2), toPixel(y2));

    // initialize variables
    int x = x1, y = y1;
    float dx = x2 - x1,
          dy = y2 - y1,
          m = dy / dx;
    // initialize e to compensate for a nonzero intercept
    float e = m - 0.5;

    // begin main loop
    for(int i = 0; i <= dx; i++) {
        setPixel(renderer, (int)x, (int)y, parseColor("0x0000ff11"));
        while(e > 0) {
            y++;
            e--;
        }
        x++;
        e += m;
        SDL_Delay(10);
    }

}

/* Bresenham's integer algorithm for the first octant */
void bresenhamIntegerOctant(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
    // draw a referencing line
    drawLine(renderer,
             toPixel(x1), toPixel(y1), toPixel(x2), toPixel(y2));

    // initialize variables
    int x = x1, y = y1;
    int dx = x2 - x1,
        dy = y2 - y1,
        // initialize e to compensate for a nonzero intercept
        e = 2 * dy - dx;

    // begin main loop
    for(int i = 0; i <= dx; i++) {
        setPixel(renderer, (int)x, (int)y, parseColor("0x0000ff11"));
        while(e > 0) {
            y++;
            e -= 2 * dx;
        }
        x++;
        e += 2 * dy;
        SDL_Delay(10);
    }
}

/* Generalized integer Bresenham's algorithm for all quadrants*/
void bresenhamInteger(SDL_Renderer *renderer, int x1, int y1, int x2, int y2) {
    // draw a referencing line
    drawLine(renderer,
             toPixel(x1), toPixel(y1), toPixel(x2), toPixel(y2));

    // initialize variables
    int x = x1, y = y1;
    int dx = abs(x2 - x1),
        dy = abs(y2 - y1),
        // directions
        s1 = Sign(x2-x1),
        s2 = Sign(y2-y1);

    // interchange dx and dy, depending on the slope of the line
    _Bool interchanged = 0;
    if(dy > dx){
        int temp = dx;
        dx = dy;
        dy = temp;
        interchanged = 1;
    }

    // initialize the error term to compensate for a nonzero intercept
    int e = 2*dy-dx;

    // begin main loop
    for(int i = 0; i <= dx; i++) {
        setPixel(renderer, (int)x, (int)y, parseColor("0x0000ff11"));
        while(e > 0) {
            if(interchanged) x += s1;
            else             y += s2;
            e -= 2 * dx;
        }
        if(interchanged) y += s2;
        else             x += s1;
        e += 2 * dy;
        SDL_Delay(10);
    }
}

void draw(SDL_Renderer *renderer){

    // using bresenham's float algorithm
    bresenhamFloatOctant(renderer, 5, 10, 55, 30);

    // using bresenham's integer algorithm
    bresenhamIntegerOctant(renderer, 5, 15, 55, 35);

    // using general bresenham's algorithm
    bresenhamInteger(renderer, 5, 30, 55, 15);
    bresenhamInteger(renderer, 5, 45, 55, 0);
    bresenhamInteger(renderer, 15, 45, 45, 0);
}

int main(int argc, char *argv[]) {
    int loop = 1;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Raster Scanning",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          WIDTH, HEIGHT,
                                          SDL_WINDOW_SHOWN);

    // Setup renderer
    SDL_Renderer* pRenderer =  SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    // Set render color to red.
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);

    // Clear winow
    SDL_RenderClear(pRenderer);

    // Render grid
    drawGrid(pRenderer, WIDTH, HEIGHT);

    // standard drawing function
    draw(pRenderer);

    // The window is open: enter program loop
    while(loop) {
        SDL_WaitEvent(&event);
        if(event.type == SDL_MOUSEBUTTONDOWN) {
            int px = toUnit(event.button.x);
            int py = toUnit(event.button.y);
            setPixel(pRenderer, px, py, parseColor("000000"));
        }
        if(event.type == SDL_QUIT)
            loop = 0;
    }

    // Clean up
    SDL_Quit();
    return 0;
}

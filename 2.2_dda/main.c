#include <SDL2/SDL.h>
#include "raster_scan.h"
#define WIDTH 640
#define HEIGHT 480

void draw(SDL_Renderer *renderer, int x1, int y1, int x2, int y2){
    // draw a referencing line
    drawLine(renderer,
             toPixel(x1), toPixel(y1), toPixel(x2), toPixel(y2));

    // approximate the line length
    int length = (abs(x2-x1) >= abs(y2-y1)) ? abs(x2-x1) : abs(y2-y1);

    // select the larger of dx or dy to be one raster unit
    float dx = (x2-x1)/(float)length,
          dy = (y2-y1)/(float)length;

    // round the values rather than truncate, so that center pixel addressing
    // is handled correctly
    float x = x1+0.5,
          y = y1+0.5;

    // begin main loop
    for(int i=0; i<=length; i++){
        setPixel(renderer, (int)x, (int)y, parseColor("0x0000ff11"));
        x += dx;
        y += dy;
        SDL_Delay(10);
    }

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

    // default drawing function
    draw(pRenderer, 80, 60, 4, 7);

    // The window is open: enter program loop
    while(loop) {
        SDL_WaitEvent(&event);
        if(event.type == SDL_MOUSEBUTTONDOWN){
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

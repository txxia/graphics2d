#include <SDL2/SDL.h>
#include "../lib/raster_scan.h"
#include "../lib/DDA.h"
#define WIDTH 640
#define HEIGHT 480
#define DELAY 8

SDL_Renderer *pRenderer;

void setPix(int x, int y){
    setPixel(pRenderer, x, y, parseColor("#000000"));
    SDL_Delay(DELAY);
}

void draw(){
    // draw a referencing line
    drawLine(pRenderer,
             toPixel(80), toPixel(60), toPixel(4), toPixel(7));
    DDA(80, 60, 4, 7, setPix);
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
    pRenderer =  SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    // Set render color to red.
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);

    // Clear winow
    SDL_RenderClear(pRenderer);

    // Render grid
    drawGrid(pRenderer, WIDTH, HEIGHT);

    // default drawing function
    draw();

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

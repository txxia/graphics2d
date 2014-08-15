#include <SDL2/SDL.h>
#include "raster_scan.h"
#define WIDTH 640
#define HEIGHT 480
#define PIXSIZE 10

int draw(){

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
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    for(int x = 0; x < WIDTH; x += PIXSIZE) {
        SDL_RenderDrawLine(pRenderer, x, 0, x, HEIGHT);
    }
    for(int y = 0; y < WIDTH; y += PIXSIZE) {
        SDL_RenderDrawLine(pRenderer, 0, y, WIDTH, y);
    }
    // Present render to the screen
    SDL_RenderPresent(pRenderer);

    // my standard drawing function
    draw();

    // The window is open: enter program loop
    while(loop) {
        SDL_WaitEvent(&event);
        if(event.type == SDL_MOUSEBUTTONDOWN){
            int px = event.button.x / PIXSIZE;
            int py = event.button.y / PIXSIZE;

            setPixel(pRenderer, px, py, parseColor("000000"));
        }
        if(event.type == SDL_QUIT)
            loop = 0;
    }

    // Clean up
    SDL_Quit();
    return 0;
}

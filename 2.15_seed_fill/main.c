#include <SDL2/SDL.h>
#include <stdbool.h>

#include <pthread.h>
#include <semaphore.h>

#include <time.h>
#include "../lib/raster_scan.h"
#include "../lib/bresenham.h"
#include "../lib/fill_seed.h"
#define WIDTH 320
#define HEIGHT 240

#define BWIDTH 40
#define BHEIGHT 30
#define DELAY 0

SDL_Renderer* pRenderer;
int **boundaries;
SDL_Color currColor;

void setPix(int x, int y){
    setPixel(pRenderer, x, y, currColor);
    SDL_Delay(DELAY);
}

void draw(){
    // boundary pixels
    inline void savePix(int x, int y){
        boundaries[x][y] = 1;
        setPixel(pRenderer, x, y, parseColor("#000000"));
    }
    boundaries = (int **)malloc(BWIDTH*sizeof(int*));
    for(int i=0; i<BWIDTH; i++){
        boundaries[i] = (int *)calloc(BHEIGHT, sizeof(int));
    }
    bresenhamInteger(0, 0, 4, 18, savePix);
    bresenhamInteger(0, 0, 18, 4, savePix);
    bresenhamInteger(4, 18, 18, 4, savePix);

    bresenhamInteger(18, 6, 33, 2, savePix);
    bresenhamInteger(33, 2, 37, 17, savePix);
    bresenhamInteger(37, 17, 22, 21, savePix);
    bresenhamInteger(22, 21, 18, 6, savePix);

    // seed fill
    currColor = int2Color(rand());
    seedFillSimple4cBFS(1, 1,
                     0, 0, 0+BWIDTH-1, 0+BHEIGHT-1,
                     boundaries, setPix);

}

int main(int argc, char *argv[]) {
    srand(time(NULL));
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

    // default drawing function
    drawGrid(pRenderer, WIDTH, HEIGHT);
    draw(pRenderer);
    drawGrid(pRenderer, WIDTH, HEIGHT);

    // The window is open: enter program loop
    while(loop) {
        SDL_WaitEvent(&event);
        if(event.type == SDL_MOUSEBUTTONDOWN){
            int px = toUnit(event.button.x);
            int py = toUnit(event.button.y);
            if(!boundaries[py][px]){
                currColor = int2Color(rand());
                seedFillSimple4cBFS(px, py, 0, 0, 0+BWIDTH-1, 0+BHEIGHT-1,
                                    boundaries, setPix);
            }
        }
        if(event.type == SDL_QUIT){
            for(int i=0; i<BWIDTH; i++){
                free(boundaries[i]);
            }
            free(boundaries);
            loop = 0;
        }
    }

    // Clean up
    SDL_Quit();
    return 0;
}

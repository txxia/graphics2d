#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include "../lib/raster_scan.h"
#include "../lib/bresenham.h"
#include "../lib/color.h"
#include "../lib/fill_seed.h"
#define WIDTH 320
#define HEIGHT 240

#define BWIDTH 40
#define BHEIGHT 30
#define DELAY 1

SDL_Renderer* pRenderer;
bool **boundaries;
SDL_Color currColor;

void setPix(int x, int y){
    setPixel(pRenderer, x, y, currColor);
    SDL_Delay(DELAY);
}

void draw(){
    // boundary pixels
    inline void savePix(int x, int y){
        boundaries[x][y] = true;
        setPixel(pRenderer, x, y, parseColor("#000000"));
    }
    boundaries = (bool **)malloc(BWIDTH*sizeof(bool*));
    for(int i=0; i<BWIDTH; i++){
        boundaries[i] = (bool *)calloc(BHEIGHT, sizeof(bool));
    }
    bresenhamInteger(0, 0, 4, 18, savePix);
    bresenhamInteger(0, 0, 18, 4, savePix);
    bresenhamInteger(4, 18, 18, 4, savePix);

    bresenhamInteger(15, 10, 30, 6, savePix);
    bresenhamInteger(30, 6, 34, 21, savePix);
    bresenhamInteger(34, 21, 19, 25, savePix);
    bresenhamInteger(19, 25, 15, 10, savePix);
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
                // seed fill
                currColor = int2Color(rand());
                // left button triggers BFS seed filling
                if(event.button.button == SDL_BUTTON_LEFT)
                    seedFillSimple4cBFS(px, py, 0, 0, 0+BWIDTH-1, 0+BHEIGHT-1,
                                        boundaries, setPix);
                // other buttons trigger DFS seed filling
                else
                    seedFillSimple4c(px, py, 0, 0, 0+BWIDTH-1, 0+BHEIGHT-1,
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

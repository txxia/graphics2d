#include <SDL2/SDL.h>
#include "../lib/raster_scan.h"
#include "../lib/bresenham.h"
#define WIDTH 640
#define HEIGHT 480

#define DELAY 5

SDL_Renderer *pRenderer;

void setPix(int x, int y){
    setPixel(pRenderer, x, y, parseColor("#3333ee"));
    SDL_Delay(DELAY);
}

void draw(){
    // bresenham's float algorithm
    drawLine(pRenderer,
             toPixel(5), toPixel(10), toPixel(55), toPixel(30));
    bresenhamFloatOctant(5, 10, 55, 30, setPix);

    // bresenham's integer algorithm
    drawLine(pRenderer,
             toPixel(5), toPixel(15), toPixel(55), toPixel(35));
    bresenhamIntegerOctant(5, 15, 55, 35, setPix);

    // general bresenham's algorithm
    drawLine(pRenderer,
             toPixel(5), toPixel(30), toPixel(55), toPixel(15));
    bresenhamInteger(5, 30, 55, 15, setPix);
    drawLine(pRenderer,
             toPixel(5), toPixel(45), toPixel(55), toPixel(0));
    bresenhamInteger(5, 45, 55, 0, setPix);
    drawLine(pRenderer,
             toPixel(15), toPixel(45), toPixel(45), toPixel(0));
    bresenhamInteger(15, 45, 45, 0, setPix);

    // bresenham's circle algorithm
    for(int i=4;i<38;i+=(40-i)/3)
        bresenhamCircle(i, setPix);
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
    pRenderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    // Set render color to red.
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);

    // Clear winow
    SDL_RenderClear(pRenderer);

    // standard drawing function
    drawGrid(pRenderer, WIDTH, HEIGHT);
    draw();
    drawGrid(pRenderer, WIDTH, HEIGHT);


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

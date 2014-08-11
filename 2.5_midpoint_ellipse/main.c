#include <SDL2/SDL.h>
#include "raster_scan.h"
#define WIDTH 640
#define HEIGHT 480
#define DELAY 10

#define Sign(x) ((x>0)-(x<0))

void NaiveMidpointEllipse(SDL_Renderer *renderer, int a, int b) {
    // initiate the variables
    int x = (int)(a + 0.5),
        y = 0,
        d1, d2;
    while(b * b * (x - 0.5) > a * a * (y + 1)) { // start in region 1 (|dx| > |dy|)
        setPixel(renderer, x, y, parseColor("#cc0000"));
        d1 = b*b*(2*x*x-2*x+0.5) + a*a*(2*y*y+4*y+2) - 2*a*a*b*b;
        if(d1 < 0) {
            y++;                                        // move vertically
        } else {
            x--;                                        // move diagonally
            y++;
        }
        SDL_Delay(DELAY);
    }
    // initialize the decision variable in region 2 (where |dx| < |dy|)
    while(x >= 0) {
        setPixel(renderer, x, y, parseColor("#aaaa00"));
        d2 = b*b*(2*x*x-4*x+2) + a*a*(2*y*y+2*y+0.5) - 2*a*a*b*b;
        if(d2 < 0) {                                    // move diagonally
            x--;
            y++;
        } else {                                        // move horizontally
            x--;
        }
        SDL_Delay(DELAY);
    }
}

void EfficientMidpointEllipse(SDL_Renderer *renderer, int a, int b) {
    // initialize the variables
    int x = (int)(a+0.5),
        y = 0,
        taa = a*a,
        t2aa = taa<<1,
        t4aa = t2aa<<1,
        tbb = b*b,
        t2bb = tbb<<1,
        t4bb = t2bb<<1,
        t2abb = a*t2bb,
        t2bbx = t2bb*x,
        tx = x,
        d1, d2;
    // initialize the decision variable in region 1
    d1 = t2bbx * (x-1) + tbb/2 + t2aa*(1-tbb);
    while(t2bb*tx > t2aa*y) {
        setPixel(renderer, x, y, parseColor("#0000cc"));
        if(d1 < 0) {                                    // move vertically
            y++;
            d1 += t4aa*y + t2aa;
        } else {                                        // move diagonally
            x--;
            y++;
            d1 = d1 - t4bb*x + t4aa*y + t2aa;
            tx = x;
        }
        SDL_Delay(DELAY);
    }

    // initialize the decision variable in region 2
    d2 = t2bb*(x*x+1) - t4bb*x + t2aa*(y*y+y-tbb) + taa/2;
    while(x>=0) {
        setPixel(renderer, x, y, parseColor("#00cc00"));
        if(d2<0) {                                      // move diagonally
            x--;
            y++;
            d2 += t4aa*y - t4bb*x + t2bb;
        } else {                                        // move horizontally
            x--;
            d2 -= t4bb*x + t2bb;
        }
        SDL_Delay(DELAY);
    }
}

void draw(SDL_Renderer *renderer) {
    NaiveMidpointEllipse(renderer, 30, 20);
    EfficientMidpointEllipse(renderer, 50, 40);
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

    // default drawing function
    drawGrid(pRenderer, WIDTH, HEIGHT);
    draw(pRenderer);
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

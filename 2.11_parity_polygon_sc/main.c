#include <SDL2/SDL.h>
#include <stdio.h>
#include "raster_scan.h"
#include "Stack.h"
#define DELAY 3

#define Sign(x) ((x>0)-(x<0))

//#define DEBUG

#ifndef DEBUG
#  define dbg(fmt, ...) (void)0
#else
#  define dbg(fmt, ...) fprintf(stderr, "[DEBUG] " fmt "\n", ##__VA_ARGS__)
#endif

/* constructor for stack data */
StackData Intxn(float x, float y) {
    StackData data;
    data.x = x;
    data.y = y;
    return data;
}

/* Simple parity polygon scan conversion algorithm*/
/* Prior to calling this function, the intersections on a scan line
   are sorted into scanline order and pushed onto a stack.
   This function is then called FOR EACH scan line. */
void Paritysc(SDL_Renderer *renderer,
              int y,                // the current position of scanline
              int left,             // the left most pixel
              int right,            // the right most pixel
              int numint,           // the number of intersections on the line
              Stack* stack           // contains intxns sorted in scanline order
             ) {
    // initialize the variables
    int i = 1,                      // ? number of intersection processed
        parity = 0,
        x = left;                   // x coord of the current pixel
    float oldxi=left-1,
          xi = stack_pop(stack).x;    // x coord of the current intersection

    // for x in the range left<=x<=right on the scan line
    while(x <= right) {
        // if oldpixel -> newpixel crosses one or more edges
        while(x >= (int)(xi + 0.5) && i<=numint){
            oldxi = xi;
            if(i<numint)
                xi = stack_pop(stack).x;        // get the next intxn
            else
                xi = right+1;                   // if xi is the last intxn
            parity = parity ? 0 : 1;            // flips the parity
            i++;
            dbg("intersection: %f -> %f", oldxi, xi);
        }

        // inside the polygon, sets pixel to polygon color
        if(parity)
            setPixel(renderer, x, y, parseColor("#ff0000"));
        // outside the polygon, sets pixel to background color
        else
            setPixel(renderer, x, y, parseColor("#dddddd"));
        //if(x >= right) i += 1;
        x+=1;
        SDL_Delay(DELAY);
        dbg("curr pix: %d, %d\n", x, y);
    }
}

void draw(SDL_Renderer *renderer) {
    demoTriangle(renderer);
    demoSnowFlake(renderer);

}

void demoSnowFlake(SDL_Renderer* renderer){
    Stack* stack = stack_init();
    int left = 20,
        right = 40;
    stack_push(stack, Intxn(30.4, 19.5));
    stack_push(stack, Intxn(29.7, 19.5));

    stack_push(stack, Intxn(31.1, 18.5));
    stack_push(stack, Intxn(29.2, 18.5));

    stack_push(stack, Intxn(31.6, 17.5));
    stack_push(stack, Intxn(28.6, 17.5));

    stack_push(stack, Intxn(32.2, 16.5));
    stack_push(stack, Intxn(28.1, 16.5));

    stack_push(stack, Intxn(32.6, 15.5));
    stack_push(stack, Intxn(27.4, 15.5));

    stack_push(stack, Intxn(37.6, 14.5));
    stack_push(stack, Intxn(33.1, 14.5));
    stack_push(stack, Intxn(26.7, 14.5));
    stack_push(stack, Intxn(21.5, 14.5));

    stack_push(stack, Intxn(37, 13.5));
    stack_push(stack, Intxn(33.7, 13.5));
    stack_push(stack, Intxn(26.1, 13.5));
    stack_push(stack, Intxn(23.1, 13.5));

    stack_push(stack, Intxn(36.4, 12.5));
    stack_push(stack, Intxn(34.4, 12.5));
    stack_push(stack, Intxn(25.4, 12.5));
    stack_push(stack, Intxn(23.6, 12.5));

    stack_push(stack, Intxn(35.6, 11.5));
    stack_push(stack, Intxn(34.9, 11.5));
    stack_push(stack, Intxn(24.9, 11.5));
    stack_push(stack, Intxn(24.1, 11.5));

    stack_push(stack, Intxn(35.5, 10.5));
    stack_push(stack, Intxn(35.2, 10.5));
    stack_push(stack, Intxn(24.9, 10.5));
    stack_push(stack, Intxn(24.2, 10.5));

    stack_push(stack, Intxn(36, 9.5));
    stack_push(stack, Intxn(34.4, 9.5));
    stack_push(stack, Intxn(25.5, 9.5));
    stack_push(stack, Intxn(23.9, 9.5));

    stack_push(stack, Intxn(36.6, 8.5));
    stack_push(stack, Intxn(33.8, 8.5));
    stack_push(stack, Intxn(25.9, 8.5));
    stack_push(stack, Intxn(23.3, 8.5));

    stack_push(stack, Intxn(38.4, 7.5));
    stack_push(stack, Intxn(33.3, 7.5));
    stack_push(stack, Intxn(26.4, 7.5));
    stack_push(stack, Intxn(22.8, 7.5));

    stack_push(stack, Intxn(37.9, 6.5));
    stack_push(stack, Intxn(32.8, 6.5));
    stack_push(stack, Intxn(27, 6.5));
    stack_push(stack, Intxn(22.4, 6.5));

    stack_push(stack, Intxn(32.5, 5.5));
    stack_push(stack, Intxn(26.5, 5.5));

    stack_push(stack, Intxn(31.9, 4.5));
    stack_push(stack, Intxn(28.1, 4.5));

    stack_push(stack, Intxn(31.4, 3.5));
    stack_push(stack, Intxn(28.6, 3.5));

    stack_push(stack, Intxn(30.8, 2.5));
    stack_push(stack, Intxn(29.3, 2.5));

    stack_push(stack, Intxn(30.4, 1.5));
    stack_push(stack, Intxn(29.6, 1.5));

    Paritysc(renderer, 1.5, left, right, 2, stack);
    Paritysc(renderer, 2.5, left, right, 2, stack);
    Paritysc(renderer, 3.5, left, right, 2, stack);
    Paritysc(renderer, 4.5, left, right, 2, stack);
    Paritysc(renderer, 5.5, left, right, 2, stack);
    Paritysc(renderer, 6.5, left, right, 4, stack);
    Paritysc(renderer, 7.5, left, right, 4, stack);
    Paritysc(renderer, 8.5, left, right, 4, stack);
    Paritysc(renderer, 9.5, left, right, 4, stack);
    Paritysc(renderer, 10.5, left, right, 4, stack);
    Paritysc(renderer, 11.5, left, right, 4, stack);
    Paritysc(renderer, 12.5, left, right, 4, stack);
    Paritysc(renderer, 13.5, left, right, 4, stack);
    Paritysc(renderer, 14.5, left, right, 4, stack);
    Paritysc(renderer, 15.5, left, right, 2, stack);
    Paritysc(renderer, 16.5, left, right, 2, stack);
    Paritysc(renderer, 17.5, left, right, 2, stack);
    Paritysc(renderer, 18.5, left, right, 2, stack);
    Paritysc(renderer, 19.5, left, right, 2, stack);

    stack_delete(stack);
}

void demoTriangle(SDL_Renderer* renderer){
    Stack* stack = stack_init();
    int left = 1,
        right = 20;
    stack_push(stack, Intxn(9.6, 15.5));
    stack_push(stack, Intxn(9.4, 15.5));

    stack_push(stack, Intxn(10.2, 14.5));
    stack_push(stack, Intxn(8.5, 14.5));

    stack_push(stack, Intxn(10.6, 13.5));
    stack_push(stack, Intxn(7.6, 13.5));

    stack_push(stack, Intxn(10.9, 12.5));
    stack_push(stack, Intxn(6.97, 12.5));

    stack_push(stack, Intxn(11.3, 11.5));
    stack_push(stack, Intxn(6.3, 11.5));

    stack_push(stack, Intxn(11.6, 10.5));
    stack_push(stack, Intxn(4.8, 10.5));

    stack_push(stack, Intxn(11.9, 9.5));
    stack_push(stack, Intxn(5.6, 9.5));

    stack_push(stack, Intxn(12.4, 8.5));
    stack_push(stack, Intxn(7.6, 8.5));

    stack_push(stack, Intxn(12.6, 7.5));
    stack_push(stack, Intxn(9.4, 7.5));

    stack_push(stack, Intxn(12.9, 6.5));
    stack_push(stack, Intxn(11.1, 6.5));

    stack_push(stack, Intxn(13.2, 5.5));
    stack_push(stack, Intxn(12.9, 5.5));

    Paritysc(renderer, 5.5, left, right, 2, stack);
    Paritysc(renderer, 6.5, left, right, 2, stack);
    Paritysc(renderer, 7.5, left, right, 2, stack);
    Paritysc(renderer, 8.5, left, right, 2, stack);
    Paritysc(renderer, 9.5, left, right, 2, stack);
    Paritysc(renderer, 10.5, left, right, 2, stack);
    Paritysc(renderer, 11.5, left, right, 2, stack);
    Paritysc(renderer, 12.5, left, right, 2, stack);
    Paritysc(renderer, 13.5, left, right, 2, stack);
    Paritysc(renderer, 14.5, left, right, 2, stack);
    Paritysc(renderer, 15.5, left, right, 2, stack);

    stack_delete(stack);
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

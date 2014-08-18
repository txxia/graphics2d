#include <SDL2/SDL.h>
#include "../lib/raster_scan.h"
#include "../lib/Stack.h"
#include "../lib/color.h"
#include "../lib/fill_polygon.h"
#define DELAY 8
#define WIDTH 480
#define HEIGHT 240

SDL_Renderer *pRenderer;
void demoStar();
void demoTriangle();

void setPix(int x, int y){
    setPixel(pRenderer, x, y, parseColor("#aaaaff"));
    SDL_Delay(DELAY);
}

void draw() {
    demoTriangle();
    demoStar();
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


void demoStar(){
    Stack* stack = stack_init();
    int left = 20,
        right = 40;
    stack_push(stack, stack_data(30.4, 19.5));
    stack_push(stack, stack_data(29.7, 19.5));

    stack_push(stack, stack_data(31.1, 18.5));
    stack_push(stack, stack_data(29.2, 18.5));

    stack_push(stack, stack_data(31.6, 17.5));
    stack_push(stack, stack_data(28.6, 17.5));

    stack_push(stack, stack_data(32.2, 16.5));
    stack_push(stack, stack_data(28.1, 16.5));

    stack_push(stack, stack_data(32.6, 15.5));
    stack_push(stack, stack_data(27.4, 15.5));

    stack_push(stack, stack_data(37.6, 14.5));
    stack_push(stack, stack_data(33.1, 14.5));
    stack_push(stack, stack_data(26.7, 14.5));
    stack_push(stack, stack_data(21.5, 14.5));

    stack_push(stack, stack_data(37, 13.5));
    stack_push(stack, stack_data(33.7, 13.5));
    stack_push(stack, stack_data(26.1, 13.5));
    stack_push(stack, stack_data(23.1, 13.5));

    stack_push(stack, stack_data(36.4, 12.5));
    stack_push(stack, stack_data(34.4, 12.5));
    stack_push(stack, stack_data(25.4, 12.5));
    stack_push(stack, stack_data(23.6, 12.5));

    stack_push(stack, stack_data(35.6, 11.5));
    stack_push(stack, stack_data(34.9, 11.5));
    stack_push(stack, stack_data(24.9, 11.5));
    stack_push(stack, stack_data(24.1, 11.5));

    stack_push(stack, stack_data(35.5, 10.5));
    stack_push(stack, stack_data(35.2, 10.5));
    stack_push(stack, stack_data(24.9, 10.5));
    stack_push(stack, stack_data(24.2, 10.5));

    stack_push(stack, stack_data(36, 9.5));
    stack_push(stack, stack_data(34.4, 9.5));
    stack_push(stack, stack_data(25.5, 9.5));
    stack_push(stack, stack_data(23.9, 9.5));

    stack_push(stack, stack_data(36.6, 8.5));
    stack_push(stack, stack_data(33.8, 8.5));
    stack_push(stack, stack_data(25.9, 8.5));
    stack_push(stack, stack_data(23.3, 8.5));

    stack_push(stack, stack_data(38.4, 7.5));
    stack_push(stack, stack_data(33.3, 7.5));
    stack_push(stack, stack_data(26.4, 7.5));
    stack_push(stack, stack_data(22.8, 7.5));

    stack_push(stack, stack_data(37.9, 6.5));
    stack_push(stack, stack_data(32.8, 6.5));
    stack_push(stack, stack_data(27, 6.5));
    stack_push(stack, stack_data(22.4, 6.5));

    stack_push(stack, stack_data(32.5, 5.5));
    stack_push(stack, stack_data(26.5, 5.5));

    stack_push(stack, stack_data(31.9, 4.5));
    stack_push(stack, stack_data(28.1, 4.5));

    stack_push(stack, stack_data(31.4, 3.5));
    stack_push(stack, stack_data(28.6, 3.5));

    stack_push(stack, stack_data(30.8, 2.5));
    stack_push(stack, stack_data(29.3, 2.5));

    stack_push(stack, stack_data(30.4, 1.5));
    stack_push(stack, stack_data(29.6, 1.5));

    Paritysc(1.5, left, right, 2, stack, setPix);
    Paritysc(2.5, left, right, 2, stack, setPix);
    Paritysc(3.5, left, right, 2, stack, setPix);
    Paritysc(4.5, left, right, 2, stack, setPix);
    Paritysc(5.5, left, right, 2, stack, setPix);
    Paritysc(6.5, left, right, 4, stack, setPix);
    Paritysc(7.5, left, right, 4, stack, setPix);
    Paritysc(8.5, left, right, 4, stack, setPix);
    Paritysc(9.5, left, right, 4, stack, setPix);
    Paritysc(10.5, left, right, 4, stack, setPix);
    Paritysc(11.5, left, right, 4, stack, setPix);
    Paritysc(12.5, left, right, 4, stack, setPix);
    Paritysc(13.5, left, right, 4, stack, setPix);
    Paritysc(14.5, left, right, 4, stack, setPix);
    Paritysc(15.5, left, right, 2, stack, setPix);
    Paritysc(16.5, left, right, 2, stack, setPix);
    Paritysc(17.5, left, right, 2, stack, setPix);
    Paritysc(18.5, left, right, 2, stack, setPix);
    Paritysc(19.5, left, right, 2, stack, setPix);

    stack_delete(stack);
}

void demoTriangle(){
    Stack* stack = stack_init();
    int left = 1,
        right = 20;
    stack_push(stack, stack_data(9.6, 15.5));
    stack_push(stack, stack_data(9.4, 15.5));

    stack_push(stack, stack_data(10.2, 14.5));
    stack_push(stack, stack_data(8.5, 14.5));

    stack_push(stack, stack_data(10.6, 13.5));
    stack_push(stack, stack_data(7.6, 13.5));

    stack_push(stack, stack_data(10.9, 12.5));
    stack_push(stack, stack_data(6.97, 12.5));

    stack_push(stack, stack_data(11.3, 11.5));
    stack_push(stack, stack_data(6.3, 11.5));

    stack_push(stack, stack_data(11.6, 10.5));
    stack_push(stack, stack_data(4.8, 10.5));

    stack_push(stack, stack_data(11.9, 9.5));
    stack_push(stack, stack_data(5.6, 9.5));

    stack_push(stack, stack_data(12.4, 8.5));
    stack_push(stack, stack_data(7.6, 8.5));

    stack_push(stack, stack_data(12.6, 7.5));
    stack_push(stack, stack_data(9.4, 7.5));

    stack_push(stack, stack_data(12.9, 6.5));
    stack_push(stack, stack_data(11.1, 6.5));

    stack_push(stack, stack_data(13.2, 5.5));
    stack_push(stack, stack_data(12.9, 5.5));

    Paritysc(5.5, left, right, 2, stack, setPix);
    Paritysc(6.5, left, right, 2, stack, setPix);
    Paritysc(7.5, left, right, 2, stack, setPix);
    Paritysc(8.5, left, right, 2, stack, setPix);
    Paritysc(9.5, left, right, 2, stack, setPix);
    Paritysc(10.5, left, right, 2, stack, setPix);
    Paritysc(11.5, left, right, 2, stack, setPix);
    Paritysc(12.5, left, right, 2, stack, setPix);
    Paritysc(13.5, left, right, 2, stack, setPix);
    Paritysc(14.5, left, right, 2, stack, setPix);
    Paritysc(15.5, left, right, 2, stack, setPix);

    stack_delete(stack);
}

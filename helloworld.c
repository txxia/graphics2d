#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {
		int WIDTH = 640, HEIGHT = 480;
    int gogogo = 1;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Hello World! :D", 
    									  SDL_WINDOWPOS_UNDEFINED,
    									  SDL_WINDOWPOS_UNDEFINED,
    									  WIDTH, HEIGHT,
    									  SDL_WINDOW_SHOWN);

		SDL_Surface *screen = SDL_GetWindowSurface(window);
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
		SDL_UpdateWindowSurface(window);

    while (gogogo) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT)
            gogogo = 0;
    }
    // The window is open: enter program loop (see SDL_PollEvent)

    SDL_Quit();
    return 0;
}

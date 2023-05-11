#include "cachelife_display.h"

SDL_Window* cachelife_window = NULL;
SDL_Renderer* cachelife_renderer = NULL;

SDL_Rect square_cell = {0,0,10,10};
size_t n_cells_X = 320;
size_t n_cells_Y = 160;


int InitCachelifeDisplay(void) {
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return -1;
    }

    cachelife_window = SDL_CreateWindow("Cachelife", 1, 1, 1600, 800, SDL_WINDOW_SHOWN);
    if (cachelife_window == NULL) {
        SDL_Log("Unable to open the window...\n");
        goto memory_clean;
    }
    cachelife_renderer = SDL_CreateRenderer(cachelife_window,-1,SDL_RENDERER_SOFTWARE);
    if (cachelife_renderer == NULL) {
        SDL_Log("Unable to open the renderer...\n");
        goto memory_clean;
    }
    return 0;

    memory_clean:
        SDL_DestroyRenderer(cachelife_renderer);
        SDL_DestroyWindow(cachelife_window);
        return -1;

}

void SetCachelifeDisplayDimensions(const unsigned int square_size) {
    square_cell.w = square_size;
    square_cell.h = square_size;
}

void QuitCachelifeDisplay(void) {
    SDL_DestroyRenderer(cachelife_renderer);
    SDL_DestroyWindow(cachelife_window);
    SDL_Quit();
}
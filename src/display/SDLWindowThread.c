#include "cachelife_display.h"


int SDLWindowThread(void* arg) {
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            // Quit the program if the window is closed
            exit(EXIT_FAILURE);
            break;
        }
        // Handle other types of events as needed
        // ...
//        SDL_UpdateWindowSurface(cachelife_window);
    }
    return 0;
}
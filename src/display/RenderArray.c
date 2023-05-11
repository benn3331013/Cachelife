#include "cachelife_display.h"


void RenderArray(const size_t len, i64* x_positions, i64* y_positions) {
    SDL_SetRenderDrawColor(cachelife_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(cachelife_renderer);

    SDL_SetRenderDrawColor(cachelife_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (size_t i=0 ; i < len; i++) {
        // if the square can be displayed on the screen
        if ( x_positions[i] >=0 && x_positions[i] < n_cells_X && y_positions[i] >=0 && y_positions[i] < n_cells_Y ) {

            square_cell.x = square_cell.w*x_positions[i];
            square_cell.y = square_cell.w*y_positions[i];
            SDL_RenderFillRect(cachelife_renderer, &square_cell);
        }
    }
    SDL_RenderPresent(cachelife_renderer);
}

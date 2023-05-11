#include "cachelife_display.h"

size_t PowerOf2(const uint_layer exp) {
    return 1<<exp;
}

void RenderNodes(uint_index nod, uint_layer lay, i64 offset_x, i64 offset_y) {
    RenderNode(nod, lay, offset_x, offset_y);
    SDL_RenderPresent(cachelife_renderer);
}

void RenderNode(uint_index nod, uint_layer lay, const i64 x, const i64 y) {
    if (lay == 0) {
        square_cell.x = square_cell.w*x;
        square_cell.y = square_cell.w*y;
//        SDL_SetRenderDrawColor(cachelife_renderer, 40, 40, 40, SDL_ALPHA_OPAQUE);
//        SDL_RenderDrawRect(cachelife_renderer, &square_cell);
        if ( nod == 0 ) {
            SDL_SetRenderDrawColor(cachelife_renderer, 40, 40, 40, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(cachelife_renderer, &square_cell);
        }
        else {
            SDL_SetRenderDrawColor(cachelife_renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
            SDL_RenderFillRect(cachelife_renderer, &square_cell);
        }
    }
    else {
//        if ( x>= 0 && x<n_cells_X && y>= 0 && y<n_cells_Y) {
            size_t p2_offset = PowerOf2(lay-1);
            RenderNode( cache[lay][nod].NorthWest_index, lay-1 , x , y );
            RenderNode( cache[lay][nod].NorthEast_index, lay-1 , x + p2_offset , y );
            RenderNode( cache[lay][nod].SouthWest_index, lay-1 , x, y + p2_offset );
            RenderNode( cache[lay][nod].SouthEast_index, lay-1 , x + p2_offset , y + p2_offset);
//        }
    }
}
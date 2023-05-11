/*
 *  Filename: cachelife_display.h
 *  Author: Benn3331013
 *  Description: The is the header file for the display functions of the C implementation of Cachelife. 
 *      See the README for details of the implementation.
 */
#ifndef CACHELIFE_DISPLAY_H
#define CACHELIFE_DISPLAY_H
#include "SDL2/SDL.h"
#include "cachelife.h"

extern SDL_Window* cachelife_window;
extern SDL_Renderer* cachelife_renderer;
extern SDL_Thread* thread_window;

extern SDL_Rect square_cell;
extern size_t n_cells_X;
extern size_t n_cells_Y;


/*
    \brief Initializes Cachelife's display module. This allocates memory for the render, windows, etc.
    This module is based on SDL2 and SDL2_ttf.
    \return 0 if the initialization went accordingly. -1 if any error occured.
*/
int InitCachelifeDisplay(void);
/*
    \brief De-initializes Cachelife's display module.
*/
void QuitCachelifeDisplay(void);

/*
    \brief Sets the dimensions of a cell.
*/
void SetCachelifeDisplayDimensions(const unsigned int square_size);

/*
    \brief This is the function run by the thread handling the window. 
    Without it, your whole machine could freeze while running Cachelife.
*/
int SDLWindowThread(void* arg);

/*
    \brief Renders an array of cells to the screen.
    \param len the number of living cells
    \param x_positions the x positions of the living cells
    \param y_positions the y positions of the living cells
*/
void RenderArray(const size_t len, i64* x_positions, i64* y_positions);
/*
    \brief Render a cached node to the screen. This should NOT be called by the user. 
    Prefer calling RenderNodes instead.
    \param nod the index of the node in the cache.
    \param lay the layer of the node.
*/
void RenderNode(const uint_index nod, const uint_layer lay, const i64 x, const i64 y);
/*
    \brief Render a cached node to the screen.
    \param nod the index of the node in the cache.
    \param lay the layer of the node.
*/
void RenderNodes(const uint_index nod, const uint_layer couche, const i64 offset_x, const i64 offset_y);



/*
    \brief Print a node. This was only a debugging tool and should never be used.
*/
void PrintNode(const uint_index nod, const uint_layer lay );

/*
    \brief Print arrays of coordinates. This was only a debugging tool and should never be used.
*/
void PrintArray(const size_t len, i64* x_positions, i64* y_positions);
#endif  //  CACHELIFE_DISPLAY_H
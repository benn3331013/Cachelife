#include "cachelife.h"

// This function will be called at most 65536 times. (which is once per possible 4x4 node)
uint_index Next_4x4( const QuadTreeNode nod ) {
    ufast8 line1;
    ufast8 line2;
    ufast8 line3;
    ufast8 n_living_cells;
    QuadTreeNode returned;
    returned.layer = 1;
    returned.future_index = -1;// -1 en unsigned

//  North-West cell
    line1 = (ufast8) cache[ 1 ][nod.NorthWest_index].NorthWest_index + cache[ 1 ][nod.NorthWest_index].NorthEast_index + cache[ 1 ][nod.NorthEast_index].NorthWest_index;
    line2 = (ufast8) cache[ 1 ][nod.NorthWest_index].SouthWest_index + cache[ 1 ][nod.NorthEast_index].SouthWest_index;
    line3 = (ufast8) cache[ 1 ][nod.SouthWest_index].NorthWest_index + cache[ 1 ][nod.SouthWest_index].NorthEast_index + cache[ 1 ][nod.SouthEast_index].NorthWest_index;
    n_living_cells = line1 + line2 + line3;
//  Game of life rules
    if ( (n_living_cells == 3) || 
    ( cache[ 1 ][nod.NorthWest_index].SouthEast_index == 1 && n_living_cells == 2 ) ) {
        // living cell
        returned.NorthWest_index = 1;
    }
    else {
        // dead cell
        returned.NorthWest_index = 0 ;
    }

//  North-East cell
    line1 += cache[ 1 ][nod.NorthEast_index].NorthEast_index - cache[ 1 ][nod.NorthWest_index].NorthWest_index;
    line2 = cache[ 1 ][nod.NorthWest_index].SouthEast_index + cache[ 1 ][nod.NorthEast_index].SouthEast_index;
    line3 += cache[ 1 ][nod.SouthEast_index].NorthEast_index  - cache[ 1 ][nod.SouthWest_index].NorthWest_index;
    n_living_cells = line1 + line2 + line3;
//  Game of life rules
    if ( (n_living_cells == 3) ||
    ( cache[ 1 ][nod.NorthEast_index].SouthWest_index == 1 && n_living_cells == 2 ) ) {
        // living cell
        returned.NorthEast_index = 1;
    }
    else {
        // dead cell
        returned.NorthEast_index = 0;
    }

//  South-East cell
    line1 = line2 + cache[ 1 ][nod.NorthEast_index].SouthWest_index;
    line2 = line3 - cache[ 1 ][nod.SouthEast_index].NorthWest_index;
    line3 = cache[ 1 ][nod.SouthEast_index].SouthWest_index + cache[ 1 ][nod.SouthEast_index].SouthEast_index + cache[ 1 ][nod.SouthWest_index].SouthEast_index;
    n_living_cells = line1 + line2 + line3;
//  Game of life rules
    if ( (n_living_cells == 3) ||
    ( cache[ 1 ][nod.SouthEast_index].NorthWest_index == 1 && n_living_cells == 2 ) ) {
        // living cell
        returned.SouthEast_index = 1;
    }
    else {
        // dead cell
        returned.SouthEast_index = 0;
    }
    
//  South-West cell
    line1 += cache[ 1 ][nod.NorthWest_index].SouthWest_index - cache[ 1 ][nod.NorthEast_index].SouthEast_index;
    line2 = cache[ 1 ][nod.SouthWest_index].NorthWest_index + cache[ 1 ][nod.SouthEast_index].NorthWest_index;
    line3 += cache[ 1 ][nod.SouthWest_index].SouthWest_index - cache[ 1 ][nod.SouthEast_index].SouthEast_index;
    n_living_cells = line1 + line2 + line3;
//  Game of life rules
    if ( (n_living_cells == 3) ||
    ( cache[ 1 ][nod.SouthWest_index].NorthEast_index == 1 && n_living_cells == 2 ) ) {
        // living cell
        returned.SouthWest_index = 1;
    }
    else {
        // dead cell
        returned.SouthWest_index = 0;
    }
    return VerifyCache(returned);
}
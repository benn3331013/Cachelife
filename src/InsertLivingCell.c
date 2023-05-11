#include "cachelife.h"

QuadTreeNode InsertLivingCell(QuadTreeNode nod, i64 x, i64 y, uint_layer lay, size_t pow_2) {
    if ( lay == 1 ) {
        if ( x >= 1 ) {
            if ( y >= 1 ) {
                nod.SouthEast_index = 1;
            }
            else {
                nod.NorthEast_index = 1;
            }
        }
        else {
            if ( y >= 1 ) {
                nod.SouthWest_index  = 1;
            }
            else {
                nod.NorthWest_index = 1;
            }
        }
    }
    else {
        if ( x >= pow_2/2 ) {
            if ( y >= pow_2/2 ) {
                nod.SouthEast_index = VerifyCache( InsertLivingCell( cache[lay - 1][nod.SouthEast_index] , x - pow_2/2 , y - pow_2/2 , lay - 1 , pow_2/2) );
            }
            else {
                nod.NorthEast_index = VerifyCache( InsertLivingCell( cache[lay - 1][nod.NorthEast_index] , x - pow_2/2 , y, lay - 1 , pow_2/2) );
            }
        }
        else {
            if ( y >= pow_2/2 ) {
                nod.SouthWest_index = VerifyCache( InsertLivingCell( cache[lay - 1][nod.SouthWest_index] , x , y - pow_2/2 , lay - 1 , pow_2/2) );
            }
            else {
                nod.NorthWest_index = VerifyCache( InsertLivingCell( cache[lay - 1][nod.NorthWest_index] , x , y , lay - 1 , pow_2/2) );
            }
        }
    }
    nod.layer = lay;
    nod.future_index = -1;
    return(nod);
}

#include "cachelife.h"


i64 x_minimum = 0;
i64 y_minimum = 0;



size_t max(const size_t a, const size_t b) {
    return (a > b) ? a : b;
}

void CachelifeSet_array(const size_t n_living_cells, i64* x_positions, i64* y_positions) {
//( TabCoord tableau, unsigned int* x_minimum, unsigned int* y_minimum, unsigned int* couche ) {

    x_minimum = x_positions[0];
    size_t x_maximum = x_positions[0];
    y_minimum = y_positions[0];
    size_t y_maximum = y_positions[0];
    for (size_t i=0 ; i < n_living_cells ; i++ ) {
        if ( x_positions[i] < x_minimum ) {
            x_minimum = x_positions[i];
        }
        else if ( x_positions[i] > x_maximum ) {
            x_maximum = x_positions[i];
        }
        if ( y_positions[i] < y_minimum ) {
            y_minimum = y_positions[i];
        }
        else if ( y_positions[i] > y_maximum ) {
            y_maximum = y_positions[i];
        }
    }
    const size_t dimension = max( x_maximum - x_minimum , y_maximum - y_minimum);
    
    root_layer = 0;
    size_t pow_2 = 1;
    while ( pow_2 <= dimension ) {
        root_layer += 1;
        pow_2 *= 2;
    }

    CreateZeros( root_layer );

    root_index = 0;
    for (size_t i=0 ; i < n_living_cells ; i++ ) {
        root_index = VerifyCache( InsertLivingCell( cache[root_layer][root_index], x_positions[i] - x_minimum, y_positions[i] - y_minimum, root_layer, pow_2) );
    }
}
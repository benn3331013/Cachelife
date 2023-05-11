#include "cachelife.h"

inline size_t _PowerOf2(const uint_layer exp) {
    return 1<<exp;
}

void TreatNode(uint_layer lay, uint_index node, size_t* len, i64** x_positions, i64** y_positions, i64 x_min, i64 y_min) {
    if ( lay == 1 ) {
        if ( cache[lay][node].NorthWest_index == 1 ) {
            *len += 1;
            *x_positions = realloc(*x_positions, (*len) * sizeof(i64*) );
            *y_positions = realloc(*y_positions, (*len) * sizeof(i64*) );
            (*x_positions)[*len - 1] = x_min;
            (*y_positions)[*len - 1] = y_min;
        }
        if ( cache[lay][node].NorthEast_index == 1 ) {
            *len += 1;
            *x_positions = realloc(*x_positions, (*len) * sizeof(i64*) );
            *y_positions = realloc(*y_positions, (*len) * sizeof(i64*) );
            (*x_positions)[*len - 1] = x_min + 1;
            (*y_positions)[*len - 1] = y_min;
        }
        if ( cache[lay][node].SouthWest_index == 1 ) {
            *len += 1;
            *x_positions = realloc(*x_positions, (*len) * sizeof(i64*) );
            *y_positions = realloc(*y_positions, (*len) * sizeof(i64*) );
            (*x_positions)[*len - 1] = x_min;
            (*y_positions)[*len - 1] = y_min + 1;
        }
        if ( cache[lay][node].SouthEast_index == 1 ) {
            *len += 1;
            *x_positions = realloc(*x_positions, (*len) * sizeof(i64*) );
            *y_positions = realloc(*y_positions, (*len) * sizeof(i64*) );
            (*x_positions)[*len - 1] = x_min + 1;
            (*y_positions)[*len - 1] = y_min + 1;
        }
    }
    else {
        size_t p_2 = _PowerOf2(lay - 1);
        if ( cache[lay][node].NorthWest_index != 0 ) {
            TreatNode( lay - 1, cache[lay][node].NorthWest_index, len, x_positions, y_positions, x_min, y_min );
        }
        if ( cache[lay][node].NorthEast_index != 0 ) {
            TreatNode( lay - 1, cache[lay][node].NorthEast_index, len, x_positions, y_positions, x_min + p_2, y_min );
        }
        if ( cache[lay][node].SouthWest_index != 0 ) {
            TreatNode( lay - 1, cache[lay][node].SouthWest_index, len, x_positions, y_positions, x_min, y_min + p_2 );
        }
        if ( cache[lay][node].SouthEast_index != 0 ) {
            TreatNode( lay - 1, cache[lay][node].SouthEast_index, len, x_positions, y_positions, x_min + p_2, y_min + p_2);
        }
    }
}

size_t ArrayFromNode(const uint_layer lay, const uint_index nod, i64** x_positions, i64** y_positions, const i64 x_min, const i64 y_min) {
    free(*x_positions);
    *x_positions = NULL;
    free(*y_positions);
    *y_positions = NULL;
    size_t len = 0;
    TreatNode(lay, nod, &len, x_positions, y_positions, x_min, y_min);

    return len;
}
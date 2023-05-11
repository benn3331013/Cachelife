#include "cachelife_display.h"

void PrintNode(const uint_index nod, const uint_layer lay ) {
    if ( lay == 0 ) {
        printf("%lu ", nod);
    }
    else {
        PrintNode(cache[ lay ][ nod ].NorthWest_index, lay - 1);
        PrintNode(cache[ lay ][ nod ].NorthEast_index, lay - 1);
        PrintNode(cache[ lay ][ nod ].SouththWest_index, lay - 1);
        PrintNode(cache[ lay ][ nod ].SouththEast_index, lay - 1);
    }
}
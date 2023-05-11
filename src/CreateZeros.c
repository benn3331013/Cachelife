#include "cachelife.h"


void CreateZeros(const uint_layer lay) {
    // if (lay > size_cache) {
    cache = (QuadTreeNode**)realloc( cache,  (lay + 1) * sizeof(QuadTreeNode*) );
    dimensions_cache = (uint_index*)realloc( dimensions_cache , (lay + 1) * sizeof(uint_index) );

    for (uint_layer i = size_cache + 1 ; i <= lay ; i++) {
        cache[i] = (QuadTreeNode*)malloc(sizeof(QuadTreeNode));
        dimensions_cache[i] = 1;

        cache[i][0].layer = i;
        cache[i][0].NorthWest_index = 0 ;
        cache[i][0].NorthEast_index = 0 ;
        cache[i][0].SouthWest_index = 0 ;
        cache[i][0].SouthEast_index = 0 ;

        cache[i][0].future_index = 0 ;
    }
    size_cache = lay;
    // }
}
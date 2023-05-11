#include "cachelife.h"


//  TODO : is it necessary to call upon VerifyCache?
//  TODO : if (...) { isolate part of the node, return Crop(...)}
uint_index Crop( const QuadTreeNode nod, uint_layer* layer ) {
    if ( *layer > 1 ) {
        QuadTreeNode cropped_node;
        cropped_node.layer = nod.layer - 1;
        if ( cache[nod.layer - 1][nod.NorthWest_index].NorthWest_index == 0 && 
        cache[nod.layer - 1][nod.NorthWest_index].SouthWest_index == 0 && 
        cache[nod.layer - 1][nod.NorthWest_index].NorthEast_index == 0) {
            cropped_node.NorthWest_index = cache[nod.layer - 1][nod.NorthWest_index].SouthEast_index;
        }
        else {
            return VerifyCache(nod);
        }
        if ( cache[nod.layer - 1][nod.NorthEast_index].NorthEast_index == 0 && 
        cache[nod.layer - 1][nod.NorthEast_index].SouthEast_index == 0 && 
        cache[nod.layer - 1][nod.NorthEast_index].NorthWest_index == 0) {
            cropped_node.NorthEast_index = cache[nod.layer - 1][nod.NorthEast_index].SouthWest_index;
        }
        else {
            return VerifyCache(nod);
        }
        if ( cache[nod.layer - 1][nod.SouthWest_index].SouthWest_index == 0 && 
        cache[nod.layer - 1][nod.SouthWest_index].NorthWest_index == 0 && 
        cache[nod.layer - 1][nod.SouthWest_index].SouthEast_index == 0) {
            cropped_node.SouthWest_index = cache[nod.layer - 1][nod.SouthWest_index].NorthEast_index;
        }
        else {
            return VerifyCache(nod);
        }
        if ( cache[nod.layer - 1][nod.SouthEast_index].SouthEast_index == 0 && 
        cache[nod.layer - 1][nod.SouthEast_index].SouthWest_index == 0 && 
        cache[nod.layer - 1][nod.SouthEast_index].NorthEast_index == 0) {
            cropped_node.SouthEast_index = cache[nod.layer - 1][nod.SouthEast_index].NorthWest_index;
        }
        else {
            return VerifyCache(nod);
        }
        cropped_node.future_index = -1;// unsigned -1
        *layer -= 1;
        uint_index tempo = Crop( cropped_node , layer );
        return ( tempo );
    }
    else {
        printf("Error: Can't crop a node with layer 1 or 0\n");
        return VerifyCache(nod);
    }
}

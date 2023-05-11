#include "cachelife.h"


// Vérifie si la node est présente dans le cache : si elle l'est, on retourne son adresse, si elle ne l'est pas, on l'ajoute et l'on retourne son adresse
// On compare les hash
// le hash devrait il être calculé dans cette fonction directement?
uint_index VerifyCache(QuadTreeNode nod) {
    if ( nod.layer > size_cache ) {//   The node is bigger than any node contained in the cache
    //  we extend the cache, by adding zero-nodes to it
        CreateZeros(nod.layer);
    //  we add the node to the cache
        cache[nod.layer] = (QuadTreeNode*)realloc(cache[nod.layer], 2*sizeof(QuadTreeNode));
        cache[nod.layer][1] = nod; 

        dimensions_cache[nod.layer] = 2;
    //  return the address of the node, in the cache
        return( 1 );
    }
    // In this implementation, the cache is not sorted
    for (uint_index i = 0 ; i < dimensions_cache[nod.layer] ; i ++) {
        if ( cache[nod.layer][i].NorthWest_index == nod.NorthWest_index && 
        cache[nod.layer][i].NorthEast_index == nod.NorthEast_index && 
        cache[nod.layer][i].SouthWest_index == nod.SouthWest_index && 
        cache[nod.layer][i].SouthEast_index == nod.SouthEast_index ) {// we found the node in the cache
        //  return the index of the node in the cache
            return ( i );
        }
    }
    // we didn't find the node in the cache

    // extend the cache
    cache[nod.layer] = (QuadTreeNode*) realloc(cache[nod.layer] , (dimensions_cache[nod.layer] + 1) * sizeof(QuadTreeNode));
    // add the node to the cache
    cache[ nod.layer ][ dimensions_cache[nod.layer] ] = nod;
    // update the cache size
    dimensions_cache[nod.layer] += 1;

    // return the address of the node, newly added to the cache
    return ( dimensions_cache[nod.layer] - 1 );
}

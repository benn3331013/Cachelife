#include "cachelife.h"

uint_layer size_cache = 0;
u32* dimensions_cache = NULL;
QuadTreeNode** cache = NULL;
mpz_t iteration_counter;
uint_layer root_layer = -1;
uint_index root_index = -1;

int InitCachelife(void) {
    //  This can be modified. It is set to 255 to avoid any realloc.
    size_cache = 255;
    cache = (QuadTreeNode**) malloc(size_cache*sizeof(QuadTreeNode*));
//  TODO : log debug?
//  assert (cache != NULL);
    if (cache == NULL) {
        printf("Error when allocating memory for the cache... Aborting.\n");
        return -1;
    }

    dimensions_cache = (uint_index*) calloc(size_cache, sizeof(uint_index));
    if (dimensions_cache == NULL) {
        printf("Error when allocating memory for the dimensions of the cache... Aborting.\n");
        free(cache);
        return -1;
    }

    for (uint_layer i=1; i<size_cache; i++) {
        cache[i] = NULL;
        dimensions_cache[i] = 0;
    }

    dimensions_cache[0] = 2;
    cache[0] = (QuadTreeNode*) malloc(2*sizeof(QuadTreeNode));
    // This corresponds to a dead cell
    cache[0][0].layer = 0;
    cache[0][0].NorthWest_index = 0;
    cache[0][0].NorthEast_index = 0;
    cache[0][0].SouthWest_index = 0;
    cache[0][0].SouthEast_index = 0;
    // This corresponds to a living cell
    cache[0][1].layer = 0;
    cache[0][1].NorthWest_index = 1;
    cache[0][1].NorthEast_index = 1;
    cache[0][1].SouthWest_index = 1;
    cache[0][1].SouthEast_index = 1;


    mpz_init_set_ui(iteration_counter, 0);

    return 0;
}

void QuitCachelife(void) {
    for (uint_layer i=0; i<size_cache; i++) {
        free(cache[i]);
    }
    free(cache);
    free(dimensions_cache);

	mpz_clear( iteration_counter );
}
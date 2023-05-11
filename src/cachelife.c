#include "cachelife.h"
#ifdef CACHELIFE_DISPLAY
#include "cachelife_display.h"
#ifdef CACHELIFE_SLOW
#include <unistd.h>
#endif
#endif

size_t PowerOf2(const uint_layer exp);
// {
//     return 1 << exp;
// }

SDL_Thread* thread_window = NULL;

void Cachelife(char* n_iterations_objective) {
    mpz_init_set_ui( iteration_counter, 0);
    mpz_t n_objective;
    mpz_init_set_str(n_objective, n_iterations_objective, 10);


    #ifdef CACHELIFE_DISPLAY
    uint_layer last_layer = root_layer;
    RenderNodes(root_index, root_layer, x_minimum, y_minimum);
    #ifdef CACHELIFE_SLOW
    sleep(1);
    #endif 
    thread_window = SDL_CreateThread(SDLWindowThread, "Window Thread", cachelife_window);
    #endif
//  TODO exception when empty node

    mpz_t mpz_2;
    mpz_init_set_ui(mpz_2, 2);
    // mpz_t mpz_1;
    // mpz_init_set_ui(mpz_1, 1);

    mpz_t tempo;
    mpz_init(tempo);

    while ( mpz_cmp(iteration_counter, n_objective) < 0 ) {
        root_index = Surround(cache[root_layer][root_index]);
        root_layer ++;
        // if ( root_index == -1 ) {
        //     printf("There was a problem...\n");
        //     exit(EXIT_FAILURE);
        // }

        root_index = Surround(cache[root_layer][root_index]);
        root_layer ++;
        // if ( root_index == -1 ) {
        //     printf("There was a problem...\n");
        //     exit(EXIT_FAILURE);
        // }

        root_index = Next(root_layer, root_index);
        root_layer -= 1;
        root_index = Crop( cache[root_layer][root_index], &root_layer );


    //  updating the iteration counter
        //  += 2**(initial_root_layer - 2)
        mpz_pow_ui( tempo , mpz_2 , root_layer - 1 );
        mpz_add( iteration_counter , iteration_counter , tempo );




    #ifdef CACHELIFE_DISPLAY
        if ( last_layer < root_layer ) {
            // the node increased in size
            x_minimum -= PowerOf2( last_layer - 1 );
            y_minimum -= PowerOf2( last_layer - 1 );
        }
        else if ( last_layer > root_layer ) {
            x_minimum += PowerOf2( last_layer - 1 ) - PowerOf2( root_layer - 1 );
            y_minimum += PowerOf2( last_layer - 1 ) - PowerOf2( root_layer - 1 );
        }
        last_layer = root_layer;

        RenderNodes(root_index, root_layer, x_minimum, y_minimum);

        #ifdef CACHELIFE_SLOW
        sleep(1);
        #endif
    #endif

    gmp_printf("iteration : %Zu/%Zu\n", iteration_counter, n_objective);

    }

	mpz_clear( tempo );
	mpz_clear( mpz_2 );

    
}
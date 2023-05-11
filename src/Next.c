#include "cachelife.h"


uint_index Next( const uint_layer lay, const uint_index ind) {
    //  The successor has never been computed
//  TODO : there's a redundancy with the recursive calls with node1-9
    if ( cache[lay][ind].future_index == (uint_index) -1 ) {
        uint_index tempo;

        //  The base case of our recursion is the 4x4 node
        if ( lay <= 2 ) {
            //  TODO : comment?
            if ( lay == 2) {
                tempo = Next_4x4( cache[2][ind] );
                cache[2][ind].future_index = tempo;
            }
            else {
                printf("Trying to compute the successor for a %u layer node\n", lay);
                return -1;
            }
        }
        else {
        
            uint_layer lay_m_1 = (uint_layer) lay - 1;
            //  Computing the results for the 9 intermediate nodes
            uint_index node1 = cache[ lay ][ ind ].NorthWest_index;
            if ( cache[ lay_m_1][ node1].future_index == (uint_index) -1 ) {
                tempo = Next( lay_m_1, node1 );
                cache[ lay_m_1 ][ node1 ].future_index = tempo;
            }
            node1 = cache[ lay_m_1][ node1 ].future_index;

            uint_index node2 = Join( lay_m_1,
                cache[lay_m_1][cache[ lay ][ ind ].NorthWest_index ].NorthEast_index,
                cache[lay_m_1][cache[ lay ][ ind ].NorthEast_index ].NorthWest_index,
                cache[lay_m_1][cache[ lay ][ ind ].NorthWest_index ].SouthEast_index,
                cache[lay_m_1][cache[ lay ][ ind ].NorthEast_index ].SouthWest_index );
            if ( cache[ lay_m_1 ][ node2 ].future_index == (uint_index) -1 ) {
                tempo = Next( lay_m_1, node2 );
                cache[ lay_m_1 ][ node2 ].future_index = tempo;
            }
            node2 = cache[ lay_m_1][ node2 ].future_index;

            uint_index node3 = cache[ lay ][ ind ].NorthEast_index;
            if ( cache[ lay_m_1 ][ node3 ].future_index == (uint_index) -1 ) {
                tempo = Next( lay_m_1, node3 );
                cache[ lay_m_1 ][ node3 ].future_index = tempo;
            }
            node3 = cache[ lay_m_1][ node3 ].future_index;

            uint_index node4 = Join( lay_m_1,
                cache[lay_m_1][ cache[ lay ][ ind ].NorthWest_index ].SouthWest_index,
                cache[lay_m_1][ cache[ lay ][ ind ].NorthWest_index ].SouthEast_index,
                cache[lay_m_1][ cache[ lay ][ ind ].SouthWest_index ].NorthWest_index,
                cache[lay_m_1][ cache[ lay ][ ind ].SouthWest_index ].NorthEast_index );
            if ( cache[ lay_m_1 ][ node4 ].future_index == (uint_index) -1 ) {
                tempo = Next( lay_m_1, node4 );
                cache[ lay_m_1 ][ node4 ].future_index = tempo;
            }
            node4 = cache[ lay_m_1][ node4 ].future_index;

            uint_index node5 = Join( lay_m_1,
                cache[lay_m_1][ cache[ lay ][ ind ].NorthWest_index ].SouthEast_index,
                cache[lay_m_1][ cache[ lay ][ ind ].NorthEast_index ].SouthWest_index,
                cache[lay_m_1][ cache[ lay ][ ind ].SouthWest_index ].NorthEast_index,
                cache[lay_m_1][ cache[ lay ][ ind ].SouthEast_index ].NorthWest_index );
            if ( cache[ lay_m_1 ][ node5 ].future_index == (uint_index) -1 ) {
                tempo = Next( lay_m_1, node5 );
                cache[ lay_m_1 ][ node5 ].future_index = tempo;
            }
            node5 = cache[ lay_m_1][ node5 ].future_index;

            uint_index node6 = Join( lay_m_1,
                cache[lay_m_1][ cache[ lay ][ ind ].NorthEast_index ].SouthWest_index,
                cache[lay_m_1][ cache[ lay ][ ind ].NorthEast_index ].SouthEast_index,
                cache[lay_m_1][ cache[ lay ][ ind ].SouthEast_index ].NorthWest_index,
                cache[lay_m_1][ cache[ lay ][ ind ].SouthEast_index ].NorthEast_index );
            if ( cache[ lay_m_1 ][ node6 ].future_index == (uint_index) -1 ) {
                tempo = Next( lay_m_1, node6 );
                cache[ lay_m_1 ][ node6 ].future_index = tempo;
            }
            node6 = cache[ lay_m_1][ node6 ].future_index;

            uint_index node7 = cache[ lay ][ ind ].SouthWest_index;
            if ( cache[ lay_m_1][ node7 ].future_index == (uint_index) -1 ) {
                tempo = Next( lay_m_1, node7 );
                cache[ lay_m_1 ][ node7 ].future_index = tempo;
            }
            node7 = cache[ lay_m_1][ node7 ].future_index;

            uint_index node8 = Join( lay_m_1,
                cache[lay_m_1][cache[ lay ][ ind ].SouthWest_index ].NorthEast_index,
                cache[lay_m_1][cache[ lay ][ ind ].SouthEast_index ].NorthWest_index,
                cache[lay_m_1][cache[ lay ][ ind ].SouthWest_index ].SouthEast_index,
                cache[lay_m_1][cache[ lay ][ ind ].SouthEast_index ].SouthWest_index );
            if ( cache[ lay_m_1][ node8 ].future_index == (uint_index) -1 ) {
                tempo = Next( lay_m_1, node8 );
                cache[ lay_m_1 ][ node8 ].future_index = tempo;
            }
            node8 = cache[ lay_m_1][ node8 ].future_index;

            uint_index node9 = cache[ lay ][ ind ].SouthEast_index;
            if ( cache[ lay_m_1][ node9 ].future_index == (uint_index) -1 ) {
                tempo = Next( lay_m_1, node9 );
                cache[ lay_m_1 ][ node9 ].future_index = tempo;
            }
            node9 = cache[ lay_m_1][ node9].future_index;

    // ######################################################################################################
            node1 = Join( lay_m_1 , node1, node2, node4, node5);
            node1 = Next( lay_m_1 , node1 );
            node3 = Join( lay_m_1 , node2, node3, node5, node6);
            node3 = Next( lay_m_1 , node3 );
            node7 = Join( lay_m_1 , node4, node5, node7, node8);
            node7 = Next( lay_m_1 , node7 );
            node9 = Join( lay_m_1 , node5, node6, node8, node9);
            node9 = Next( lay_m_1 , node9 );
            tempo = Join( lay_m_1 , node1, node3, node7, node9 );
            cache[lay][ind].future_index = tempo;
    //  The double recursion allows to get the successor 2**(k-2) iterations deep
    //  By taking advantage of the rules of the game : of the space between 2**k -1 and 2**(k-1)
        }
    }
    return cache[lay][ind].future_index;
}

#include "cachelife.h"


uint_index Surround(QuadTreeNode root) {
    // TODO : would this break the program, in case of empty grid? 
//    assert(root.layer != 0);
    if ( root.layer != 0 ) {
        QuadTreeNode final_node;
        final_node.layer = root.layer + 1;

        QuadTreeNode filler_node;
        filler_node.layer = root.layer ;
        filler_node.future_index = -1;// unsigned -1
        filler_node.NorthWest_index = 0 ;// 0s are always in 0th position in the cache
        filler_node.NorthEast_index = 0 ;
        filler_node.SouthWest_index = 0 ;

    //  Up Left quarter : North West
        filler_node.SouthEast_index = root.NorthWest_index;
        final_node.NorthWest_index = VerifyCache(filler_node);
        filler_node.SouthEast_index = 0;

    //  Up RIght quarter : North East
        filler_node.SouthWest_index = root.NorthEast_index;
        final_node.NorthEast_index = VerifyCache(filler_node);
        filler_node.SouthWest_index = 0;
        
    //  Down Left quarter : South West
        filler_node.NorthEast_index = root.SouthWest_index;
        final_node.SouthWest_index = VerifyCache(filler_node);
        filler_node.NorthEast_index = 0;
        
    //  Down Right quarter : South East
        filler_node.NorthWest_index = root.SouthEast_index;
        final_node.SouthEast_index = VerifyCache(filler_node);

        final_node.future_index = -1;// unsigned -1 
        return VerifyCache(final_node);
    }
    else {
        printf("Error : surrounding a layer 0 node\n");
        return -1;
    }
}
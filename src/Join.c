#include "cachelife.h"


uint_index Join(const uint_layer lay, const uint_index a, const uint_index b, const uint_index c, const uint_index d) {
    QuadTreeNode retour;
    retour.layer =  lay ;
    retour.future_index = -1;// -1 en unsigned
    retour.NorthWest_index = a;
    retour.NorthEast_index = b;
    retour.SouthWest_index = c;
    retour.SouthEast_index = d;
    
    return VerifyCache(retour);
}
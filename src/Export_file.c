#include "cachelife.h"

inline size_t _PowerOf2(const uint_layer exp) {
    return 1<<exp;
}


void Export_file_subfunction(FILE* export_f, uint_layer lay, uint_index nod, const i64 x, const i64 y) {
    if (lay == 0) {
        if ( nod == 1 ) {
            fprintf(export_f, "%zd, %zd\n", x, y );
        }
    }
    else {
        if (nod != 0) {
            const size_t p2_offset = _PowerOf2(lay-1);
            Export_file_subfunction( export_f, lay-1, cache[lay][nod].NorthWest_index , x , y );
            Export_file_subfunction( export_f, lay-1, cache[lay][nod].NorthEast_index , x + p2_offset , y );
            Export_file_subfunction( export_f, lay-1, cache[lay][nod].SouthWest_index , x, y + p2_offset );
            Export_file_subfunction( export_f, lay-1, cache[lay][nod].SouthEast_index , x + p2_offset , y + p2_offset);
        }
    }
}

void Export_file(char* filename) {
    FILE* target_file = fopen(filename, "w");
    if (target_file == NULL) {
        printf("can't open %s...\n", filename); 
        return;
    }

    Export_file_subfunction(target_file, root_layer, root_index, x_minimum, y_minimum);
    fclose(target_file);
    
}
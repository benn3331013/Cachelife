#include "cachelife.h"

void CachelifeSet_file(char* filename) {
    FILE* opened_file = fopen(filename, "r");
    if (opened_file == NULL) {
        printf("error : Can't open the file %s\n", filename);
    }
    size_t len;
    fscanf(opened_file, "len=%lu\n", &len );

    i64* x_pos = (i64*) malloc(len*sizeof(i64));
    i64* y_pos = (i64*) malloc(len*sizeof(i64));
    for (size_t i = 0 ; i < len ; i++ ) {
        fscanf(opened_file, "%lu,%lu\n", (i64*) x_pos+i, (i64*) y_pos+i );
    }
    fclose(opened_file);


    CachelifeSet_array(len, x_pos, y_pos);
    free(x_pos);
    free(y_pos);

}
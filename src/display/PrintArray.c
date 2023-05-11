#include "cachelife_display.h"

void PrintArray(const size_t len, i64* x_positions, i64* y_positions) {
    for (int i = 0 ; i < len ; i++) {
        printf("(%zd, %zd)\n", x_positions[i], y_positions[i]);
    }
}
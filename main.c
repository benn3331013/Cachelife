#include "cachelife.h"
#include <string.h>
#ifdef CACHELIFE_DISPLAY
#include "cachelife_display.h"
#endif


int main(int argc, char** argv) {
    char limit[201] = "";
    char filename[51] = "";
    char filename_export[51] = "";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Usage: %s [OPTIONS]\n", argv[0]);
            printf("\t-h, --help\tPrint this help message and exit\n");
            printf("\t-l, --limit\tSet the number of iterations (max 200 decimals). Default is 100.\n");
            printf("\t-f, --file\tSet the filename for the initial position (max 50 characters)\n");
            printf("\t-e, --export\tSet the filename for the export of the last position (max 50 characters)\n");
            exit(EXIT_SUCCESS);
        } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--limit") == 0) {
            i++;
            if (i >= argc) {
                printf("Error: Expected an integer after %s\n", argv[i-1]);
                exit(EXIT_FAILURE);
            }
            if (strlen(argv[i]) >= 200) {
                printf("Error: The maximum number of iteration should have at most 200 decimals.\n");
                printf("Why would you ever want more than that?\n");
                printf("Do you even realize how much 200 decimals is?\n");
                printf("You can go up to 99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999\n");
                printf("IT'S A LOT!\n");
                printf("Anyway, you can change that by changing the main.c file...\n");
                exit(EXIT_FAILURE);
            }
            strcpy(limit, argv[i]);
        } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
            i++;
            if (i >= argc) {
                printf("Error: Expected a filename after %s\n", argv[i-1]);
                exit(EXIT_FAILURE);
            }
            if (strlen(argv[i]) >= 50) {
                printf("Error: Filename is too long (max 50 characters)\n");
                exit(EXIT_FAILURE);
            }
            strcpy(filename, argv[i]);
        } else if (strcmp(argv[i], "-e") == 0 || strcmp(argv[i], "--export") == 0) {
            i++;
            if (i >= argc) {
                printf("Error: Expected a filename after %s\n", argv[i-1]);
                exit(EXIT_FAILURE);
            }
            if (strlen(argv[i]) >= 50) {
                printf("Error: Export filename is too long (max 50 characters)\n");
                exit(EXIT_FAILURE);
            }
            strcpy(filename_export, argv[i]);
        } else {
            printf("Error: Unknown option %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }


    if (0 != InitCachelife() ) {
        return -1;
    }
    #ifdef CACHELIFE_DISPLAY
    if ( 0 != InitCachelifeDisplay() ) {
        return -1;
    }
    #endif


    if (strcmp(limit, "") == 0) {
        strcpy(limit, "100");
    }

    if ( strcmp(filename, "") != 0 ) {
        CachelifeSet_file(filename);
    } else {
        i64 x_p[] = {15,16,17,17,17};
        i64 y_p[] = {16,17,15,16,17};
        CachelifeSet_array(5, x_p, y_p);
    }


    Cachelife(limit);

    // Save the reached position
    if (strcmp(filename_export, "") != 0) {
        Export_file(filename_export);
    }



    #ifdef CACHELIFE_DISPLAY
    int threadReturnValue;
    SDL_WaitThread(thread_window, &threadReturnValue);
    #endif
    QuitCachelife();
    #ifdef CACHELIFE_DISPLAY
    QuitCachelifeDisplay();
    #endif
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../dependency.h"
#include "../log.h"
#include "version.h"

int main(int argc, const char** argv) {
    if (argc == 1) {
        installAllDependencies();
    } else if(argc > 1) {
        if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) {
            printf("BoxCar v%d.%d.%d\n",
                   BOXCAR_VERSION_MAJOR,
                   BOXCAR_VERSION_MINOR,
                   BOXCAR_VERSION_PATCH);
            exit(0);
        } else if (strcmp(argv[1], "install") == 0) {
            if (argc == 2) installAllDependencies();
            else if (argc == 3);
            else {
                logErr("Too many arguments. Expected: 2, got: 3");
            }
        }
    }

    return 0;
}
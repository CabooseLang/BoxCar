#include <stdio.h>
#include "log.h"

void logErr(const char* message) {
    printf("[ERR] %s\n", message);
}

void logInf(const char* message) {
    printf("[\x1b[92mINF\x1b[0m] %s\n", message);
}

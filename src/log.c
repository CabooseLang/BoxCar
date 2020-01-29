#include <stdio.h>
#include "log.h"

void logErr(const char* message) {
    printf("[\x1b[31mERR\x1b[0m] %s\n", message);
}

void logInf(const char* message) {
    printf("[\x1b[32mINF\x1b[0m] %s\n", message);
}

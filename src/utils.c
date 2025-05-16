#include "../include/utils.h"

void log_print(int stat, char *msg) {
    if (!msg) return;

    if (stat < 0) { // (-) Failure Message...
        printf("%s(-)%s ", INVERSE, RESET);
        printf("%s%s%s\n", BRIGHT_RED, msg, RESET);
        return;
    }
    if (stat == 0) { // (*) Log Message...
        printf("%s(*) %s%s\n", DIM, msg, RESET);
        return;
    }
    // (+) Success Message...
    printf("%s(+)%s ", INVERSE, RESET);
    printf("%s%s%s\n\n", BRIGHT_GREEN, msg, RESET);
}

void log_sent(size_t bytes, const char *type, int code) {
    printf("%s--> Sent %zu bytes! [%s, %d]%s\n",
            DIM, bytes, type, code, RESET);
}

void log_read(size_t bytes) {
    printf("%s<-- Received Response! [%zu Bytes]%s\n",
        DIM, bytes, RESET);
}

void log_banner(char *msg, size_t len) {
    if (len > 40) return;

    printf("==");
    printf(" %s%s%s ", INVERSE, msg, RESET);
    for (size_t i = 0; i < (40 - (4 + len)); i++) {
        putchar('=');
    }
    printf("\n\n");
}

void log_site(__uint16_t port) {
    printf("%sSite is running at: %s%s%shttp://localhost:%u%s\n\n",
        BOLD, RESET, UNDERLINE , CYAN, port, RESET);
}
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
    printf("%s%s%s\n", GREEN, msg, RESET);
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

char *read_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + 1);
    if (!buffer) return NULL;

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    return buffer;
}

char *read_file_bin(const char *file_path, size_t *out_size) {
    FILE *file = fopen(file_path, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    *out_size = file_size;
    return buffer;
}
#ifndef HTTP_H
#define HTTP_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Function prototypes for request and response handling
char *parse_request(const char *request, size_t len);
char *build_response(int status_code, const char *con_type, const char *body);
char *build_response_bin(int code, const char *type, const char *body, size_t body_len, size_t *out_header_len);
const char *get_con_mime(const char * path);
int is_bin_mime(const char *type);

#endif
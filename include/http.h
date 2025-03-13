#ifndef HTTP_H
#define HTTP_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Function prototypes for request and response handling
char *parse_request(const char *request, size_t len);
char *build_response(int status_code, const char *body);

#endif

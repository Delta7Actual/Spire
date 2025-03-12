#ifndef HTTP_H
#define HTTP_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// Function prototypes for request and response handling
char *parse_request(const char *request, size_t len);
int  build_response(uint8_t status_code, const char *body, char *response_buffer);

#endif

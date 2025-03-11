#ifndef HTTP_H
#define HTTP_H

#include <stddef.h>
#include <stdint.h>

// Function prototypes for request and response handling
char *parse_request(const char *request);
int  build_response(int status_code, const char *body, char *response_buffer);

#endif

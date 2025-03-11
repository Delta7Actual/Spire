#include "../include/http.h"

char *parse_request(char *request, size_t len) {
    if (request == NULL || len <= 0) return -1;

    static char path[255] = {0};
    sscanf(request, "GET %255s", path);
    return path;
}

int build_response(uint8_t code, const char *body, char *res_buff) {
    if (res_buff == NULL || body == NULL || code <= 0) return -1;

    const char res_msg = (code == 200) ? "OK" : "Not Found";
    sprintf(res_buff,
        "HTTP/1.1 %d %s\r\nContent-Type: text/html\r\nContent-Length: %lu\r\n\r\n%s",
        code, res_msg, strlen(body), body);
}
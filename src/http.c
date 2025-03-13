#include "../include/http.h"

char *parse_request(const char *request, size_t len) {
    if (request == NULL || len <= 0) return NULL;

    static char path[255] = {0};
    sscanf(request, "GET %255s", path);

    // Remove leading slash if it exists
    if (path[0] == '/') {
        memmove(path, path + 1, strlen(path));  // Shift the string to remove the slash
    }

    return path;
}

char *build_response(int code, const char *body) {
    if (!body || code <= 0) return NULL;

    const char *res_msg = (code == 200) ? "OK" : "Not Found";
    size_t res_len = strlen("HTTP/1.1 ") + 3 + strlen(res_msg) + strlen("\r\nContent-Type: text/html\r\nContent-Length: ") + 10 + strlen("\r\n\r\n") + strlen(body);

    char *res_buff = malloc(res_len + 1);
    if (!res_buff) return NULL;

    snprintf(res_buff,
        res_len + 1,
        "HTTP/1.1 %d %s\r\nContent-Type: text/html\r\nContent-Length: %lu\r\n\r\n%s",
        code, res_msg, strlen(body), body);

    return res_buff;
}

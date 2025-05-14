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
    const char *header_fmt =
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s";

    // Calculate actual length needed
    size_t body_len = strlen(body);
    size_t header_len = snprintf(NULL, 0, header_fmt, code, res_msg, body_len, body);

    char *res_buff = malloc(header_len + 1);
    if (!res_buff) return NULL;

    snprintf(res_buff, header_len + 1, header_fmt, code, res_msg, body_len, body);
    return res_buff;
}
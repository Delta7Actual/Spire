#include "../include/http.h"

char *parse_request(const char *request, size_t len) {
    if (request == NULL || len <= 0) return NULL;

    static char path[255] = {0};
    sscanf(request, "GET %255s", path);
    return path;
}

char *build_response(int code, const char *con_type, const char *body) {
    if (!body || !con_type || code <= 0) return NULL;

    const char *res_msg = (code == 200) ? "OK" : "Not Found";
    const char *header_fmt =
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s";

    // Calculate actual length needed
    size_t body_len = strlen(body);
    size_t header_len = snprintf(NULL, 0, header_fmt, code, res_msg, con_type, body_len, body);

    char *res_buff = malloc(header_len + 1);
    if (!res_buff) return NULL;

    snprintf(res_buff, header_len + 1, header_fmt, code, res_msg, con_type, body_len, body);
    return res_buff;
}

const char *get_con_type(const char *path) {
    if (!path) return "text/plain";

    const char *ext = strrchr(path, '.');
    if (!ext) return "text/plain";

    if (strcmp(ext, ".html") == 0) return "text/html";
    if (strcmp(ext, ".css") == 0) return "text/css";

    return "text/plain"; // Add other types.
}
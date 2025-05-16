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

char *build_response_bin(int code, const char *type, const char *body, size_t body_len, size_t *out_header_len) {
    char header[512];
    const char *msg = (code == 200) ? "OK" : "Not Found";

    int hlen = snprintf(header, sizeof(header),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "\r\n",
        code, msg, type, body_len);

    char *response = malloc(hlen + body_len);
    if (!response) return NULL;

    memcpy(response, header, hlen);
    memcpy(response + hlen, body, body_len);
    *out_header_len = hlen;
    return response;
}

const char *get_con_mime(const char *path) {
    if (!path) return "text/plain";

    const char *ext = strrchr(path, '.');
    if (!ext) return "text/plain";

    if (strcmp(ext, ".html") == 0) return "text/html";
    if (strcmp(ext, ".css")  == 0) return "text/css";
    if (strcmp(ext, ".js")   == 0) return "application/javascript";
    if (strcmp(ext, ".png")  == 0) return "image/png";
    if (strcmp(ext, ".jpg")  == 0 || strcmp(ext, ".jpeg") == 0) return "image/jpeg";

    return "application/octet-stream";
}

int is_bin_mime(const char *mime) {
    return strncmp(mime, "image/", 6) == 0
        || strcmp(mime, "application/octet-stream") == 0
        || strcmp(mime, "application/javascript")   == 0;
}
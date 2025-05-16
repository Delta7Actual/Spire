#include "../include/core.h"

int app_launch(App *app) {
    if (!app || app->p_count <= 0 || !app->pages || app->port <= 5000) return -1;

    log_print(0, "Starting app...\n");

    int server = open_conn(app->port);
    if (server < 0) return -1;

    log_banner("SERVER START", 12);
    log_site(app->port);

    printf("%sAvailable pages:%s\n", BOLD, RESET);
    for (int i = 0; i < app->p_count; i++) {
        printf("  - http://localhost:%u/%s\n", app->port, app->pages[i].title);
    }
    printf("\n========================================\n\n");

    while (1) {
        Conn *conn = connect_conn(server);
        if (!conn) continue;

        char buff[1024] = {0};
        int rb = recv(conn->client_sock, buff, sizeof(buff) - 1, 0);
        if (rb <= 0) {
            cycle_client(conn);
            continue;
        }

        buff[rb] = '\0';
        log_read(strlen(buff));
        char *path = parse_request(buff, rb);

        char file_path[256] = {0};
        int found = 0;
        char *body = NULL;
        size_t body_len = 0;
        const char *content_type = NULL;
        int code = 404;

        // Look for HTML page match
        for (int i = 0; i < app->p_count; i++) {
            if (strncmp(app->pages[i].title, path + 1, strlen(app->pages[i].title)) == 0) {
                snprintf(file_path, sizeof(file_path), "%s", app->pages[i].path);
                found = 1;
                break;
            }
        }

        // Static file fallback (CSS, PNG, etc.)
        if (!found) {
            snprintf(file_path, sizeof(file_path), ".%s", path);
            found = access(file_path, F_OK) == 0;
        }

        if (found) {
            content_type = get_con_mime(file_path);

            if (is_bin_mime(content_type)) {
                body = read_file_bin(file_path, &body_len);
            } else {
                body = read_file(file_path);
                if (body) body_len = strlen(body);
            }

            if (body) {
                code = 200;
            } else {
                found = 0; // fallback to 404
            }
        }

        if (!found) {
            body = "<h1 style=\"text-align:center\">404 Not Found</h1>";
            body_len = strlen(body);
            content_type = "text/html";
        }

        size_t header_len = 0;
        char *response = build_response_bin(code, content_type, body, body_len, &header_len);
        if (response) {
            ssize_t sent = send(conn->client_sock, response, header_len + body_len, 0);
            log_sent(sent, content_type, code);

            if (found && body) free(body);
            free(response);
        }

        cycle_client(conn);
    }

    close_conn(server);
    return 0;
}
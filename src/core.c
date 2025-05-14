#include "../include/core.h"

int app_launch(App *app) {
    if (!app || app->p_count <= 0 || !app->pages || app->port <= 5000) return -1;

    printf("(*) Starting app...\n");

    int server = open_conn(app->port);
    if (server < 0) return -1;

    printf("=========================\n%s%d%s\n=========================\n"
        , "Site up on: http://localhost:", app->port, "/{Page_Name}!");
    
    printf("Available pages:\n-------------------------\n");
    for (int i = 0; i < app->p_count; i++) {
        printf("%d. %s%d/%s\n-------------------------\n\n\n"
            , i+1, "http://localhost:", app->port, app->pages[i].title);
    }

    while (1) {
        Conn *conn = connect_conn(server);
        if (!conn) continue;

        char buff[1024] = {0};
        int rb = recv(conn->client_sock, buff, sizeof(buff)-1, 0);
        if (rb <= 0) {
            cycle_client(conn);
            continue;
        }

        buff[rb] = '\0';
        printf("Received data! :\n%s\n", buff);
        char *path = parse_request(buff, rb);

        char file_path[256] = {0};
        char *body = NULL;
        int found = 0;

        for (int i = 0; i < app->p_count; i++) { // Search HTML files
            // Skipping the slash
            if (strncmp(app->pages[i].title, path + 1, strlen(app->pages[i].title)) == 0) {
                snprintf(file_path, sizeof(file_path), "%s", app->pages[i].path);
                found = 1;
                break;
            }
        }

        if (!found) { // Search CSS files
            snprintf(file_path, sizeof(file_path), ".%s", path); // keep the slash
            found = access(file_path, F_OK) == 0;
        } 

        if (found) {
            printf("Resolved file path: %s\n", file_path);
            body = read_file(file_path);
            if (!body) found = 0;
        }

        int code = 404;
        const char *content_type = "text/html";

        if (found) {
            body = read_file(file_path);
            if (!body) {
                found = 0;
            } else {
                content_type = get_con_type(file_path);
                code = 200;
            }
        }

        if (!found) {
            body = "<h1 style=\"text-align:center\">404 Not Found</h1>";
            content_type = "text/html";
        }

        printf("FOUND: %d | LOOKED FOR: %s\n", found, path);
        printf("Sending... MIME: %s | CODE: %d | PATH: %s\n", content_type, code, path);

        char *response = build_response(code, content_type, body);
        if (response) {
            ssize_t sent = send(conn->client_sock, response, strlen(response), 0);
            printf("Sent %zd bytes\n", sent);
            if (found && body) free(body);
            free(response);
        }

        cycle_client(conn);
    }

    close_conn(server);
    return 0;
}
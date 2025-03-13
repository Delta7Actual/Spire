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
        if (!conn) break;

        char buff[1024] = {0};
        int rb = recv(conn->client_sock, buff, sizeof(buff)-1, 0);
        if (rb <= 0) {
            close_conn(conn);
            break;
        }

        buff[rb] = '\0';
        printf("Received data! :\n%s\n", buff);
        char *path = parse_request(buff, rb);

        int code = 404;
        char *body = "<h1>404 Page not found!</h1>";

        int found = 0;
        for (int i = 0; i < app->p_count; i++) {
            if (strncmp(app->pages[i].title, path, strlen(app->pages[i].title)) == 0) {
                found = 1;
                body = read_file(app->pages[i].path);
                break;
            }
        }

        printf("FOUND: %d | LOOKED FOR: %s\n", found, path);
        if (found) code = 200;

        char *response = build_response(code, body);
        if (response) {
            send(conn->client_sock, response, strlen(response), 0);
            if (found) free(body);
            free(response);
        }

        close_conn(conn);
    }

    return 0;
}
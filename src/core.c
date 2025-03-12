#include "../include/core.h"

int app_launch(App *app) {
    if (app == NULL || app->p_count <= 0 || app->pages == NULL || app->port <= 5000) return -1;

    int server = open_conn(app->port);
    if (server < 0) return -1;
    printf("%s%d\n", "Site up on: http://localhost:", app->port);

    while (1) {
        Conn *conn = connect_conn(server);
        if (conn == NULL) continue;

        char buff[1024] = {0};
        int rb = recv(conn->client_sock, buff, sizeof(buff)-1, 0);
        if (rb <= 0) {
            close_conn(conn);
            continue;
        }

        buff[rb] = '\0';
        printf("Received data! :\n%s\n", buff);
        char *path = parse_request(buff, rb);

        int res_msg = 404;
        char *res_body = "<h1>404 NOT FOUND!</h1>";
        char res_buff[1024] = {0};

        if (path != NULL) {
            res_msg = 200;
            res_body = "<h1>200 OK!</h1>\n<h2>Hello from server!</h2>";
        }

        if (build_response(res_msg, res_body, res_buff) < 0) {
            close_conn(conn);
            continue;
        }
        printf("Sending response!\n%s\n", res_buff);
        send(conn->client_sock, res_buff, strlen(res_buff), 0);
        close_conn(conn);
    }
}
#include "server.h"

typedef struct s_app {
    char *title;
    char *path;
    uint16_t port;
} App;

char *html_s(const char *title);
char *html_e();

int app_launch(uint16_t port);
#include "server.h"
#include "http.h"
#include "utils.h"
#include "builder.h"

#include <stdio.h>

typedef struct s_app {
    Page *pages;
    uint8_t p_count;
    uint16_t port;
} App;

char *html_s(const char *title);
char *html_e();

int app_launch(App *app);
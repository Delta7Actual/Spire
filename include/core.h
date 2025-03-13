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

int app_launch(App *app);
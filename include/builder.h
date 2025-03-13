#ifndef addER_H
#define addER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

typedef struct s_page {
    char *title;
    char *path;
    char *body;
} Page;

// typedef struct s_heading {
//     uint8_t mag;
//     char *content;
// } Heading;

// typedef struct s_div {
//     char *content;
// } Div;

// typedef struct s_anchor {
//     char *url;
//     char *content;
// } Anchor;

Page *page_init(const char *title);
int page_render(Page *page);

int add_heading(Page *page, uint8_t mag, const char *content);
int add_div(Page *page, const char *content);
int add_anchor(Page *page, const char *url, const char *content);

char *read_file(const char *file_path);

#endif
#ifndef BUILDER_H
#define BUILDER_H

#include "utils.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

typedef struct s_page {
    char *title;
    char *path;
    char *body;
    char *style; // This is optional
} Page;

Page *page_init(const char *title, const char *style);
int page_render(Page *page);

int add_heading(Page *page, uint8_t mag, const char *content);
int add_div(Page *page, const char *content);
int add_anchor(Page *page, const char *url, const char *content);
int add_button(Page *page, const char *onclick, const char *content);
int add_paragraph(Page *page, const char *content);
int add_image(Page *page, const char *src, const char *alt, uint16_t width, uint16_t height);

// Add more elements

#endif
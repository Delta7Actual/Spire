#include "../include/builder.h"

// Util method to append element
static int append_element(Page *page, const char *element) {
    size_t new_body_len = strlen(page->body) + strlen(element) + 1;

    page->body = realloc(page->body, new_body_len);
    if (!page->body) return -1;

    strcat(page->body, element);

    return 0;
}

Page *page_init(const char *title, const char *style) {
    if (!title) return NULL;
    
    Page *page = malloc(sizeof(Page));
    if (!page) return NULL;

    page->title = strdup(title);
    page->body = strdup("");
    if (style) { // eg. style -> public/style.css
        size_t path_len = strlen(style) + strlen("public/.css") + 1;
        page->style = malloc(path_len);
        if (!page->style) return NULL;
        snprintf(page->style, path_len, "public/%s.css", style);
    } else page-> style = strdup("");

    log_print(1, "Page created successfully!");
    return page;
}

int page_render(Page *page) {
    if (!page || !page->title) return -1;

    size_t path_len = strlen(page->title) + strlen("public/.html") + 1;
    page->path = malloc(path_len);
    if (!page->path) return -1;
    snprintf(page->path, path_len, "public/%s.html", page->title);

    FILE *output = fopen(page->path, "w");
    if (!output) return -1;

    if (!page->style) {
        fprintf(output,
            "<!DOCTYPE html>\n<html>\n<head>\n<title>%s</title>\n</head><body>\n%s\n</body>\n</html>", 
            page->title, page->body);
    } else {
        fprintf(output,
            "<!DOCTYPE html>\n<html>\n<head>\n<title>%s</title>\n<link rel=\"stylesheet\" href=\"%s\">\n</head><body>\n%s\n</body>\n</html>", 
            page->title, page->style, page->body);
    }

    fclose(output);

    log_print(1, "Page rendered successfully!");
    return 0;
}

int add_heading(Page *page, uint8_t mag, const char *content) {
    if (!page || !content || mag < 1 || mag > 6) return -1;
    log_print(0, "Building [Heading] ...");
    
    char heading[1024] = {0};
    snprintf(heading, sizeof(heading), "<h%d>%s</h%d>\n", mag, content, mag);

    return append_element(page, heading);
}

int add_div(Page *page, const char *content) {
    if (!page || !content) return -1;
    log_print(0, "Building [Division] ...");

    char div[1024] = {0};
    snprintf(div, sizeof(div), "<div>%s</div>\n", content);

    return append_element(page, div);
}

int add_anchor(Page *page, const char *url, const char *content) {
    if (!page || !url || !content) return -1;
    log_print(0, "Building [anchor] ...");

    char anchor[1024] = {0};
    snprintf(anchor, sizeof(anchor), "<a href=\"%s\">%s</a>\n", url, content);

    return append_element(page, anchor);
}

int add_button(Page *page, const char *onclick, const char *content) {
    if (!page || !content) return -1;
    log_print(0, "Building [Button] ...");

    char button[1024] = {0};
    if (onclick) {
        snprintf(button, sizeof(button), "<button onclick=\"%s\">%s</button>\n",
            onclick, content);
    } else {
        snprintf(button, sizeof(button), "<button>%s</button>\n", content);
    }
    
    return append_element(page, button);
}

int add_paragraph(Page *page, const char *content) {
    if (!page || !content) return -1;
    log_print(0, "Building [Paragraph] ...");

    char paragraph[1024] = {0};
    snprintf(paragraph, sizeof(paragraph), "<p>%s</p>\n", content);

    return append_element(page, paragraph);
}

int add_image(Page *page, const char *src, const char *alt, uint16_t width, uint16_t height) {
    if (!page || !src) return -1;
    log_print(0, "Building [Image] ...");

    if (width > 1500 || height > 1500)
        log_print(-1, "[Warning] Image dimensions are very big!");
    if (width == 0 || height == 0)
        log_print(-1, "[Warning] Image dimensions are zero! (Image is not visible)");

    char image[1024] = {0};
    if (alt) {
        snprintf(image, sizeof(image), "<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"%s\">\n", 
            src, width, height, alt);
    } else {
        snprintf(image, sizeof(image), "<img src=\"%s\" width=\"%u\" height=\"%u\">\n", 
            src, width, height);
    }

    return append_element(page, image);
}
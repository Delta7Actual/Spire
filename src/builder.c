#include "../include/builder.h"

Page *page_init(const char *title) {
    if (!title) return NULL;
    printf("(*) Creating page...\n");
    
    Page *page = malloc(sizeof(Page));
    if (!page) return NULL;

    page->title = strdup(title);
    page->body = strdup("");

    printf("(+) Page created successfully!\n\n");
    return page;
}

int page_render(Page *page) {
    if (!page || !page->title) return -1;
    printf("(*) Rendering page...\n");

    size_t path_len = strlen(page->title) + strlen("public/.html") + 1;
    page->path = malloc(path_len);
    if (!page->path) return -1;
    snprintf(page->path, path_len, "public/%s.html", page->title);

    FILE *output = fopen(page->path, "w");
    if (!output) return -1;

    fprintf(output, "<!DOCTYPE html>\n<html>\n<head>\n<title>%s</title>\n</head><link rel=\"stylesheet\" href=\"public/styleSheet.css\">\n<body>\n%s\n</body>\n</html>", 
            page->title, page->body);

    printf("(+) Page rendered successfully and saved to: %s\n\n", page->path);
    fclose(output);
    return 0;
}

int add_heading(Page *page, uint8_t mag, const char *content) {
    if (!page || !content || mag < 1 || mag > 6) return -1;
    printf("(*) Building [heading] on page: %s...\n", page->title);
    
    char heading[1024];
    snprintf(heading, sizeof(heading), "<h%d>%s</h%d>", mag, content, mag);

    // Append
    size_t new_body_len = strlen(page->body) + strlen(heading) + 1;
    page->body = realloc(page->body, new_body_len);
    if (!page->body) return -1;
    strcat(page->body, heading);

    printf("(+) [heading] addition on page: %s successful!\n\n", page->title);
    return 0;
}

int add_div(Page *page, const char *content) {
    if (!page || !content) return -1;
    printf("(*) Building [div] on page: %s...\n", page->title);

    char div[1024];
    snprintf(div, sizeof(div), "<div>%s</div>", content);

    // Append
    size_t new_body_len = strlen(page->body) + strlen(div) + 1;
    page->body = realloc(page->body, new_body_len);
    if (!page->body) return -1;
    strcat(page->body, div);

    printf("(+) [div] addition on page: %s successful!\n\n", page->title);
    return 0;
}

int add_anchor(Page *page, const char *url, const char *content) {
    if (!page || !url || !content) return -1;
    printf("(*) Building [anchor] on page: %s...\n", page->title);

    char anchor[1024];
    snprintf(anchor, sizeof(anchor), "<a href=\"%s\">%s</a>", url, content);

    // Append
    size_t new_body_len = strlen(page->body) + strlen(anchor) + 1;
    page->body = realloc(page->body, new_body_len);
    if (!page->body) return -1;
    strcat(page->body, anchor);

    printf("(+) [anchor] addition on page: %s successful!\n\n", page->title);
    return 0;
}

char *read_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) return NULL;

    printf("(*) Reading file: %s...\n", file_path);

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + 1);
    if (!buffer) return NULL;

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    printf("(+) Reading from file: %s successful!\n\n", file_path);
    return buffer;
}
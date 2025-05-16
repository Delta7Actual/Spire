#include "../include/builder.h"

Page *page_init(const char *title, const char *style) {
    if (!title) return NULL;
    log_print(0, "Creating page..");
    
    Page *page = malloc(sizeof(Page));
    if (!page) return NULL;

    page->title = strdup(title);
    page->body = strdup("");
    page->style = style ? strdup(style) : NULL;

    return page;
}

int page_render(Page *page) {
    if (!page || !page->title) return -1;
    log_print(0, "Rendering page...");

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
    } else { // <link rel=\"stylesheet\" href=\"public/styleSheet.css\">\n
        fprintf(output,
            "<!DOCTYPE html>\n<html>\n<head>\n<title>%s</title>\n<link rel=\"stylesheet\" href=\"%s\">\n</head><body>\n%s\n</body>\n</html>", 
            page->title, page->style, page->body);
    }

    fclose(output);
    return 0;
}

int add_heading(Page *page, uint8_t mag, const char *content) {
    if (!page || !content || mag < 1 || mag > 6) return -1;
    log_print(0, "Building [heading]...");
    
    char heading[1024];
    snprintf(heading, sizeof(heading), "<h%d>%s</h%d>", mag, content, mag);

    // Append
    size_t new_body_len = strlen(page->body) + strlen(heading) + 1;
    page->body = realloc(page->body, new_body_len);
    if (!page->body) return -1;
    strcat(page->body, heading);

    return 0;
}

int add_div(Page *page, const char *content) {
    if (!page || !content) return -1;
    log_print(0, "Building [div]...");

    char div[1024];
    snprintf(div, sizeof(div), "<div>%s</div>", content);

    // Append
    size_t new_body_len = strlen(page->body) + strlen(div) + 1;
    page->body = realloc(page->body, new_body_len);
    if (!page->body) return -1;
    strcat(page->body, div);

    return 0;
}

int add_anchor(Page *page, const char *url, const char *content) {
    if (!page || !url || !content) return -1;
    log_print(0, "Building [anchor]...");

    char anchor[1024];
    snprintf(anchor, sizeof(anchor), "<a href=\"%s\">%s</a>", url, content);

    // Append
    size_t new_body_len = strlen(page->body) + strlen(anchor) + 1;
    page->body = realloc(page->body, new_body_len);
    if (!page->body) return -1;
    strcat(page->body, anchor);

    return 0;
}

char *read_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size + 1);
    if (!buffer) return NULL;

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    return buffer;
}
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include "../include/core.h"

int main(void) {
    printf("%s\n", "Hello world!");

    // Allocate memory for Page struct
    Page *page = (Page *)malloc(sizeof(Page));
    if (page == NULL) {
        printf("Failed to allocate memory for page\n");
        return 1; // Exit if memory allocation fails
    }

    // Allocate memory for the strings and assign values
    page->title = "TITLE";
    page->body = "<h1>BODY TEXT</h1>";
    page->path = "../skib.html";

    // Allocate memory for App struct
    App *app = (App *)malloc(sizeof(App));
    if (app == NULL) {
        printf("Failed to allocate memory for app\n");
        free(page); // Free the previously allocated memory for page
        return 1; // Exit if memory allocation fails
    }

    // Initialize app fields
    app->port = 55555;
    app->p_count = 1;
    app->pages = page;

    app_launch(app);

    // Clean up
    free(page); // Free the page memory
    free(app);  // Free the app memory

    return 0;
}
#include <stdio.h>

// Step 0: Include the core.h file
// Make sure the other h files are in the same directory
#include "../include/core.h"

int main() {
    // Step 1: Initialize the app
    App app = {0};
    app.port = 5500;
    app.p_count = 1;  // Number of pages
    app.pages = malloc(sizeof(Page) * app.p_count);
    if (!app.pages) {
        printf("(-) Failed to allocate memory for pages\n");
        return -1;
    }

    // Step 2: Create a page
    Page *page = page_init("index");  // Page title will be "index"
    if (!page) {
        printf("(-) Failed to initialize page\n");
        return -1;
    }

    // Step 3: Add content to the page
    add_heading(page, 1, "Welcome to My Website!");
    add_div(page, "This is a sample div with some content.");
    add_anchor(page, "/about", "About Us");

    // Step 4: Render the page to a file
    if (page_render(page) != 0) {
        printf("(-) Failed to render the page\n");
        return -1;
    }

    // Step 5: Initialize the app with the created page
    app.pages[0] = *page;  // Assign the page to the app

    // Step 6: Launch the app
    if (app_launch(&app) != 0) {
        printf("(-) Failed to launch the app\n");
        return -1;
    }

    // Step 7: Clean up
    free(page->title);
    free(page->body);
    free(page->path);
    free(page);
    free(app.pages);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "../include/builder.h"
#include "../include/core.h" // Step 0: Include the core header

int main() {
    // Step 1: Initialize the app
    App app = {0};
    app.port = 5500;
    app.p_count = 2;
    app.pages = malloc(sizeof(Page) * app.p_count);
    if (!app.pages) {
        printf("(-) Failed to allocate memory for pages\n");
        return -1;
    }

    // Step 2: Create pages
    Page *index = page_init("index", "public/style.css");
    Page *contact = page_init("contact", "public/contactstyle.css");

    if (!index || !contact) {
        printf("(-) Failed to initialize one or more pages\n");
        return -1;
    }

    // Step 3: Add content to "index" page
    add_heading(index, 1, "Welcome to DevBlog!");
    add_div(index, "This is the homepage of a fictional blog for developers.");
    add_anchor(index, "/contact", "Contact Us");

    // Step 4: Add content to "contact" page
    add_heading(contact, 2, "Get in Touch");
    add_div(contact, "Feel free to reach out to us at dev@blog.com.");
    add_anchor(contact, "/index", "Go Back Home");

    // Step 5: Render both pages
    if (page_render(index) != 0 || page_render(contact) != 0) {
        printf("(-) Failed to render one or more pages\n");
        return -1;
    }

    // Step 6: Add pages to the app
    app.pages[0] = *index;
    app.pages[1] = *contact;

    // Step 7: Launch app
    if (app_launch(&app) != 0) {
        printf("(-) Failed to launch the app\n");
        return -1;
    }

    // Step 8: Clean up
    free(index->title);
    free(index->path);
    free(index->body);
    free(index);

    free(contact->title);
    free(contact->path);
    free(contact->body);
    free(contact);

    free(app.pages);

    return 0;
}
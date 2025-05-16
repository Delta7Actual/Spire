# SPIRE - Web-Dev in C

A simple HTTP server in C that can serve static HTML files based on the user's request. This is designed to be a web-tool for C users, where they can create sites programmatically!

## Features
- Supports serving static HTML files.
- Supports multiple pages (you can add more pages in the configuration).
- Supports Divs, Headings and Anchors.

## Future
- Full CSS support.
- Expanded support for HTML elements.
- Dynamic site serving and processing.

## How to use this?
### 0. Include "core.h"
- The core functionality is defined in core.h, which includes all the functions, structures, and constants required to build and run the server.
- Make sure this header file is in the same directory as your source files.
- Example code:
```c
#include "../include/core.h"
```
### 1. Initialize the application
- Start by initializing the App structure.
- You'll need to set the desired port number, the number of pages you plan to serve, and allocate memory for the pages.
- Example code:
```c
    App app = {0};    // The App structure
    app.port = 55555; // The port the server will listen on
    app.p_count = 1;  // Number of pages
    app.pages = malloc(sizeof(Page) * app.p_count); // Allocate memory for pages
```
### 2. Initialize a page
- Now you can create a page by initializing a Page structure.
- Each page requires a title (e.g., "index" for the main page).
- Example code:
```c
    Page *page = page_init("index");  // Page title will be "index"
```
### 3. Add content to the page
- After we have created our page, we can add content to it in the form of HTML elements.
- (Expanded support for more elements will come in the future.
- Example code:
```c
    add_heading(page, 1, "Welcome to My Website!");           // Adding <h1> element with some text
    add_div(page, "This is a sample div with some content."); // Adding <div> element with some text
    add_anchor(page, "/about", "About Us");                   // Adding <a> element with some text and some link
```
### 4. Render the page and save it to a file
- Now we will translate our page into plain HTML and save it to a file.
- Make sure there is a directory called "public", the HTML files will go there.
- Example code:
```c
    render_page(page);
```
### 5. Anchor the page to the app
- After the page has been created and rendered it needs to be anchored to the App structure.
- Example code:
```c
    app.pages[0] = *page;  // Anchor the page to the app
```
### 6. Launch the app
- Now that we have our complete app we wll launch it!
- Example code:
```c
    app_launch(&app)
```
### Now the server will be listening on: https://localhost:{PortYouProvided}!

#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include <X11/Xlib.h>


int main() {
    Display *dpy;
    Window root;
    XEvent ev;

    dpy = XOpenDisplay(0);
    if (!dpy) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    root = DefaultRootWindow(dpy);

    // Attempt to become the window manager
    XSelectInput(dpy, root, SubstructureRedirectMask | SubstructureNotifyMask);
    XSync(dpy, False);

    printf("Simple window manager is running!\n");

    while (1) {
        XNextEvent(dpy, &ev);

        switch (ev.type) {
            case MapRequest: {
                // Get screen size (dimensions of the root window)
                XWindowAttributes attr;
                XGetWindowAttributes(dpy, root, &attr);
                int screen_width = attr.width - 12;
                int screen_height = attr.height - 12;

                // Move and resize the window to fill the screen
                XMoveResizeWindow(dpy, ev.xmaprequest.window, 6, 6, screen_width, screen_height);

                // Map (show) the window
                XMapWindow(dpy, ev.xmaprequest.window);
                break;
            }
            case ConfigureRequest: {
                XConfigureRequestEvent *cre = &ev.xconfigurerequest;
                XWindowChanges changes = {
                    .x = cre->x, .y = cre->y,
                    .width = cre->width, .height = cre->height,
                    .border_width = cre->border_width,
                    .sibling = cre->above, .stack_mode = cre->detail
                };
                XConfigureWindow(dpy, cre->window, cre->value_mask, &changes);
                break;
            }
        }
    }

    XCloseDisplay(dpy);
    return 0;
}

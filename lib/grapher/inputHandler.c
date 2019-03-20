#include "inputHandler.h"

char *text = NULL;

void processMouseWheel(SDL_MouseWheelEvent event);

void processEvents() {
    SDL_Event event;

    if (text == NULL) {
        text = malloc(sizeof(char) * 1024);
        text[0] = '\0';
    }

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
            case SDL_KEYDOWN:
                processKeyDown(event.key.keysym);
                break;
            case SDL_MOUSEMOTION:
                processMouseMotion(event.motion);
                break;
            case SDL_MOUSEBUTTONUP:
                processMousePress(event.button);
                break;
            case SDL_TEXTINPUT:
                strcat(text, event.text.text);
                log_info("%s", text);
                log_info("SDL_IsTextInputActive : %i", SDL_IsTextInputActive);
                break;
            case SDL_MOUSEWHEEL:
                processMouseWheel(event.wheel);
                break;
            default:
                break;
        }
    }
}

void processMouseWheel(SDL_MouseWheelEvent event) {
    if (event.y == -1) { // molette bas
        zoom();
    } else {
        unzoom();
    }

}

static void processMousePress(SDL_MouseButtonEvent key) {
}


static void processMouseMotion(SDL_MouseMotionEvent key) {

}


static void processKeyDown(SDL_Keysym key) {
    SDL_Keycode code = key.sym;

    switch (code) {
        case (97) : // A
            nbGradChange(-2);
            break;
        case (122): // Z
            nbGradChange(2);
            break;

    }


    log_info("Code : %i", code);
}
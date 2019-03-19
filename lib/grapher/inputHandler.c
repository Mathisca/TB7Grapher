
#include "inputHandler.h"

void processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                processKeyDown(event.key.keysym);
                break;
            case SDL_MOUSEMOTION:
                processMouseMotion(event.motion);
                break;
            case SDL_MOUSEBUTTONUP:
                processMousePress(event.button);
                break;
            default:
                break;
        }
    }
}

static void processMousePress(SDL_MouseButtonEvent key) {

}


static void processMouseMotion(SDL_MouseMotionEvent key) {

}


static void processKeyDown(SDL_Keysym key) {
    SDL_Keycode code = key.sym;
    log_info("Code : %i", code);
}
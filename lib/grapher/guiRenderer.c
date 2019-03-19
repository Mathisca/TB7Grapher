#include "guiRenderer.h"

void startMainLoop() {
    while(1) {
        processEvents();
        render();
    }
}


void render() {
    SDL_Renderer *renderer = getRenderer();

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine(renderer, 100, 200, 300, 500);

    SDL_RenderPresent(renderer);
}
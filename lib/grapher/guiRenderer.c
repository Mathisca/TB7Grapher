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
    SDL_RenderDrawLine(renderer, 512, 0, 512, 800);

    SDL_RenderPresent(renderer);
}
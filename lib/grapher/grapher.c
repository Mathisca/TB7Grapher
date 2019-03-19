#include "grapher.h"





void plotFunction(Entity n, double begin, double end, double step) {
    initGraphics();


    while(1) {
        SDL_Renderer *renderer = getRenderer();

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

    }

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                             "Missing file",
                             "File is missing. Please reinstall the program.",
                             NULL);
}

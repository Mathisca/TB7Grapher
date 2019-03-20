#include <pthread.h>
#include "guiManager.h"

static SDL_Renderer *gRenderer = NULL;

void startUserInterface() {
    initGraphics();

    pthread_t thread1;
    pthread_create(&thread1, NULL, startMainLoop, NULL);

    SDL_Delay(1000);
    addEntity(syntaxBuild(createMockListTrue()), "sin((2*x)+5)");

    SDL_Delay(1000);
    addEntity(syntaxBuild(createMockListTrue3()), "-tan(-x+2.5)*1.45");

    SDL_Delay(1000);
    addEntity(syntaxBuild(createMockListTrue6()), "tanh(x)");

    while(1) {


    }

}

/**
 * Initialise les libs SDL
 */

static int initSDL() {
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0) {
        log_error("Impossible de charger SDL : %s", SDL_GetError());
        return 0;
    }
    if (TTF_Init() < 0) {
        log_error("Impossible de charger l'extension TTF : %s", TTF_GetError());
        return 0;
    }
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        log_error("Impossible de charger l'extension IMG : %s", IMG_GetError());
        return 0;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    return 1;
}

/**
 * Création de la fenêtre SDL
 */
static int createWindow() {
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    gWindow = SDL_CreateWindow("TB7Plotter",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               DM.w, DM.h, SDL_WINDOW_SHOWN);

    if (gWindow == NULL) {
        log_error("Impossible de créer la fenêtre : %s\n", SDL_GetError());
        return 0;
    }
    SDL_SetWindowResizable(gWindow, SDL_TRUE);

    return 1;
}

/**
 * Création du renderer SDL
 */
static int createRenderer() {
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);

    if (gRenderer == NULL) {
        log_error("Impossible de créer le renderer : %s\n", SDL_GetError());
        return 0;
    }
    SDL_SetRenderDrawBlendMode(getRenderer(), SDL_BLENDMODE_BLEND);

    return 1;
}

void getWindowWidth(int *w, int *h) {
    SDL_GetWindowSize(gWindow, w, h);
}

SDL_Renderer *getRenderer() {
    return gRenderer;
}

void freeGraphics() {
    if (gWindow != NULL) { // Les ressources seront libérées automatiquement
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }
}

/**
 * Initialise la SDL et les fenêtres
 * @return réussi
 */
int initGraphics() {
    if (!initSDL() || !createWindow() || !createRenderer())
        return 0;
    return 1;
}

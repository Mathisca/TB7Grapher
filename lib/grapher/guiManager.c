#include <pthread.h>
#include "guiManager.h"

static SDL_Renderer *gRenderer = NULL;
static SDL_Window *gWindow;

/**
 * Starts user interface
 */
void startUserInterface() {
    if(!initGraphics()) {
        exit(1);
    }

    // Thread that manages the rendering
    pthread_t thread1;
    pthread_create(&thread1, NULL, startMainLoop, NULL);

    // La console reste sur le thread principal
    processConsoleInstructions();
}

/**
 * Initialize SDL and the window
 * @return success
 */
int initGraphics() {
    if (!initSDL() || !createWindow() || !createRenderer())
        return 0;
    return 1;
}

/**
 * Initialize SDL and SDL libs
 */
static int initSDL() {
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Impossible de charger SDL : %s", SDL_GetError());
        return 0;
    }
    if (TTF_Init() < 0) {
        fprintf(stderr, "Impossible de charger l'extension TTF : %s", TTF_GetError());
        return 0;
    }
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        fprintf(stderr, "Impossible de charger l'extension IMG : %s", IMG_GetError());
        return 0;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    return 1;
}

/**
 * Creates SDL window
 */
static int createWindow() {
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    gWindow = SDL_CreateWindow("TB7Plotter",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               DM.w, DM.h, SDL_WINDOW_SHOWN);

    if (gWindow == NULL) {
        fprintf(stderr, "Impossible de créer la fenêtre : %s\n", SDL_GetError());
        return 0;
    }

    SDL_SetWindowResizable(gWindow, SDL_TRUE);

    return 1;
}

/**
 * Creates SDL renderer
 */
static int createRenderer() {
    // SDL_RENDERER_PRESENTVSYNC to cap at 60 fps
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);

    if (gRenderer == NULL) {
        fprintf(stderr, "Impossible de créer le renderer : %s\n", SDL_GetError());
        return 0;
    }
    SDL_SetRenderDrawBlendMode(getRenderer(), SDL_BLENDMODE_BLEND);

    return 1;
}

/**
 * Retrieve window dimensions
 * @param w pointer to the variable that contains the width
 * @param h pointer to the variable that contains the height
 */
void getWindowWidth(int *w, int *h) {
    SDL_GetWindowSize(gWindow, w, h);
}

/**
 * Récupère le renderer du programme
 * @return renderer
 */
SDL_Renderer *getRenderer() {
    return gRenderer;
}

/**
 * Libère la mémoire utilisée par SDL
 */
void freeGraphics() {
    if (gWindow != NULL) {
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
    }
}
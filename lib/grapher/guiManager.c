#include <pthread.h>
#include "guiManager.h"

static SDL_Renderer *gRenderer = NULL;
static SDL_Window *gWindow;

/**
 * Démarre l'interface utilisateur
 */
void startUserInterface() {
    if(!initGraphics()) {
        exit(1);
    }

    // Création du thread qui gère le rendering
    pthread_t thread1;
    pthread_create();

    // La console reste sur le thread principal
    processConsoleInstructions();
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

/**
 * Initialise les libs SDL
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
 * Création de la fenêtre SDL
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
 * Création du renderer SDL
 */
static int createRenderer() {
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);

    if (gRenderer == NULL) {
        fprintf(stderr, "Impossible de créer le renderer : %s\n", SDL_GetError());
        return 0;
    }
    SDL_SetRenderDrawBlendMode(getRenderer(), SDL_BLENDMODE_BLEND);

    return 1;
}

/**
 * Récupère les dimensions de la fenêtre
 * @param w pointeur vers la variable qui va contenir la largeur
 * @param h pointeur vers la variable qui va contenir la hauteur
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
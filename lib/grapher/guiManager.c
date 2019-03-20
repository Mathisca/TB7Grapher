#include <pthread.h>
#include "guiManager.h"

static SDL_Renderer *gRenderer = NULL;

void startUserInterface() {
    initGraphics();

    pthread_t thread1;
    pthread_create(&thread1, NULL, startMainLoop, NULL);

    while (!SDL_QuitRequested()) {
        int select = 0;
        int selectbis = 0;
        int R = 255, G = 0, B = 0, A = 255;
        printf("Bienvenue sur TB7 Plotter, que voulez-vous faire? \n");
        printf("1. Ajouter une expression et la visualiser. \n");
        printf("2. Supprimer une expression. \n");
        scanf("%d", &select);
        switch (select) {
            case 1: {
                printf("Veuillez entrer votre expresion et appuyer sur Entrée. \n");


                char *function = malloc(sizeof(char) * 100);
                scanf("%s", function);
                printf("Appuyez sur 1 si vous souhaitez choisir la couleur de votre courbe. \n");
                printf("Appuyez sur 2 pour avoir la couleur par défaut. \n");
                scanf("%d", &selectbis);

                if (selectbis == 1) {
                    printf("Entrez le code RGBA correspondant en appuyant sur Entrée entre chaque code. \n");
                    scanf("%d %d %d %d", &R, &G, &B, &A);
                }

                SDL_Color color = {R, G, B, A};
                ElementList list = RecognizeLexem(function);
                Entity e = syntaxBuild(list);

                printf("Erreur : %i\n", e->element.value.error);

                addEntity(e, function, color);
            }
            case 2: {

            }
            default: {

            }

        }

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

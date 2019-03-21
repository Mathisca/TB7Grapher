#include "inputHandler.h"

/**
 * Handles SDL Events
 */
void processEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                processKeyDown(event.key.keysym);
                break;
            case SDL_MOUSEWHEEL:
                processMouseWheel(event.wheel);
                break;
            default:
                //
                break;
        }
    }
}

/**
 * Called when a mouse wheel event occurs
 * @param event SDL event
 */
void processMouseWheel(SDL_MouseWheelEvent event) {
    if (event.y == 1) { // scroll up
        zoom();
    } else { // scroll down
        unzoom();
    }

}

/**
 * Called when a keyboard key is pressed
 * @param key keyboard key pressed
 */
static void processKeyDown(SDL_Keysym key) {
    SDL_Keycode code = key.sym;

    switch (code) {
        case (97) : // A
            nbGradChange(-2);
            break;
        case (122): // Z
            nbGradChange(2);
            break;
        case (113): // Q
            togglePrintGrid();
            break;
        case (1073741906): // uparrow
            changeYSpan(2);
            break;
        case (1073741905): // downarrow
            changeYSpan(-2);
            break;
        case (1073741904): // left
            changeXSpan(-2);
            break;
        case (1073741903): // right
            changeXSpan(2);
            break;
        default:
            break;
    }
}


void processConsoleInstructions() {
    const char *errorNames[] = {"aucune erreur",
                                "pas de fonction entrée",
                                "division par zéro",
                                "opération non réelle",
                                "caractère non reconnu",
                                "fonction non reconnue",
                                "erreur de syntaxe",
                                "erreur de parenthèse"};

    while (!SDL_QuitRequested()) {

        int select = 0;
        int R = 255, G = 0, B = 0, A = 255; // default color

        printf("\nBienvenue sur TB7 Plotter, que voulez-vous faire? \n");
        printf("Veuillez entrer votre expression et appuyer sur entrée. \n");

        char *function = malloc(sizeof(char) * 100);
        scanf("%s", function);

        printf("Appuyez sur 1 si vous souhaitez choisir la couleur de votre courbe. \n");
        printf("Appuyez sur 2 pour avoir la couleur par défaut. \n");

        scanf("%d", &select);

        if (select == 1) {
            printf("Entrez le code RGBA correspondant en appuyant sur Entrée entre chaque code. \n");
            scanf("%d %d %d %d", &R, &G, &B, &A);
        }

        SDL_Color color = {(Uint8) R, (Uint8) G, (Uint8) B, (Uint8) A};
        ElementList list = RecognizeLexem(function);

        if (list == NULL) // check if analytic is OK
            fprintf(stderr, "Une erreur est survenue.\n");
        else if (list->element.token == ERROR) { // check if analytic is OK
            fprintf(stderr, "Une erreur est survenue : %s\n", errorNames[list->element.value.error]);
        } else {
            Entity e = syntaxBuild(list);

            if (e == NULL) // check if syntax is OK
                fprintf(stderr, "Une erreur est survenue.\n");
            else if (e->element.token == ERROR) { // check if syntax is OK
                fprintf(stderr, "Une erreur est survenue : %s\n", errorNames[e->element.value.error]);
            } else {
                printf("Fonction ajoutée avec succès !\n");
                addEntity(e, function, color);
            }
        }

    }

}


#include "guiRenderer.h"

static TTF_Font *gFont;
static ValueArray gValuesArray = NULL;

static double gSpanX = 10.0;
static double gSpanY = 10.0;
static int gNbGrad = 10;

/**
 * Démarrage du loop principal
 */
void *startMainLoop() {
    loadResources();

    while (!SDL_QuitRequested()) {
        processEvents();
        render();
    }

    freeGraphics();
}

/**
 * Chargement des ressources graphiques (police d'écriture)
 */
static void loadResources() {
    // Ouverture de la police
    gFont = TTF_OpenFont("fonts/opensans.ttf", 100);

    // Vérification
    if (gFont == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de la police : %s\n", TTF_GetError());
        exit(1);
    }
}

/**
 * Ajoute une fonction au graph
 *
 * @param e fonction à ajouter
 * @param fct nom d'affichage de la fonction
 * @param color couleur de la fonction
 */
void addEntity(Entity e, char *fct, SDL_Color color) {
    if(e->element.token == ERROR && e->element.value.error != NO_ERROR) {
        fprintf(stderr, "La fonction passée au grapheur était erronnée !\n");
        return;
    }

    ValueArray newArray = malloc(sizeof(struct valueArraySt));

    newArray->e = e;
    newArray->p = processPoints(e); // On calcule directement les points de la fonction ici
    newArray->color = color;
    newArray->printableValue = fct;

    newArray->nextEntity = gValuesArray;
    gValuesArray = newArray;
}

/**
 * Recalcule tous les points des courbes
 * (en cas de changement de span par exemple)
 */
static void recalculateAll() {
    ValueArray copy = gValuesArray;

    while (copy != NULL) {
        copy->p = processPoints(copy->e);
        copy = copy->nextEntity;
    }
}

/**
 * Calcule les points d'une fonction
 * @param e fonction à calculer
 * @return les points calculés
 */
static Point processPoints(Entity e) {
    Point p = NULL;

    /* On évalue les valeurs de la fonction du min du graphique au max.
     * Le pas est de gSpanX/PRECISION pour avoir toujours suffisamment de points
     * pour tracer la courbe de manière continue
     */
    for (double i = -gSpanX / 2.0; i < gSpanX / 2.0; i += gSpanX / PRECISION) {
        Result r = result(e, i);

        if (r.error == NO_ERROR) {
            Point newPoint = malloc(sizeof(struct pointSt));

            newPoint->x = i;
            newPoint->y = r.value;
            newPoint->nextPoint = NULL;

            if (p == NULL)
                p = newPoint;
            else {
                newPoint->nextPoint = p;
                p = newPoint;
            }

        }
    }
    return p;
}

/**
 * Augmente la taille de graphique affichée
 */
void unzoom() {
    gSpanY += ZOOMFACTOR;
    gSpanX += ZOOMFACTOR;

    recalculateAll();
}

/**
 * Réduit la taille de graphiqe affichée
 */
void zoom() {
    if (gSpanY - ZOOMFACTOR > 0 && gSpanX - ZOOMFACTOR > 0) {
        gSpanY -= 10;
        gSpanX -= 10;

        recalculateAll();
    }
}

/**
 * Modifie le nombre de graduations
 * @param mod nombre de graduations à modifier
 */
void nbGradChange(int mod) {
    if (gNbGrad + mod > 0)
        gNbGrad += mod;
}

/**
 * Actualise l'affichage
 */
void render() {
    int width, height;
    getWindowWidth(&width, &height);

    int graphBeginX = (int) (width / 3.0);
    double graphWidth = ((2.0 / 3.0) * width);
    int graphMidX = (int) ((graphWidth) / 2 + graphBeginX);

    int printGrid = 1;


    // Screen clear

    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(getRenderer());

    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0xFF);

    // Separation

    SDL_RenderDrawLine(getRenderer(), graphBeginX, 0, graphBeginX, height);

    // Axis

    SDL_RenderDrawLine(getRenderer(), graphBeginX, height / 2, width, height / 2); // X
    SDL_RenderDrawLine(getRenderer(), graphMidX, 0, graphMidX, height); //

    // Arrows creation

    SDL_RenderDrawLine(getRenderer(), graphMidX - 10, 20, graphMidX, 0);
    SDL_RenderDrawLine(getRenderer(), graphMidX, 0, graphMidX + 10, 20);
    SDL_RenderDrawLine(getRenderer(), width - 20, height / 2 + 10, width, height / 2);
    SDL_RenderDrawLine(getRenderer(), width, height / 2, width - 20, height / 2 - 10);

    // Graduations creation

    for (int i = 0; i < gNbGrad; i++) {
        int positionW = (int) (graphBeginX + i * (graphWidth) / gNbGrad);
        int positionH = (int) (i * ((double) height / gNbGrad));

        int gradSizeW = (int) (graphWidth / 100);
        int gradSizeH = height / 100;

        SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0xFF);

        SDL_RenderDrawLine(getRenderer(), positionW, height / 2 + gradSizeH, positionW, height / 2 - gradSizeH);
        SDL_RenderDrawLine(getRenderer(), (int) (graphWidth - gradSizeW), positionH, (int) (graphWidth + gradSizeW),
                           positionH);

        char *grad = malloc(sizeof(char) * 100);

        sprintf(grad, "%.1lf", ((1.0 * i / gNbGrad) * gSpanX) - gSpanX / 2);
        makeText(grad, positionW + gradSizeW, height / 2 + gradSizeH, 20, 20);

        sprintf(grad, "%.1lf", ((-1.0 * i / gNbGrad) * gSpanY) + gSpanY / 2);
        makeText(grad, graphMidX + gradSizeW, positionH + gradSizeH, 20, 20);


        free(grad);


        // Grid creation (except in the middle and at the beginning)

        if (printGrid && i != 0 && i != gNbGrad / 2) {
            SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 70);
            SDL_RenderDrawLine(getRenderer(), positionW, 0, positionW, height); // axe X
            SDL_RenderDrawLine(getRenderer(), graphBeginX, positionH, width, positionH); // axe Y
        }

    }


    makeText("TB7Plotter", 50, 0, width / 3 - 100, height / 10);
    makeText("x", width - width / 70, height / 2 + height / 600, width / 75, width / 50);
    makeText("f(x)", graphMidX - width / 30, height / 700, width / 50, width / 50);

    // Plotter creation
    ValueArray back = gValuesArray;
    for (int j = 0; back != NULL; ++j) {
        Point p = back->p;

        SDL_SetRenderDrawColor(getRenderer(), back->color.r, back->color.g, back->color.b, back->color.a);

        while (p != NULL) {
            int x1 = (int) (graphWidth + ((graphWidth * p->x) / gSpanX));
            int y1 = (int) (height / 2.0 - ((p->y * height) / (gSpanY)));
            SDL_RenderDrawPoint(getRenderer(), x1, y1);

            p = p->nextPoint;
        }

        int yLine = height / 5 + (height / 10) * j;
        int xLine = width / 30;


        SDL_RenderDrawLine(getRenderer(), xLine, yLine, 2 * xLine, yLine);
        char *printableString = malloc(sizeof(char) * 100);

        sprintf(printableString, "f(x) = %s", back->printableValue);
        makeText(printableString, (int) (2.3 * xLine), yLine - 10, (int) (width / 200.0 * strlen(printableString)), 30);

        back = back->nextEntity;
    }

    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0, 0xFF, 0xFF);

    int mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    double mathMouseX = (((mouseX - graphBeginX) * gSpanX) / graphWidth - gSpanX / 2.0);
    double mathMouseY = -((mouseY - height / 2) * gSpanY) / height;


    if (mouseX >= graphBeginX) {
        char *position = malloc(sizeof(char) * 100);

        sprintf(position, "x = %.2lf", mathMouseX);
        makeText(position, graphBeginX + 10, height - 20, 80, 20);

        sprintf(position, "y = %.2lf", mathMouseY);
        makeText(position, graphBeginX + 10, height - 45, 80, 20);

        free(position);

    }

    SDL_RenderPresent(getRenderer());
}

/**
 * Affiche du texte à l'écran
 *
 * @param text texte à afficher
 * @param x position x du texte
 * @param y position y du texte
 * @param w largeur du texte
 * @param h hauteur du texte
 */
static void makeText(char *text, int x, int y, int w, int h) {
    SDL_Color black = {0, 0, 0};

    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(gFont, text, black);
    SDL_Texture *Message = SDL_CreateTextureFromSurface(getRenderer(),
                                                        surfaceMessage); //now you can convert it into a texture

    SDL_Rect textRect;
    textRect.x = x;
    textRect.y = y;
    textRect.w = w;
    textRect.h = h;

    SDL_RenderCopy(getRenderer(), Message, NULL, &textRect);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

}
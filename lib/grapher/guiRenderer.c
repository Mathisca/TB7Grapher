#include "guiRenderer.h"

static TTF_Font *gFont; // font used in the program
static ValueArray gValuesArray = NULL; // contains the functions

static double gSpanX = DEFAULTSPAN; // span X of the graph
static double gSpanY = DEFAULTSPAN; // span Y of the graph
static int gNbGrad = DEFAULTGRAD; // number of graduations
static int gPrintGrid = 1;

/**
 * Starts the main loop
 */
void *startMainLoop() {
    loadResources();

    // Loop until the user wants to exit
    while (!SDL_QuitRequested()) {
        processEvents();
        render();
    }

    freeGraphics();
}

/**
 * Loads the graphical resources (fonts)
 */
static void loadResources() {
    // Opens the font
    gFont = TTF_OpenFont("fonts/opensans.ttf", 100);

    // Checks if the font is correctly open
    if (gFont == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de la police : %s\n", TTF_GetError());
        exit(1);
    }
}

/**
 * Adds a function to the graph
 *
 * @param e function to add
 * @param fct name of the function
 * @param color color of the function
 */
void addEntity(Entity e, char *fct, SDL_Color color) {
    // Checks if the function is valid
    if (e->element.token == ERROR && e->element.value.error != NO_ERROR) {
        fprintf(stderr, "La fonction passée au grapheur était erronnée !\n");
        return;
    }

    // Allocated the memory for a new function
    ValueArray newArray = malloc(sizeof(struct valueArraySt));

    newArray->e = e;
    newArray->p = processPoints(e); // Calculates the points of the function here
    newArray->color = color;
    newArray->printableValue = fct;

    newArray->nextEntity = gValuesArray;
    gValuesArray = newArray;
}

/**
 * Recalculates all the points
 * (in case of a span change)
 */
static void recalculateAll() {
    ValueArray copy = gValuesArray;

    while (copy != NULL) {
        freePoints(copy->p);
        copy->p = processPoints(copy->e);
        copy = copy->nextEntity;
    }
}

static void freePoints(Point p) {
    if (p == NULL)
        return;

    free(p->nextPoint);
    freePoints(p->nextPoint);
}

/**
 * Calculates all the points of a function
 * @param e function to calculate the points toq
 * @return the calculated points
 */
static Point processPoints(Entity e) {
    Point p = NULL;

    /*
     * We evaluate the values of the function from min to max of the graph.
     * The step is gSpanX/PRECISION to always get a sufficent number of points to plot the graph
     */
    for (double i = -gSpanX / 2.0; i < gSpanX / 2.0; i += gSpanX / PRECISION) {
        Result r = result(e, i); // evaluates the function

        if (r.error == NO_ERROR) {
            Point newPoint = malloc(sizeof(struct pointSt));

            newPoint->x = i;
            newPoint->y = r.value;
            newPoint->nextPoint = NULL;

            // Adds the point to the list
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
 * Increases the size of the displayed graph
 */
void unzoom() {
    gSpanY += ZOOMFACTOR;
    gSpanX += ZOOMFACTOR;

    // recalculate everything as the span has changed
    recalculateAll();
}

/**
 * Reduces the size of the displayed graph
 */
void zoom() {
    // Check if we can still zoom
    if (gSpanY - ZOOMFACTOR > 0 && gSpanX - ZOOMFACTOR > 0) {
        gSpanY -= 10;
        gSpanX -= 10;

        // recalculate everything as the span has changed
        recalculateAll();
    }
}

void changeXSpan(int change) {
    if(gSpanX + change > 0)
        gSpanX += change;

    recalculateAll();
}

void changeYSpan(int change) {
    if(gSpanY + change > 0)
        gSpanY += change;

    recalculateAll();
}

/**
 * Toggles the grid on the graph
 */
void togglePrintGrid() {
    gPrintGrid ^= 1;
}

/**
 * Modifies the number of graduations
 * @param mod numbers of graduations to modify
 */
void nbGradChange(int mod) {
    if (gNbGrad + mod > 0)
        gNbGrad += mod;
}

/**
 * Refreshes display
 */
static void render() {
    int width, height;
    getWindowWidth(&width, &height);

    int graphBeginX = (int) (width / 3.0); // Position of the left tab
    double graphWidth = ((2.0 / 3.0) * width); // Width of the graph
    int graphMidX = (int) ((graphWidth) / 2 + graphBeginX); // x = 0 on the graph

    // Screen clear
    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(getRenderer());
    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0xFF);

    // Separation between the menu and the graph
    SDL_RenderDrawLine(getRenderer(), graphBeginX, 0, graphBeginX, height);

    // Y and X Axis
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

        SDL_RenderDrawLine(getRenderer(), positionW, height / 2 + gradSizeH,
                           positionW, height / 2 - gradSizeH);

        SDL_RenderDrawLine(getRenderer(), (int) (graphWidth - gradSizeW), positionH,
                           (int) (graphWidth + gradSizeW), positionH);

        // text that holds the values of the graduations
        char *grad = malloc(sizeof(char) * 100);

        sprintf(grad, "%.1lf", ((1.0 * i / gNbGrad) * gSpanX) - gSpanX / 2);
        makeText(grad, positionW + gradSizeW, height / 2 + gradSizeH, 20, 20);

        sprintf(grad, "%.1lf", ((-1.0 * i / gNbGrad) * gSpanY) + gSpanY / 2);
        makeText(grad, graphMidX + gradSizeW, positionH + gradSizeH, 20, 20);


        free(grad);


        // Grid creation (except in the middle and at the beginning)
        if (gPrintGrid && i != 0 && i != gNbGrad / 2) {
            SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 70);
            SDL_RenderDrawLine(getRenderer(), positionW, 0, positionW, height); // axe X
            SDL_RenderDrawLine(getRenderer(), graphBeginX, positionH, width, positionH); // axe Y
        }

    }

    // Informations display
    makeText("TB7Plotter", 50, 0, width / 3 - 100, height / 10);
    makeText("x", width - width / 70, height / 2 + height / 600, width / 75, width / 50);
    makeText("f(x)", graphMidX - width / 30, height / 700, width / 50, width / 50);

    // Plots the graph
    ValueArray back = gValuesArray;
    for (int j = 0; back != NULL; ++j) {
        Point p = back->p;

        // Sets color to the function's color
        SDL_SetRenderDrawColor(getRenderer(), back->color.r, back->color.g, back->color.b, back->color.a);

        while (p != NULL && p->nextPoint != NULL) {
            // Translated the "math" x and y to the screen's x and y
            int x1 = (int) (graphWidth + ((graphWidth * p->x) / gSpanX));
            int y1 = (int) (height / 2.0 - ((p->y * height) / (gSpanY)));

            int x2 = (int) (graphWidth + ((graphWidth * p->nextPoint->x) / gSpanX));
            int y2 = (int) (height / 2.0 - ((p->nextPoint->y * height) / (gSpanY)));

            // Make the line between two points
            SDL_RenderDrawLine(getRenderer(), x1, y1, x2, y2);

            p = p->nextPoint;
        }

        // Prints the legend in the left menu
        int yLine = height / 5 + (height / 10) * j;
        int xLine = width / 30;
        SDL_RenderDrawLine(getRenderer(), xLine, yLine, 2 * xLine, yLine);

        // Text of the function in the left menu
        char *printableString = malloc(sizeof(char) * 100);
        sprintf(printableString, "f(x) = %s", back->printableValue);
        makeText(printableString, (int) (2.3 * xLine), yLine - 10, (int) (width / 200.0 * strlen(printableString)), 30);

        // go to the next function to pot
        back = back->nextEntity;
    }

    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0, 0xFF, 0xFF);

    int mouseX, mouseY; // Contains mouse position

    SDL_GetMouseState(&mouseX, &mouseY);


    // If the mouse is somewhere in the graph
    if (mouseX >= graphBeginX) {
        // Translated the real mouse position to "mathematical" position
        double mathMouseX = (((mouseX - graphBeginX) * gSpanX) / graphWidth - gSpanX / 2.0);
        double mathMouseY = -((mouseY - height / 2.0) * gSpanY) / height;

        if(gValuesArray != NULL) {
            Result r = result(gValuesArray->e, mathMouseX);

            SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0xFF);

            if (r.error == NO_ERROR && !isnan(r.value)) {
                int realFunctionY = (int) (height / 2 - ((r.value * height) / (gSpanY)));

                char *str = malloc(sizeof(char) * 100);
                sprintf(str, "[%lf, %lf]", mathMouseX, r.value);
                makeText(str, mouseX + width / 100, realFunctionY + height / 100, width / 10, width / 60);
                free(str);


                SDL_RenderDrawLine(getRenderer(), mouseX, realFunctionY, mouseX, height / 2);
                SDL_RenderDrawLine(getRenderer(), mouseX, realFunctionY, (int) (graphBeginX + graphWidth / 2),
                                   realFunctionY);
            }
        }


        // Prints the mathematical position of the mouse in the graph
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
 * Displays text on screen
 *
 * @param text text to display
 * @param x x position of text
 * @param y y position of text
 * @param w width of text
 * @param h height of text
 */
static void makeText(char *text, int x, int y, int w, int h) {
    SDL_Color black = {0, 0, 0};

    SDL_Surface *testSurface = TTF_RenderText_Blended(gFont, text, black);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(getRenderer(), testSurface);

    SDL_Rect textRect;
    textRect.x = x;
    textRect.y = y;
    textRect.w = w;
    textRect.h = h;

    SDL_RenderCopy(getRenderer(), textTexture, NULL, &textRect);

    // Frees the used memory
    SDL_FreeSurface(testSurface);
    SDL_DestroyTexture(textTexture);
}
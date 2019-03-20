#include "guiRenderer.h"

TTF_Font *Sans;  //this opens a font style and sets a size

Entity e;

void startMainLoop() {
    e = malloc(sizeof(struct entitySt));
    e->right_operand = malloc(sizeof(struct entitySt));
    e->left_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand = malloc(sizeof(struct entitySt));
    e->left_operand->left_operand = malloc(sizeof(struct entitySt));
    e->element.token = OPERATOR;
    e->element.value.operators = MULTIPLY;
    e->right_operand->element.token = FUNCTION;
    e->right_operand->element.value.functions = LN;
    e->right_operand->left_operand->element.token = VARIABLE;
    e->left_operand->element.token = FUNCTION;
    e->left_operand->element.value.functions = SIN;
    e->left_operand->left_operand->element.token = REAL;
    e->left_operand->left_operand->element.value.real = 9;
    e->left_operand->right_operand = NULL;
    e->left_operand->left_operand->left_operand = NULL;
    e->left_operand->left_operand->right_operand = NULL;
    e->right_operand->right_operand = NULL;
    e->right_operand->left_operand->right_operand = NULL;
    e->right_operand->left_operand->left_operand = NULL;

    Sans = TTF_OpenFont("fonts/opensans.ttf", 100);
    if (Sans == NULL) {
        log_fatal("Font error : %s", TTF_GetError());
        exit(1);
    }

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 100; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect


    SDL_SetTextInputRect(&Message_rect);
    SDL_StartTextInput();
    processPoints();

    while (1) {
        processEvents();
        render();
    }
}

Point p = NULL;
double spanX = 10.0;
double spanY = 10.0;

int nbGrad = 10;


void processPoints() {
    p = NULL;

    for (double i = -spanX / 2.0; i < spanX / 2.0; i += spanX / 10000.0) {
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


}


void unzoom() {
    spanY *= 2;
    spanX *= 2;

    processPoints();
}

void zoom() {
    if(spanX == 0 || spanY == 0) {
        spanX = 1;
        spanY = 1;
    }
    spanY /= 2;
    spanX /= 2;

    processPoints();
}

void nbGradChange(int mod) {
    if (nbGrad + mod > 0)
        nbGrad += mod;
}

void render() {
    spanX += 0.05;
    spanY += 0.05;
    processPoints();
    int width, height;
    getWindowWidth(&width, &height);


    int graphBeginX = (int) (width / 3.0);
    double graphWidth = ((2.0 / 3.0) * width);
    int graphMidX = (int) ((graphWidth) / 2 + graphBeginX);

    int printGrid = 1;


    //Clear de l'écran
    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(getRenderer());

    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0xFF);

    // Séparation
    SDL_RenderDrawLine(getRenderer(), graphBeginX, 0, graphBeginX, height);

    // Axes
    SDL_RenderDrawLine(getRenderer(), graphBeginX, height / 2, width, height / 2); // X
    SDL_RenderDrawLine(getRenderer(), graphMidX, 0, graphMidX, height); // Y

    // Création des graduations
    for (int i = 0; i < nbGrad; i++) {
        int positionW = (int) (graphBeginX + i * (graphWidth) / nbGrad);
        int positionH = (int) (i * ((double) height / nbGrad));

        int gradSizeW = (int) (graphWidth / 100);
        int gradSizeH = height / 100;

        SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0xFF);

        SDL_RenderDrawLine(getRenderer(), positionW, height / 2 + gradSizeH, positionW, height / 2 - gradSizeH);
        SDL_RenderDrawLine(getRenderer(), (int) (graphWidth - gradSizeW), positionH, (int) (graphWidth + gradSizeW),
                           positionH);

        char *grad = malloc(sizeof(char) * 100);

        sprintf(grad, "%.1lf", ((1.0 * i / nbGrad) * spanX) - spanX / 2);

        makeText(grad, positionW + gradSizeW, height / 2 + gradSizeH, 20, 20);

        sprintf(grad, "%.1lf", ((-1.0 * i / nbGrad) * spanY) + spanY / 2);

        makeText(grad, graphMidX + gradSizeW, positionH + gradSizeH, 20, 20);


        free(grad);


        // Création de la grille (sauf au milieu et au début)
        if (printGrid && i != 0 && i != 5) {
            SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 70);
            SDL_RenderDrawLine(getRenderer(), positionW, 0, positionW, height); // axe X
            SDL_RenderDrawLine(getRenderer(), graphBeginX, positionH, width, positionH); // axe Y
        }

    }

    makeText("TB7Plotter", 30, 0, width / 3 - 60, 100);
    makeText("x", width - width/75, height/2 + height/700, width/75, width/50);
    makeText("f(x)", graphMidX - width/50, height/700, width/50, width/50);


    // Création du graphique

    SDL_SetRenderDrawColor(getRenderer(), 0xFF, 0, 0, 0xFF);

    Point back = p;
    while (back != NULL && back->nextPoint != NULL) {

        int x1 = (int) (graphWidth + ((graphWidth * back->x) / spanX));
        int x2 = (int) (graphWidth + ((graphWidth * back->nextPoint->x) / spanX));
        int y1 = (int) (height / 2.0 - ((back->y * height) / (spanY)));
        int y2 = (int) (height / 2.0 - ((back->nextPoint->y * height) / (spanY)));

        SDL_RenderDrawPoint(getRenderer(), x1, y1);

        back = back->nextPoint;
    }

    int mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    if (mouseX >= graphBeginX) {
        double mathMouseX = ((mouseX - graphBeginX) * spanX) / graphWidth - spanX / 2.0;

        Result r = result(e, mathMouseX);

        SDL_SetRenderDrawColor(getRenderer(), 0, 0xFF, 0xFF, 0xFF);

        if (r.error == NO_ERROR && !isnan(r.value)) {
            int realFunctionY = (int) (height / 2 - ((r.value * height) / (spanY)));

            char *str = malloc(sizeof(char) * 100);
            sprintf(str, "[%lf, %lf]", mathMouseX, r.value);
            makeText(str, mouseX + width / 100, realFunctionY + height / 100, width / 15, width / 60);
            free(str);


            SDL_RenderDrawLine(getRenderer(), mouseX, realFunctionY, mouseX, height / 2);

            SDL_RenderDrawLine(getRenderer(), mouseX, realFunctionY, (int) (graphBeginX + graphWidth / 2),
                               realFunctionY);
        }
    }

    SDL_RenderPresent(getRenderer());


}

static void makeText(char *text, int x, int y, int w, int h) {
    SDL_Color black = {0, 0, 0};

    SDL_Surface *surfaceMessage = TTF_RenderText_Blended(Sans, text, black);
    SDL_Texture *Message = SDL_CreateTextureFromSurface(getRenderer(),
                                                        surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = x;  //controls the rect's x coordinate
    Message_rect.y = y; // controls the rect's y coordinte
    Message_rect.w = w; // controls the width of the rect
    Message_rect.h = h; // controls the height of the rect

    SDL_RenderCopy(getRenderer(), Message, NULL, &Message_rect);


    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

}
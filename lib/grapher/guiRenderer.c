#include "guiRenderer.h"

TTF_Font *Sans;  //this opens a font style and sets a size

Entity function;

void startMainLoop(Entity ent) {

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

    SDL_RenderDrawLine(getRenderer(), graphMidX - 10, 20 ,graphMidX , 0);
    SDL_RenderDrawLine(getRenderer(), graphMidX, 0, graphMidX + 10, 20);
    SDL_RenderDrawLine(getRenderer(), width - 20, height/2 +10 , width, height/2);
    SDL_RenderDrawLine(getRenderer(), width, height/2, width - 20, height/2 - 10);

    // Graduations creation

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


        // Grid creation (except in the middle and at the beginning)

        if (printGrid && i != 0 && i != 5) {
            SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 70);
            SDL_RenderDrawLine(getRenderer(), positionW, 0, positionW, height); // axe X
            SDL_RenderDrawLine(getRenderer(), graphBeginX, positionH, width, positionH); // axe Y
        }

    }

    makeText("TB7Plotter", 30, 0, width / 3 - 60, 100);
    //makeText("R : Entrer une nouvelle expression", 30, 200, width / 4 - 60, 0);
    makeText("x", width - width/70, height/2 + height/600, width/75, width/50);
    makeText("f(x)", graphMidX - width/30, height/700, width/50, width/50);

    // Plotter creation

    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0xFF);

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

        SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 0xFF);

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
    Message_rect.y = y; // controls the rect's y coordinate
    Message_rect.w = w; // controls the width of the rect
    Message_rect.h = h; // controls the height of the rect

    SDL_RenderCopy(getRenderer(), Message, NULL, &Message_rect);


    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

}
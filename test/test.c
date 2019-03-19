#include "test.h"
#include "SDL.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void testGraph() {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return;
    }
    window = SDL_CreateWindow(
            "hello_sdl2",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return;
    }
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void testSyntax() {
    ElementList list = createMockList();
    printf("salut");
}

void testAnalyst() {

}

void testInterpreter() {

}

ElementList createMockElement(TOKENS token, Union u) {
    ElementList list = (ElementList) malloc(sizeof(struct elementListSt));
    Element e;
    e.token = token;
    e.value = u;
    list->element = e;
    return list;
}

ElementList createMockList() {
    Union u1;
    u1.functions = SIN;
    ElementList list = createMockElement(FUNCTION, u1);
    Union u2;
    u2.real = 0.0f;
    list->nextElement = createMockElement(PAR_OPN, u2);
    list->nextElement->nextElement = createMockElement(PAR_OPN, u2);
    Union u3;
    u3.real = 2.0f;
    list->nextElement->nextElement = createMockElement(REAL, u3);
    Union u4;
    u4.operators = MULTIPLY;
    list->nextElement->nextElement->nextElement = createMockElement(OPERATOR, u4);
    list->nextElement->nextElement->nextElement->nextElement = createMockElement(VARIABLE, u4);
    list->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(PAR_CLS, u4);
    Union u5;
    u5.operators = PLUS;
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(OPERATOR,
                                                                                                           u5);
    Union u6;
    u6.real = 5;
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            REAL, u6);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            PAR_CLS, u6);

    return list;
}


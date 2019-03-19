/*
#include "test.h"
//#include "SDL.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void testGraph() {
//    SDL_Window* window = NULL;
//    SDL_Surface* screenSurface = NULL;
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
//        return;
//    }
//    window = SDL_CreateWindow(
//            "hello_sdl2",
//            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//            SCREEN_WIDTH, SCREEN_HEIGHT,
//            SDL_WINDOW_SHOWN
//    );
//    if (window == NULL) {
//        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
//        return;
//    }
//    screenSurface = SDL_GetWindowSurface(window);
//    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
//    SDL_UpdateWindowSurface(window);
//    SDL_Delay(2000);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
}

void testSyntax() {
    ElementList list = createMockListTrue();
    ERRORS err0 = syntaxChecker(list);
    ERRORS err1 = syntaxChecker(createMockListFalse1());
    ERRORS err2 = syntaxChecker(createMockListFalse2());
    ERRORS err3 = syntaxChecker(createMockListFalse3());
    ERRORS err4 = syntaxChecker(createMockListFalse4());
    ERRORS err5 = syntaxChecker(createMockListFalse5());
    ERRORS err6 = syntaxChecker(createMockListFalse6());
    return;
}

void testAnalyst() {

}

void testInterpreter() {

}

ElementList createMockElement(TOKENS token, Valeur u) {
    ElementList list = (ElementList) malloc(sizeof(struct elementListSt));
    Element e;
    e.token = token;
    e.value = u;
    list->element = e;
    return list;
}

ElementList createMockListTrue() {
    // sin((2*x)+5)
    Valeur u1;
    u1.functions = SIN;
    ElementList list = createMockElement(FUNCTION, u1);
    Valeur u2;
    u2.real = 0.0f;
    list->nextElement = createMockElement(PAR_OPN, u2);
    list->nextElement->nextElement = createMockElement(PAR_OPN, u2);
    Valeur u3;
    u3.real = 2.0f;
    list->nextElement->nextElement->nextElement = createMockElement(REAL, u3);
    Valeur u4;
    u4.operators = MULTIPLY;
    list->nextElement->nextElement->nextElement->nextElement = createMockElement(OPERATOR, u4);
    list->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(VARIABLE, u4);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(PAR_CLS, u4);
    Valeur u5;
    u5.operators = PLUS;
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            OPERATOR,
            u5);
    Valeur u6;
    u6.real = 5;
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            REAL, u6);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(
            PAR_CLS, u6);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListFalse1() {
    //*5x
    Valeur u1;
    u1.operators = MULTIPLY;
    ElementList list = createMockElement(OPERATOR, u1);
    Valeur u2;
    u2.real = 5.0f;
    list->nextElement = createMockElement(REAL, u2);
    list->nextElement->nextElement = createMockElement(VARIABLE, u2);
    list->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListFalse2() {
    // cos3+x
    Valeur u1;
    u1.functions = SIN;
    ElementList list = createMockElement(FUNCTION, u1);
    Valeur u2;
    u2.real = 3.0f;
    list->nextElement = createMockElement(REAL, u2);
    Valeur u3;
    u3.operators = PLUS;
    list->nextElement->nextElement = createMockElement(OPERATOR, u3);
    list->nextElement->nextElement->nextElement = createMockElement(VARIABLE, u3);
    list->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListFalse3() {
    // 5*(3-x
    Valeur u1;
    u1.real = 5.0f;
    ElementList list = createMockElement(REAL, u1);
    Valeur u2;
    u2.operators = MULTIPLY;
    list->nextElement = createMockElement(OPERATOR, u2);
    list->nextElement->nextElement = createMockElement(PAR_OPN, u2);
    Valeur u3;
    u3.real = 3.0f;
    list->nextElement->nextElement->nextElement = createMockElement(REAL, u3);
    Valeur u4;
    u4.operators = MINUS;
    list->nextElement->nextElement->nextElement->nextElement = createMockElement(OPERATOR, u4);
    list->nextElement->nextElement->nextElement->nextElement->nextElement = createMockElement(VARIABLE, u4);
    list->nextElement->nextElement->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListFalse4() {
    // )5-x(
    Valeur u1;
    u1.real = 0;
    ElementList list = createMockElement(PAR_OPN, u1);
    Valeur u2;
    u2.real = 5.0f;
    list->nextElement = createMockElement(REAL, u2);
    Valeur u3;
    u3.operators = MINUS;
    list->nextElement->nextElement = createMockElement(OPERATOR, u3);
    list->nextElement->nextElement->nextElement = createMockElement(VARIABLE, u3);
    list->nextElement->nextElement->nextElement->nextElement = createMockElement(PAR_OPN, u3);
    list->nextElement->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}


ElementList createMockListFalse5() {
    // cos()
    Valeur u1;
    u1.functions = COS;
    ElementList list = createMockElement(OPERATOR, u1);
    list->nextElement = createMockElement(PAR_OPN, u1);
    list->nextElement->nextElement = createMockElement(PAR_CLS, u1);
    list->nextElement->nextElement->nextElement = NULL;
    return list;
}

ElementList createMockListFalse6() {
    // 5+*x
    Valeur u1;
    u1.real = 5.0f;
    ElementList list = createMockElement(REAL, u1);
    Valeur u2;
    u2.operators = PLUS;
    list->nextElement = createMockElement(OPERATOR, u2);
    Valeur u3;
    u3.operators = MULTIPLY;
    list->nextElement->nextElement = createMockElement(OPERATOR, u3);
    list->nextElement->nextElement->nextElement = createMockElement(VARIABLE, u3);
    list->nextElement->nextElement->nextElement->nextElement = NULL;
    return list;
}
 */


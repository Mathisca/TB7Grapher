#ifndef TB7GRAPHER_TOKENS_H
#define TB7GRAPHER_TOKENS_H

#include <SDL2/SDL.h>


typedef enum TOKENS {
    REAL,
    OPERATOR,
    FUNCTION,
    ERROR,
    PAR_OPN,
    PAR_CLS,
    VARIABLE
} TOKENS;

typedef enum FUNCTIONS {
    SIN,
    COS,
    TAN,
    SINC,
    COSC,
    TANC,
    ABS,
    EXP,
    LOG,
    LN,
    SINH,
    COSH,
    TANH,
    SQRT,
    ARCSIN,
    ARCCOS,
    ARCTAN

} FUNCTIONS;

typedef enum OPERATORS {
    MULTIPLY,
    DIVIDE,
    PLUS,
    MINUS,
    POWER
} OPERATORS;

typedef enum ERRORS {
    NO_ERROR,
    NO_INPUT,
    DIV_BY_ZERO,
    NON_REAL_OPERATION,
    UNRECOGNIZED_CHAR,
    UNRECOGNIZED_FUNCTION,
    SYNTAX_ERROR,
    PAR_ERROR
} ERRORS;

typedef union valeurSt {
    double real;
    OPERATORS operators;
    FUNCTIONS functions;
    ERRORS error;
} Valeur;

typedef struct elementSt {
    TOKENS token;
    Valeur value;
} Element;

typedef struct resultSt {
    ERRORS error;
    double value;
} Result;


typedef struct entitySt *Entity;
struct entitySt {
    Element element;

    Entity left_operand;
    Entity right_operand;
};

typedef struct pointSt *Point;
struct pointSt {
    double x;
    double y;

    Point nextPoint;
};

typedef struct valueArraySt *ValueArray;
struct valueArraySt {
    Point p;
    Entity e;
    SDL_Color color;
    char * printableValue;

    ValueArray nextEntity;
};


typedef struct elementListSt *ElementList;
struct elementListSt {
    Element element;
    ElementList nextElement;
};

#endif //TB7GRAPHER_TOKENS_H
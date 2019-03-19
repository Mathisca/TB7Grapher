#ifndef TB7GRAPHER_TOKENS_H
#define TB7GRAPHER_TOKENS_H

typedef enum TOKENS {
    NO_TOKEN,
    REAL,
    OPERATOR,
    FUNCTION,
    ERROR,
    END,
    PAR_OPN,
    PAR_CLS,
    VARIABLE
} TOKENS;

typedef enum FUNCTIONS {
    SIN,
    COS,
    TAN,
    SINC,
    ABS,
    EXP,
    LOG,
    LN

} FUNCTIONS;

typedef enum OPERATORS{
    MULTIPLY,
    DIVIDE,
    PLUS,
    MINUS,
    POWER
} OPERATORS;

typedef enum ERRORS{
    DIV_BY_ZERO,
    NON_REAL_OPERATION,
    UNRECOGNIZED_CHAR,
    UNRECOGNIZED_FUNCTION,
    SYNTAX_ERROR
} ERRORS;

typedef union unionSt {
    double real;
    OPERATORS operators;
    FUNCTIONS functions;
    ERRORS error;
} Union;

typedef struct elementSt {
    TOKENS token;
    Union value;
} Element;

typedef struct entitySt * Entity;

struct entitySt {
    Element element;

    Entity left_operand;
    Entity right_operand;
};

typedef struct pointSt * Point;
struct pointST {
    double x;
    double y;

    Point nextPoint;
};

typedef struct elementListSt * ElementList;
struct elementListSt {
    Element element;
    ElementList nextElement;
};

#endif //TB7GRAPHER_TOKENS_H

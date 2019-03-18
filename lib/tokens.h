#ifndef TB7GRAPHER_TOKENS_H
#define TB7GRAPHER_TOKENS_H

enum TOKEN {
    NO_TOKEN,
    REAL,
    OPERATOR,
    FUNCTION,
    ERROR,
    END,
    PAR_OPN,
    PAR_CLS,
    VARIABLE
};
typedef enum TOKEN TOKEN;

typedef struct entitySt * Entity;

struct entitySt {
    TOKEN token;
    double value;

    Entity left_operand;
    Entity right_operand;
};


#endif //TB7GRAPHER_TOKENS_H

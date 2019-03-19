#include "syntaxAnalyser.h"


Entity createEntity(Element e) {
    Entity entity = (Entity) malloc(sizeof(struct entitySt));
    entity->element = e;
    entity->left_operand = NULL;
    entity->right_operand = NULL;
    return entity;
}

Element createElement(TOKENS token, OPERATORS operator, FUNCTIONS function, ERRORS error, double value) {
    Element e;
    if (token == OPERATOR) {
        e.token = OPERATOR;
        Union u;
        u.operators = operator;
        e.value = u;
    } else if (token == FUNCTION) {
        e.token = FUNCTION;
        Union u;
        u.functions = function;
        e.value = u;
    } else if (token == ERROR) {
        e.token = ERROR;
        Union u;
        u.error = error;
        e.value = u;
    } else if (token == REAL) {
        e.token = REAL;
        Union u;
        u.real = value;
        e.value = u;
    } else {
        e.token = token;
        Union u;
        e.value = u;
    }
    return e;
}
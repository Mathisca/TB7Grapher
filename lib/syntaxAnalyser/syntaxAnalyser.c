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
        Valeur u;
        u.operators = operator;
        e.value = u;
    } else if (token == FUNCTION) {
        e.token = FUNCTION;
        Valeur u;
        u.functions = function;
        e.value = u;
    } else if (token == ERROR) {
        e.token = ERROR;
        Valeur u;
        u.error = error;
        e.value = u;
    } else if (token == REAL) {
        e.token = REAL;
        Valeur u;
        u.real = value;
        e.value = u;
    } else {
        e.token = token;
        Valeur u;
        e.value = u;
    }
    return e;
}
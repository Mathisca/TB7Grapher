#include "syntaxAnalyser.h"

Entity syntaxBuild(ElementList list) {

}

ERRORS syntaxChecker(ElementList list) {
    ElementList firstElement = list;
    int opened_par = 0;
    int closed_par = 0;
    ERRORS error = NO_ERROR;

    // checking the begin of the list
    if (list->element.token == OPERATOR) {
        if (list->element.value.operators != PLUS && list->element.value.operators != MINUS) {
            return error = SYNTAX_ERROR;
        }
    }
    ElementList prev_elmnt;
    while (list != NULL) {
        if (list->element.token == PAR_OPN) {
            opened_par++;
            if (list->nextElement == NULL) {
                error = SYNTAX_ERROR;
                break;
            } else {
                if (list->nextElement->element.token == PAR_CLS) {
                    error = SYNTAX_ERROR;
                    break;
                }
            }
        } else if (list->element.token == PAR_CLS) {
            closed_par++;
        } else if (list->element.token == FUNCTION) {
            // it should have a parenthese right after
            if (list->nextElement == NULL) {
                error = SYNTAX_ERROR;
                break;
            } else {
                if (list->nextElement->element.token != PAR_OPN) {
                    error = PAR_ERROR;
                    break;
                }
                if (list->nextElement->nextElement == NULL) {
                    error = SYNTAX_ERROR;
                    break;
                } else {
                    if (list->nextElement->nextElement->element.token == PAR_CLS) {
                        error = SYNTAX_ERROR;
                        break;
                    }
                }
            }
        } else if (list->element.token == OPERATOR) {
            if (list->nextElement == NULL) {
                error = SYNTAX_ERROR;
                break;
            } else {
                if (list->nextElement->element.token == OPERATOR) {
                    error = SYNTAX_ERROR;
                    break;
                }
            }
        }

        // Testing the conditions
        if (opened_par < closed_par) {
            error = PAR_ERROR;
            break;
        }

        prev_elmnt = list;
        list = list->nextElement;
    }

    // at the end of the list
    if (opened_par != closed_par) {
        error = PAR_ERROR;
    }
    if (prev_elmnt->element.token == OPERATOR || prev_elmnt->element.token == FUNCTION ||
        prev_elmnt->element.token == PAR_OPN) {
        error = SYNTAX_ERROR;
    }

    return error;
}

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
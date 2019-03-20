#include "syntaxAnalyser.h"

Entity syntaxBuild(ElementList list) {
    ERRORS error = syntaxChecker(list);
    if (error == NO_ERROR) {
        ElementList first_elmt = list;
        // no error is detected, we can proceed
        int operator_lvl = 10000;
        Valeur operator;
        int actual_level = 0;
        int level_to_break;
        int in_function = 0;
        int operator_position = 0;
        int i = 0;
        while (list != NULL) {
            if (list->element.token == FUNCTION) {
                level_to_break = actual_level;
                in_function = 1;
            }
            if (list->element.token == PAR_OPN) {
                actual_level++;
            } else if (list->element.token == PAR_CLS) {
                actual_level--;
                if (level_to_break == actual_level) {
                    in_function = 0;
                }
            }
            if (!in_function) {
                if (list->element.token == OPERATOR) {
                    if (actual_level < operator_lvl) {
                        operator = list->element.value;
                        operator_lvl = actual_level;
                        operator_position = i;
                    }
                }
            }
            list = list->nextElement;
            i++;
        }
        if (operator_lvl != 10000) {
            // operator is the main aspect of the expression
            Element main_operator;
            main_operator.token = OPERATOR;
            main_operator.value = operator;
            Entity tree = createEntity(main_operator);

            printf("ONLY A FUNCTION");

        } else {
            printf("ONLY A FUNCTION");
        }
    } else {
        printf("SYNTAX ERROR");
    }
}

ElementList createElementListWithPosition(ElementList list, int position0, int position1) {

}

Entity createTree(ElementList list) {
    Entity tree;
    ElementList first_elmt = list;

    // no error is detected, we can proceed
    int operator_lvl = 10000;
    Valeur operator;
    int actual_level = 0;
    int level_to_break;
    int in_function = 0;
    int operator_position = 0;
    int i = 0;
    ElementList prev_elmnt = NULL;
    while (list != NULL) {
        if (list->element.token == FUNCTION) {
            level_to_break = actual_level;
            in_function = 1;
        }
        if (list->element.token == PAR_OPN) {
            actual_level++;
        } else if (list->element.token == PAR_CLS) {
            actual_level--;
            if (level_to_break == actual_level) {
                in_function = 0;
            }
        }
        if (!in_function) {
            if (list->element.token == OPERATOR) {
                if (actual_level < operator_lvl) {
                    if (i != 0) {
                        if (prev_elmnt != NULL && prev_elmnt->element.token != PAR_OPN) {
                            operator = list->element.value;
                            operator_lvl = actual_level;
                            operator_position = i;
                        }
                    }
                }
            }
        }
        prev_elmnt = list;
        list = list->nextElement;
        i++;
    }
    if (operator_lvl != 10000) {
        // operator is the main aspect of the expression
        Element main_operator;
        main_operator.token = OPERATOR;
        main_operator.value = operator;
        tree = createEntity(main_operator);
        int j = 0;
        if (first_elmt->element.token == PAR_OPN) {
            first_elmt = first_elmt->nextElement;
            operator_position--;
        }
        ElementList first_expression = first_elmt;
        ElementList second_expression;
        ElementList prev_elmnt;

        list = first_expression;
        prev_elmnt = list;
        while (list != NULL) {
            if (j == operator_position) {
                second_expression = list->nextElement;
                prev_elmnt->nextElement = NULL;
                break;
            }
            j++;
            prev_elmnt = list;
            list = list->nextElement;
        }
        list = second_expression;
        while (list != NULL) {
            if (list->nextElement != NULL) {
                if (list->nextElement->nextElement != NULL) {

                }
                if (list->nextElement->element.token == PAR_CLS) {
                    list->nextElement = NULL;
                }
            }
            list = list->nextElement;
        }
        tree->left_operand = createTree(second_expression);
        tree->right_operand = createTree(first_expression);
    } else {
        if (first_elmt->element.token == PAR_OPN) {
            first_elmt = first_elmt->nextElement;
        }
        if (first_elmt->element.token == VARIABLE) {
            tree = createEntity(first_elmt->element);
        } else if (first_elmt->element.token == REAL) {
            tree = createEntity(first_elmt->element);
        } else if (first_elmt->element.token == FUNCTION) {
            tree = createEntity(first_elmt->element);
            tree->left_operand = createTree(first_elmt->nextElement);
        } else if (first_elmt->element.token == OPERATOR) {
            Element multiply;
            multiply.token = OPERATOR;
            Valeur multiply_u;
            multiply_u.operators = MULTIPLY;
            multiply.value = multiply_u;
            tree = createEntity(multiply);
            if (first_elmt->element.value.operators == MINUS) {
                Valeur u;
                u.real = -1.0f;
                Element e;
                e.token = REAL;
                e.value = u;
                tree->left_operand = createEntity(e);
                tree->right_operand = createTree(first_elmt->nextElement);
            }
        }
    }
    return tree;
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
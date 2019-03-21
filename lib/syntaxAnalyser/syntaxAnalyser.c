/*
 * File: syntaxAnalyser.h
 * Names: DELFORGE Bastien
 *        ALBRECHT Jérémy
 * Date: 20/03/2019
 */

#include "syntaxAnalyser.h"

/**
 * @brief Check for the syntax of the expression and call createTree if syntax is correct, return an error otherwise
 * @param list Linked list of the user's input
 * @return Binary tree containing our expression, a single node with the error if there is one
 * @author DELFORGE Bastien
 * @author ALBRECHT Jérémy
 */
Entity syntaxBuild(ElementList list) {
    ERRORS error = syntaxChecker(list);
    Entity tree;
    if (error == NO_ERROR) {
        tree = createTree(list);
    } else {
        Element e;
        e.token = ERROR;
        Valeur u;
        u.error = error;
        e.value = u;
        tree = createEntity(e);
    }
    return tree;
}

/**
 * @brief Method used to create the binary tree
 * @attention is called recursively
 * @param list Linked list we want the binary tree
 * @return Entity
 * @author DELFORGE Bastien
 * @author ALBRECHT Jérémy
 */
Entity createTree(ElementList list) {
    Entity tree; // creating the return value
    ElementList first_elmt = list; // create a copy of the first element of our linked list

    int operator_lvl = 10000; // used to determine at which depth is the operator, i.e. the main operator is the one with the lowest operator level
    Valeur operator; // to store the main operator
    int actual_level = 0; // used in the loop
    int level_to_break; // used in the loop
    int in_function = 0; // boolean if we are in a function or not
    int operator_position = 0;
    int i = 0;

    ElementList prev_elmnt = NULL; // storing at each iteration the previous element

    while (list != NULL) {
        if (list->element.token == FUNCTION) {
            // we are in a function, all the operators in it won't be the main operator, we set variables to skip all the function's content
            level_to_break = actual_level;
            in_function = 1;
        }
        if (list->element.token == PAR_OPN) {
            actual_level++;
        } else if (list->element.token == PAR_CLS) {
            actual_level--;
            if (level_to_break == actual_level) {
                // we have reached the end of a function, we can resume looking for a main operator
                in_function = 0;
            }
        }
        if (!in_function) { // we are NOT in a function
            if (list->element.token == OPERATOR && actual_level < operator_lvl && i != 0) {
                // we just detected an operator, whose level is below the previous one (i.e. more important) and isn't the first element of the expression
                if (prev_elmnt != NULL && prev_elmnt->element.token !=
                                                  PAR_OPN) { // if the operator is right after a bracket, it's not a operator but only a sign in front of an function
                    operator = list->element.value;
                    operator_lvl = actual_level;
                    operator_position = i;
                }
            }
        }
        prev_elmnt = list;
        list = list->nextElement;
        i++;
    } // end while

    // PART TWO:: 2 cases:
    // 1- there is a main operator in the expression
    // 2- there is no main operator, only a function, a constant, or a variable
    if (operator_lvl != 10000) { // CASE 1
        Element main_operator; // creating the element of the main operator
        main_operator.token = OPERATOR;
        main_operator.value = operator;

        tree = createEntity(main_operator); // create the first node of the binary tree with the main operator

        if (first_elmt->element.token ==
                PAR_OPN) { // if the first element is a bracket, we delete it and adapt the operator's position
            first_elmt = first_elmt->nextElement;
            operator_position--;
        }

        // Separating the two different expression next to the operator
        ElementList first_expression = first_elmt;
        ElementList second_expression;
        ElementList prev_elmnt;
        int j = 0;

        list = first_expression;
        prev_elmnt = list;

        while (list != NULL) {
            // we iterate throught the linked list to find the operator
            if (j == operator_position) { // we reached the operator !
                second_expression = list->nextElement; // second expression is the one after the operator
                prev_elmnt->nextElement = NULL; // suppress the link between first and second expression by setting to NULL
                break;
            }
            j++;
            prev_elmnt = list;
            list = list->nextElement;
        }
        // removing the last bracket in the second expression (if there is one)
        list = second_expression;

        while (list != NULL) {
            if (list->nextElement != NULL && list->nextElement->element.token == PAR_CLS) {
                list->nextElement = NULL;
            }
            list = list->nextElement;
        }

        // calling recursively this function to create the binary tree with second_expression and first_expression as parameter
        tree->right_operand = createTree(second_expression);
        tree->left_operand = createTree(first_expression);
    } else { // CASE 2
        // removing the first element if it's a bracket
        while (first_elmt->element.token == PAR_OPN) {
            first_elmt = first_elmt->nextElement;
        }

        // checking for case
        switch (first_elmt->element.token) {
            case VARIABLE:
                // only creating a node with the variable element
                tree = createEntity(first_elmt->element);
                break;
            case REAL:
                // only creatng a node with a real element
                tree = createEntity(first_elmt->element);
                break;
            case FUNCTION:
                // it's a function, we're creating a node with the function element and putting the content in its left child
                tree = createEntity(first_elmt->element);
                tree->left_operand = createTree(first_elmt->nextElement);
                break;
            case OPERATOR: {
                // for an operator we should check if it's a minus in front of a function
                // in this case we should add a multiply node with a value of -1
                Element multiply;
                multiply.token = OPERATOR;
                Valeur multiply_u;
                multiply_u.operators = MULTIPLY;
                multiply.value = multiply_u;
                tree = createEntity(multiply);
                Valeur u;
                switch (first_elmt->element.value.operators) {
                    case MINUS:
                        u.real = -1.0f;
                        break;
                    case PLUS:
                        u.real = 1.0f;
                        break;
                }
                Element e;
                e.token = REAL;
                e.value = u;
                tree->left_operand = createEntity(e); // left child is our +/-1
                tree->right_operand = createTree(first_elmt->nextElement); // right child is the rest of the expression
            }
                break;
        }
    }
    return tree;
}


/**
 * @brief Check for the expression syntax and return an error if the expression is incorrect and impossible to process
 * @param list Linked list containing the expression
 * @return NO_ERROR, or the given error
 *
 * @details 1. A bracket is mandatory after a declaration of a function
 * @details 2. Same number of opening and clsoing brackets
 * @details 3. No closing bracket before an opening one
 * @details 4. Mandatory expression in a function
 * @details 5. Two operators cannot be followed, unless it's a minus or a plus
 * @details 6. No operators like MULTIPLY, DIVIDE at the begin of expression
 *
 * @author DELFORGE Bastien
 * @author ALBRECHT Jérémy
 */
ERRORS syntaxChecker(ElementList list) {
    int opened_par = 0;
    int closed_par = 0;
    ERRORS error = NO_ERROR; // at first we consider there is no error

    // checking the begin of the list for rule 6
    if (list->element.token == OPERATOR) {
        if (list->element.value.operators != PLUS && list->element.value.operators != MINUS) {
            return SYNTAX_ERROR;
        }
    }

    ElementList prev_elmnt; // storing the previous element during our loop
    while (list != NULL) {
        if (list->element.token == PAR_OPN) {
            opened_par++; // counting the opening brackets
            if (list->nextElement == NULL) { // next to an opening bracket there is no expression => SYNTAX_ERROR
                error = SYNTAX_ERROR;
                break;
            } else {
                if (list->nextElement->element.token ==
                    PAR_CLS) { // next to an opening bracket there is a closing bracket => SYNTAX_ERROR
                    error = SYNTAX_ERROR;
                    break;
                } else if (list->nextElement->element.token == OPERATOR &&
                           (list->nextElement->element.value.operators == DIVIDE ||
                            list->nextElement->element.value.operators == MULTIPLY)) {
                    error = SYNTAX_ERROR;
                    break;
                }
            }
        } else if (list->element.token == PAR_CLS) {
            closed_par++; // counting the closing brackets
        } else if (list->element.token == FUNCTION) {
            // it should have a parenthese right after
            if (list->nextElement == NULL) { // a function is not followed by anything => SYNTAX_ERROR
                error = SYNTAX_ERROR;
                break;
            } else {
                if (list->nextElement->element.token !=
                        PAR_OPN) { // a function is not followed by a bracket => PAR_ERROR
                    error = PAR_ERROR;
                    break;
                }
                if (list->nextElement->nextElement ==
                        NULL) { // a function is followed by a bracket but then nothing => SYNTAX_ERROR
                    error = SYNTAX_ERROR;
                    break;
                } else {
                    if (list->nextElement->nextElement->element.token ==
                            PAR_CLS) { // a function is followed by an opening bracket and directly after a closing bracket => SYNTAX_ERROR
                        error = SYNTAX_ERROR;
                        break;
                    }
                }
            }
        } else if (list->element.token == OPERATOR) { // an operator isn't followed by antything => SYNTAX_ERROR
            if (list->nextElement == NULL) {
                error = SYNTAX_ERROR;
                break;
            } else {
                if (list->nextElement->element.token == OPERATOR &&
                        (list->element.value.operators == MULTIPLY || list->element.value.operators == DIVIDE)) {
                    // an operator (DIVIDE and MULTIPLY) is followed by another operator different from PLUS and MINUS
                    if (list->nextElement->element.value.operators != PLUS &&
                            list->nextElement->nextElement->element.value.operators != MINUS) {
                        error = SYNTAX_ERROR;
                        break;
                    }
                } else if (list->nextElement->element.token == OPERATOR &&
                           (list->element.value.operators == PLUS || list->element.value.operators == MINUS)) {
                    // an operator (PLUS and MINUS) is followed by another operator different from PLUS and MINUS
                    error = SYNTAX_ERROR;
                    break;

                }
            }
        }

        // At each iteration, check if there is no closing bracket before an opening one
        if (opened_par < closed_par) {
            error = PAR_ERROR;
            break;
        }

        prev_elmnt = list;
        list = list->nextElement;
    }

    // At the end, check if all opening brackets are closed
    if (opened_par != closed_par) {
        error = PAR_ERROR;
    }
    // at the end there is an operator, a function or an opening bracket => SYNTAX_ERROR
    if (prev_elmnt->element.token == OPERATOR || prev_elmnt->element.token == FUNCTION ||
        prev_elmnt->element.token == PAR_OPN) {
        error = SYNTAX_ERROR;
    }

    return error;
}


/**
 * @brief Method used to allocate the memory for a node in our binary tree and pre-fill its children with NULL values
 * @param e Element
 * @return The node
 */
Entity createEntity(Element e) {
    Entity entity = (Entity) malloc(sizeof(struct entitySt));
    entity->element = e;
    entity->left_operand = NULL;
    entity->right_operand = NULL;
    return entity;
}

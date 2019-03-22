/*
 * File: lexicalAnalyser.c
 * Authors: PIETTE Benoit, Salim El Fadali
 */

#include "lexicalAnalyser.h"
#include <stdlib.h>
#include <string.h>

double convertirenreel(char *s) { // convert string to double with atof function

    double d;
    d = atof(s);
    return d;

}

/**
 * Checks if the character is a real number
 *
 * @param e ElementList to be modified
 * @param *saisie char stroke
 * @param *i integer to increment to run along the string
 */

ElementList RecognizeLexemValue(ElementList e, char *saisie, int *i) {
    ElementList el = (ElementList) malloc(sizeof(struct elementListSt));
    double new = 0;
    char str[20];
    int j = 0;
    while (1) {
        if ((saisie[*i] <= '9' && saisie[*i] >= '0') || saisie[*i] == '.') {
            str[j] = saisie[*i];
            str[j+1] = '\0';
            j++;
            (*i)++;
        } else {
            if (j > 0) {
                (*i)--;
                new = convertirenreel(str);
                el->element.token = REAL;
                Valeur u;
                u.real = new;
                el->element.value = u;
                el->nextElement = NULL;
            } else {
                el = NULL;
            }
            //(*i)--;
            break;
        }
    }
    return el;
}

/**
 * Checks if the character is a variable 'x'
 *
 * @param e ElementList to be modified
 * @param *saisie char stroke
 * @param *i integer to increment to run along the string
 */

ElementList RecognizeLexemVariable(ElementList e, char *saisie, int *i) {
    ElementList el = (ElementList) malloc(sizeof(struct elementListSt));
    char var = 'x';
    if (saisie[*i] == var) {
        el->element.token = VARIABLE;
        Valeur u;
        el->element.value = u;
    } else {
        el = NULL;
    }
    return el;
}

/**
 * Checks if the character is an operator
 *
 * @param e ElementList to be modified
 * @param *saisie char stroke
 * @param *i integer to increment to run along the string
 */

ElementList RecognizeLexemOperators(ElementList e, char *saisie, int *i) {
    Valeur value;
    ElementList el = (ElementList) malloc(sizeof(struct elementListSt));
    switch (saisie[*i]) {

        case '*':
            el->element.token = OPERATOR;
            value.operators = MULTIPLY;
            el->element.value = value;
            break;

        case '+':
            el->element.token = OPERATOR;
            value.operators = PLUS;
            el->element.value = value;
            break;

        case '-':
            el->element.token = OPERATOR;
            value.operators = MINUS;
            el->element.value = value;
            break;

        case '^':
            el->element.token = OPERATOR;
            value.operators = POWER;
            el->element.value = value;
            break;

        case '/':
            el->element.token = OPERATOR;
            value.operators = DIVIDE;
            el->element.value = value;
            break;
        default:
            el = NULL;
    }
    return el;
}

/**
 * Checks if the character is a parenthesis
 *
 * @param e ElementList to be modified
 * @param *saisie char stroke
 * @param *i integer to increment to run along the string
 */

ElementList RecognizeLexemParenthesis(ElementList e, char *saisie, int *i) {
    Valeur value;
    ElementList el = (ElementList) malloc(sizeof(struct elementListSt));

    switch (saisie[*i]) {

        case '(':
            el->element.token = PAR_OPN;
            el->element.value = value;
            break;

        case ')':
            el->element.token = PAR_CLS;
            el->element.value = value;
            break;
        default:
            el = NULL;
    }
    return el;
}

/**
 * Checks if the character is a known function
 *
 * @param e ElementList to be modified
 * @param *saisie char stroke
 * @param *i integer to increment to run along the string
 */

ElementList RecognizeLexemFunction(ElementList e, char *c, int *i) {
    ElementList el = (ElementList) malloc(sizeof(struct elementListSt));

    switch (c[*i]) { //switch to check letters
        case 's':
            if (c[*i + 1] == 'i' && c[*i + 2] == 'n') {
                if (c[*i + 3] == 'c') { // sinc case
                    el->element.token = FUNCTION;
                    el->element.value.functions = SINC;
                    *i = *i + 3;
                } else if (c[*i + 3] == 'h') { // sinh case
                    el->element.token = FUNCTION;
                    el->element.value.functions = SINH;
                    *i = *i + 3;
                } else { // sin case
                    el->element.token = FUNCTION;
                    el->element.value.functions = SIN;
                    *i = *i + 2;
                }
            } else if (c[*i + 1] == 'q' && c[*i + 2] == 'r' && c[*i + 3] == 't') { // sqrt case
                el->element.token = FUNCTION;
                el->element.value.functions = SQRT;
                *i = *i + 3;
            } else { // Limit case when the string is not recognized
                el->element.token = ERROR;
                el->element.value.error = UNRECOGNIZED_CHAR;
            }
            break;

        case 'l':
            if (c[*i + 1] == 'n') { // Ln case
                el->element.token = FUNCTION;
                el->element.value.functions = LN;
                *i = *i + 1;
            } else if (c[*i + 1] == 'o' && c[*i + 2] == 'g') { //  Log case
                el->element.token = FUNCTION;
                el->element.value.functions = LOG;
                *i = *i + 2;
            } else { // Limit case when the string is not recognized
                el->element.token = ERROR;
                el->element.value.error = UNRECOGNIZED_CHAR;
            }

            break;

        case 'a':
            if (c[*i + 1] == 'b' && c[*i + 2] == 's') {// Abs case
                el->element.token = FUNCTION;
                el->element.value.functions = ABS;
                *i = *i + 2;
            } else if (c[*i + 1] == 'r' && c[*i + 2] == 'c') {
                if (c[*i + 3] == 'c' && c[*i + 4] == 'o' && c[*i + 5] == 's') {// Arccos case
                    el->element.token = FUNCTION;
                    el->element.value.functions = ARCCOS;
                    *i = *i + 5;
                } else if (c[*i + 3] == 's' && c[*i + 4] == 'i' && c[*i + 5] == 'n') { // Arcsin case
                    el->element.token = FUNCTION;
                    el->element.value.functions = ARCSIN;
                    *i = *i + 5;
                } else if (c[*i + 3] == 't' && c[*i + 4] == 'a' && c[*i + 5] == 'n') { // Arctan case
                    el->element.token = FUNCTION;
                    el->element.value.functions = ARCTAN;
                    *i = *i + 5;
                } else { // Limit case when the string is not recognized
                    el->element.token = ERROR;
                    el->element.value.error = UNRECOGNIZED_FUNCTION;
                    *i = *i + 2;
                }
            } else { // Limit case when the string is not recognized
                el->element.token = ERROR;
                el->element.value.error = UNRECOGNIZED_CHAR;
            }
            break;

        case 'c':
            if (c[*i + 1] == 'o' && c[*i + 2] == 's') {
                if (c[*i + 3] == 'c') { // Cosc case
                    el->element.token = FUNCTION;
                    el->element.value.functions = COSC;
                    *i = *i + 3;
                } else if (c[*i + 3] == 'h') { // Cosh case
                    el->element.token = FUNCTION;
                    el->element.value.functions = COSH;
                    *i = *i + 3;
                } else {  // Cos case
                    el->element.token = FUNCTION;
                    el->element.value.functions = COS;
                    *i = *i + 2;
                }
            } else { // Limit case when the string is not recognized
                el->element.token = ERROR;
                el->element.value.error = UNRECOGNIZED_FUNCTION;
            }

            break;

        case 't':
            if (c[*i + 1] == 'a' && c[*i + 2] == 'n') {
                if (c[*i + 3] == 'c') { //Tanc case
                    el->element.token = FUNCTION;
                    el->element.value.functions = TANC;
                    *i = *i + 3;
                } else if (c[*i + 3] == 'h') {  // Tanh case
                    el->element.token = FUNCTION;
                    el->element.value.functions = TANH;
                    *i = *i + 3;
                } else { // Tan case
                    el->element.token = FUNCTION;
                    el->element.value.functions = TAN;
                    *i = *i + 2;
                }

            } else { // Limit case when the string is not recognized
                el->element.token = ERROR;
                el->element.value.error = UNRECOGNIZED_FUNCTION;
            }

            break;

        case 'e':
            if (c[*i + 1] == 'x' && c[*i + 2] == 'p') { // Exp case
                el->element.token = FUNCTION;
                el->element.value.functions = EXP;
                *i = *i + 2;
            } else { // Limit case when the string is not recognized
                el->element.token = ERROR;
                el->element.value.error = UNRECOGNIZED_CHAR;
            }
            break;

        default :
            el = NULL;
    }
    return el;
}

/**
 * Recognizes the mathemathical function from a char stroke
 *
 * @param *chaine char stroke
 */

ElementList RecognizeLexem(char *chaine) {
    ElementList e = NULL;
    int *i = (int *) malloc(sizeof(int));
    *i = 0;
    ElementList list = (ElementList) malloc(sizeof(struct elementListSt));
    ElementList copy = list;

    ElementList op_e = NULL;
    ElementList val_e = NULL;
    ElementList var_e = NULL;
    ElementList par_e = NULL;
    ElementList fun_e = NULL;

    while (chaine[*i] != '\0') {
        op_e = RecognizeLexemOperators(e, chaine, i);
        if (op_e != NULL) {
            list->nextElement = op_e;
        } else {
            val_e = RecognizeLexemValue(e, chaine, i);
            if (val_e != NULL) {
                list->nextElement = val_e;
            } else {
                var_e = RecognizeLexemVariable(list, chaine, i);
                if (var_e != NULL) {
                    list->nextElement = var_e;
                } else {
                    par_e = RecognizeLexemParenthesis(e, chaine, i);
                    if (par_e != NULL) {
                        list->nextElement = par_e; // TODO sigsegv
                    } else {
                        fun_e = RecognizeLexemFunction(e, chaine, i);
                        if (fun_e != NULL) {
                            list->nextElement = fun_e; // TODO sigsegv aussi
                        }
                    }
                }
            }
        }
        list = list->nextElement; // TODO sigsegv
        (*i)++;
    }

    return copy->nextElement;
}
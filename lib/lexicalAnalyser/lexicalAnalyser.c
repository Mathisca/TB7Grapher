#include "lexicalAnalyser.h"

double convertirenreel(char *s) {

    double d;
    d = atof(s);
    return d;

}


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


ElementList RecognizeLexemVariable(ElementList e, char *saisie, int *i) {
    ElementList el = (ElementList) malloc(sizeof(struct elementListSt));
    char var = 'x';
    if (saisie[*i] == var) {
        el->element.token = VARIABLE;
        Valeur u;
        el->element.value = u; // TODO ??????
        el->nextElement = NULL;
    } else {
        el = NULL;
    }
    return el;
}

ElementList RecognizeLexemOperators(ElementList e, char *saisie, int *i) { //Fonction opérateur
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

ElementList RecognizeLexemParenthesis(ElementList e, char *saisie, int *i) {
    Valeur value;
    ElementList el = (ElementList) malloc(sizeof(struct elementListSt));

    switch (saisie[*i]) {

        case '(':
            el->element.token = PAR_OPN;
            el->element.value = value; // TODO value non init!!!
            el->nextElement = NULL;
            break;

        case ')':
            el->element.token = PAR_CLS;
            el->element.value = value; // TODO value non init!!!
            el->nextElement = NULL;
            break;
        default:
            el = NULL;
    }
    return el;
}


ElementList
RecognizeLexemFunction(ElementList e, char *c, int *i) { // fonction permettant de renvoyer  un maillon d'une fonction
    ElementList el = (ElementList) malloc(sizeof(struct elementListSt));

    switch (c[*i]) { //switch pour les différentes premières lettres des fonctions
        case 's':
            if (c[*i + 1] == 'i' && c[*i + 2] == 'n') {
                if (c[*i + 3] == 'c') { // cas pour sinc
                    el->element.token = FUNCTION;
                    el->element.value.functions = SINC;
                    *i = *i + 3;
                } else if (c[*i + 3] == 'h') { // cas pour sinh
                    el->element.token = FUNCTION;
                    el->element.value.functions = SINH;
                    *i = *i + 3;
                } else { // Cas pour sin
                    el->element.token = FUNCTION;
                    el->element.value.functions = SIN;
                    *i = *i + 2;
                }
            } else if (c[*i + 1] == 'q' && c[*i + 2] == 'r' && c[*i + 3] == 't') { // Cas pour sqrt
                el->element.token = FUNCTION;
                el->element.value.functions = SQRT;
                *i = *i + 3;
            } else { // Cas limite avec s en 1er lettre n etant pas SIN, SINH, SINHC ou SQRT
                el->element.token = ERROR;
                el->element.value.error = UNRECOGNIZED_CHAR;
            }
            break;

        case 'l':
            if (c[*i + 1] == 'n') { // Cas pour Ln
                el->element.token = FUNCTION;
                el->element.value.functions = LN;
                *i = *i + 1;
            } else if (c[*i + 1] == 'o' && c[*i + 2] == 'g') { // Cas pour Log
                el->element.token = FUNCTION;
                el->element.value.functions = LOG;
                *i = *i + 2;
            } else {// Cas limite pour erreur avec l n'etant ni ln et log
                el->element.token = ERROR;
                el->element.value.error = UNRECOGNIZED_CHAR;
            }

            break;

        case 'a':
            if (c[*i + 1] == 'b' && c[*i + 2] == 's') {// Cas pour Abs
                el->element.token = FUNCTION;
                el->element.value.functions = ABS;
                *i = *i + 2;
            } else if (c[*i + 1] == 'r' && c[*i + 2] == 'c') {
                if (c[*i + 3] == 'c' && c[*i + 4] == 'o' && c[*i + 5] == 's') {// Cas pour Arccos
                    el->element.token = FUNCTION;
                    el->element.value.functions = ARCCOS;
                    *i = *i + 5;
                } else if (c[*i + 3] == 's' && c[*i + 4] == 'i' && c[*i + 5] == 'n') { // Cas pour Arcsin
                    el->element.token = FUNCTION;
                    el->element.value.functions = ARCSIN;
                    *i = *i + 5;
                } else if (c[*i + 3] == 't' && c[*i + 4] == 'a' && c[*i + 5] == 'n') { // Cas pour Arctan
                    el->element.token = FUNCTION;
                    el->element.value.functions = ARCTAN;
                    *i = *i + 5;
                } else {//Cas limite pour ARC suivit dautres lettres
                    el->element.token = ERROR;
                    el->element.value.error = UNRECOGNIZED_FUNCTION;
                    *i = *i + 2;
                }
            } else { // Cas limite pour toutes lettre venant apres a si ni ABS ni ARC
                el->element.token = ERROR;
                el->element.value.error = UNRECOGNIZED_CHAR;
            }
            break;

        case 'c':
            if (c[*i + 1] == 'o' && c[*i + 2] == 's') {
                if (c[*i + 3] == 'c') { // Cas pour Cosc
                    el->element.token = FUNCTION;
                    el->element.value.functions = COSC;
                    *i = *i + 3;
                } else if (c[*i + 3] == 'h') { // Cas pour Cosh
                    el->element.token = FUNCTION;
                    el->element.value.functions = COSH;
                    *i = *i + 3;
                } else {  // Cas pour Cos
                    el->element.token = FUNCTION;
                    el->element.value.functions = COS;
                    *i = *i + 2;
                }
            } else { // Cas limite pour c différent de cos
                el->element.token = ERROR;
                el->element.value.error = UNRECOGNIZED_FUNCTION;
            }

            break;

        case 't':
            if (c[*i + 1] == 'a' && c[*i + 2] == 'n') {
                if (c[*i + 3] == 'c') { // Cas pour Tanc
                    el->element.token = FUNCTION;
                    el->element.value.functions = TANC;
                    *i = *i + 3;
                } else if (c[*i + 3] == 'h') {  // Cas pour Tanh
                    el->element.token = FUNCTION;
                    el->element.value.functions = TANH;
                    *i = *i + 3;
                } else { // Cas pour Tan
                    el->element.token = FUNCTION;
                    el->element.value.functions = TAN;
                    *i = *i + 2;
                }

            } else {// Cas limite pour c différent de tan
                el->element.token = ERROR;
                el->element.value.error = UNRECOGNIZED_FUNCTION;
            }

            break;

        case 'e':
            if (c[*i + 1] == 'x' && c[*i + 2] == 'p') { // Cas pour Exp
                el->element.token = FUNCTION;
                el->element.value.functions = EXP;
                *i = *i + 2;
            } else {// Cas limite pour e différent de exp
                el->element.token = ERROR;
                el->element.value.error = UNRECOGNIZED_CHAR;
            }
            break;

        default :
            el = NULL;
    }
    if (el != NULL) {
        el->nextElement = NULL;
    }
    return el;
}

ElementList RecognizeLexem(
        char *chaine) { // Fonction princial de l analyseur, appelle chaque fonction dans un while permettant de parcourir la chaine de caractères
    ElementList e = NULL;
    int *i = (int *) malloc(sizeof(int));
    *i = 0;
    ElementList list = (ElementList) malloc(sizeof(struct elementListSt));
    list->nextElement = NULL;
    ElementList copy = list;

    ElementList op_e = NULL;
    ElementList val_e = NULL;
    ElementList var_e = NULL;
    ElementList par_e = NULL;
    ElementList fun_e = NULL;

    while (chaine[*i] != '\0') {
        op_e = NULL;
        val_e = NULL;
        var_e = NULL;
        par_e = NULL;
        fun_e = NULL;
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
                        list->nextElement = par_e;
                    } else {
                        fun_e = RecognizeLexemFunction(e, chaine, i);
                        if (fun_e != NULL) {
                            list->nextElement = fun_e;
                        } else {
                            list->nextElement = (ElementList) malloc(sizeof(struct elementListSt));
                            Element element;
                            element.token = ERROR;
                            element.value.error = UNRECOGNIZED_CHAR;
                            list->nextElement->element = element;
                            list->nextElement->nextElement = NULL;
                        }
                    }
                }
            }
        }
        list = list->nextElement;
        (*i)++;
    }

    return copy->nextElement;
}

ElementList Test() {
    char chaine[50] = "tan(x+23.5)*3";
    return RecognizeLexem(chaine);
}
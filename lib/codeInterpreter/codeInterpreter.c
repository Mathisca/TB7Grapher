#include "codeInterpreter.h"


Result result(Entity e, double x) {
    Result r; // structure à retourner
    r.value = 0; //initialisation de la structure à retourner
    r.error = NO_ERROR;

    if (e == NULL || e->element.token == ERROR) { // cas d'arrêt
        r.error = NO_INPUT;
        return r;
    } else {

        if (e->element.token == VARIABLE) { //définition de la variable x
            e->element.value.real = x;
        }

        if (e->right_operand == NULL && e->left_operand == NULL) { // si l'arbre n'a pas de fils
            r.value = e->element.value.real;
        } else {
            Result left = result(e->left_operand, x); //vérification des erreurs
            if (left.error != NO_ERROR) {
                r.error = left.error;
                r.value = 0;
                return r;
            }
            result(e->left_operand, x);
        }

        if (e->element.token == OPERATOR) { //gestion des opérations (*, /, +, -)
            switch (e->element.value.operators) {
                case MULTIPLY:
                    r.value = result(e->left_operand, x).value * result(e->right_operand, x).value;
                    break;
                case DIVIDE:
                    if (e->left_operand->element.value.real == 0) { //valeur interdite
                        r.error = DIV_BY_ZERO; //type d'erreur
                    }
                    r.value = result(e->left_operand, x).value / result(e->right_operand, x).value;
                    break;
                case PLUS:
                    r.value = result(e->left_operand, x).value + result(e->right_operand, x).value;
                    break;
                case MINUS:
                    r.value = result(e->left_operand, x).value - result(e->right_operand, x).value;
                    break;
                case POWER:
                    r.value = pow((result(e->left_operand, x).value), (result(e->right_operand, x).value));
            }
        } else if (e->element.token == FUNCTION) { //gestion des fonctions
            switch (e->element.value.functions) {
                case SIN:
                    r.value = sin(result(e->left_operand, x).value);
                    break;
                case COS:
                    r.value = cos(result(e->left_operand, x).value);
                    break;
                case TAN:
                    if (e->left_operand->element.value.real == M_2_PI) {
                        r.error = NON_REAL_OPERATION;
                    }
                    r.value = tan(result(e->left_operand, x).value);
                    break;
                case SINC:
                    if (e->left_operand->element.value.real == 0) {
                        r.error = DIV_BY_ZERO;
                    }
                    r.value = (sin(result(e->left_operand, x).value) / result(e->left_operand, x).value);
                    break;
                case COSC:
                    if (e->left_operand->element.value.real == 0) {
                        r.error = DIV_BY_ZERO;
                    }
                    r.value = (cos(result(e->left_operand, x).value) / result(e->left_operand, x).value);
                    break;
                case TANC:
                    if (e->left_operand->element.value.real == 0) {
                        r.error = DIV_BY_ZERO;
                    }
                    r.value = (tan(result(e->left_operand, x).value) / result(e->left_operand, x).value);
                    break;
                case ABS:
                    r.value = fabs(result(e->left_operand, x).value);
                    break;
                case EXP:
                    r.value = exp(result(e->left_operand, x).value);
                    break;
                case LOG:
                    if (e->left_operand->element.value.real <= 0) {
                        r.error = NON_REAL_OPERATION;
                    }
                    r.value = log10(result(e->left_operand, x).value);
                    break;
                case LN:
                    if (e->left_operand->element.value.real <= 0) {
                        r.error = NON_REAL_OPERATION;
                    }
                    r.value = log(result(e->left_operand, x).value);
                    break;
                case SINH:
                    r.value = sinh(result(e->left_operand, x).value);
                    break;
                case COSH:
                    r.value = cosh(result(e->left_operand, x).value);
                    break;
                case TANH:
                    r.value = tanh(result(e->left_operand, x).value);
                    break;
                case SQRT:
                    if (e->left_operand->element.value.real < 0) {
                        r.error = NON_REAL_OPERATION;
                    }
                    r.value = sqrt(result(e->left_operand, x).value);
                    break;
                case ARCSIN:
                    if (e->left_operand->element.value.real < -1 || e->left_operand->element.value.real > 1) {
                        r.error = NON_REAL_OPERATION;
                    }
                    r.value = asin(result(e->left_operand, x).value);
                    break;
                case ARCCOS:
                    if (e->left_operand->element.value.real < -1 || e->left_operand->element.value.real > 1) {
                        r.error = NON_REAL_OPERATION;
                    }
                    r.value = acos(result(e->left_operand, x).value);
                    break;
                case ARCTAN:
                    if (e->left_operand->element.value.real < -1 || e->left_operand->element.value.real > 1) {
                        r.error = NON_REAL_OPERATION;
                    }
                    r.value = atan(result(e->left_operand, x).value);
                    break;
                default: //si la fonction ne correspond à aucun cas ci dessus
                    r.value = 0;
                    break;
            }
        }

    }
    return r;
}


double test_evaluation() { //fonction test du programme --> création arbre
    double res = 0;
    Result r;
    Entity e = malloc(sizeof(struct entitySt));
    e->right_operand = malloc(sizeof(struct entitySt));
    e->left_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand = malloc(sizeof(struct entitySt));
    e->left_operand->left_operand = malloc(sizeof(struct entitySt));
    e->element.token = OPERATOR;
    e->element.value.operators = MULTIPLY;
    e->right_operand->element.token = FUNCTION;
    e->right_operand->element.value.functions = LN;
    e->right_operand->left_operand->element.token = VARIABLE;
    e->left_operand->element.token = FUNCTION;
    e->left_operand->element.value.functions = SIN;
    e->left_operand->left_operand->element.token = REAL;
    e->left_operand->left_operand->element.value.real = 9;
    e->left_operand->right_operand = NULL;
    e->left_operand->left_operand->left_operand = NULL;
    e->left_operand->left_operand->right_operand = NULL;
    e->right_operand->right_operand = NULL;
    e->right_operand->left_operand->right_operand = NULL;
    e->right_operand->left_operand->left_operand = NULL;

    r = result(e, 0.5);
    res = r.value;
    return res;
}
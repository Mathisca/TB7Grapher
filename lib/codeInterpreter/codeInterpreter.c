#include "codeInterpreter.h"


Result result(Entity e, double x) {
    double fx = 0;
    Result r;
    r.value = 0;
    r.error = NO_ERROR;

    if (e == NULL || e->element.token == ERROR) {
        r.error = NO_INPUT;
        return r;
    } else {

        if (e->element.token == VARIABLE) {
            e->element.value.real = x;
        }

        if (e->right_operand == NULL && e->left_operand == NULL) {
            fx = e->element.value.real;
        } else {
            Result left = result(e->left_operand, x);
            if (left.error != NO_ERROR) {
                r.error = left.error;
                r.value = 0;
                return r;
            }
            result(e->left_operand, x);
        }

        if (e->element.token == OPERATOR) {
            switch(e->element.value.operators) {
                case MULTIPLY:
                    fx = result(e->left_operand, x).value * result(e->right_operand, x).value;
                    break;
                case DIVIDE:
                    if (e->left_operand->element.value.real == 0) {
                        r.error = DIV_BY_ZERO;
                    }
                    fx = result(e->left_operand, x).value / result(e->right_operand, x).value;
                    break;
                case PLUS:
                    fx = result(e->left_operand, x).value + result(e->right_operand, x).value;
                    break;
                case MINUS:
                    fx = result(e->left_operand, x).value - result(e->right_operand, x).value;
                    break;
                case POWER:
                    fx = pow((result(e->left_operand, x).value), (result(e->right_operand, x).value));
            }
        } else if (e->element.token == FUNCTION) {
            switch(e->element.value.functions) {
                case SIN:
                    fx = sin(result(e->left_operand, x).value);
                    break;
                case COS:
                    fx = cos(result(e->left_operand, x).value);
                    break;
                case TAN:
                    fx = tan(result(e->left_operand, x).value);
                    break;
                case SINC:
                    if (e->left_operand->element.value.real == 0) {
                        r.error = DIV_BY_ZERO;
                    }
                    fx = (sin(result(e->left_operand, x).value) / result(e->left_operand, x).value);
                    break;
                case COSC:
                    if (e->left_operand->element.value.real == 0) {
                        r.error = DIV_BY_ZERO;
                    }
                    fx = (cos(result(e->left_operand, x).value) / result(e->left_operand, x).value);
                    break;
                case TANC:
                    if (e->left_operand->element.value.real == 0) {
                        r.error = DIV_BY_ZERO;
                    }
                    fx = (tan(result(e->left_operand, x).value) / result(e->left_operand, x).value);
                    break;
                case ABS:
                    fx = fabs(result(e->left_operand, x).value);
                    break;

                case EXP:
                    fx = exp(result(e->left_operand, x).value);
                    break;
                case LOG:
                    if (e->left_operand->element.value.real <= 0) {
                        r.error = NON_REAL_OPERATION;
                    }
                    fx = log10(result(e->left_operand, x).value);
                    break;
                case LN:
                    if (e->left_operand->element.value.real <= 0) {
                        r.error = NON_REAL_OPERATION;
                    }
                    fx = log(result(e->left_operand, x).value);
                    break;
                case SINH:
                    fx = sinh(result(e->left_operand, x).value);
                    break;
                case COSH:
                    fx = cosh(result(e->left_operand, x).value);
                    break;
                case TANH:
                    fx = tanh(result(e->left_operand, x).value);
                    break;
                case SQRT:
                    if (e->left_operand->element.value.real < 0) {
                        r.error = NON_REAL_OPERATION;
                    }
                    fx = sqrt(result(e->left_operand, x).value);
                    break;
                case ARCSIN:
                    if (e->left_operand->element.value.real < -1 || e->left_operand->element.value.real > 1){
                        r.error = NON_REAL_OPERATION;
                    }
                    fx = asin(result(e->left_operand, x).value);
                    break;
                case ARCCOS:
                    if (e->left_operand->element.value.real < -1 || e->left_operand->element.value.real > 1){
                        r.error = NON_REAL_OPERATION;
                    }
                    fx = acos(result(e->left_operand, x).value);
                    break;
                case ARCTAN:
                    if (e->left_operand->element.value.real < -1 || e->left_operand->element.value.real > 1){
                        r.error = NON_REAL_OPERATION;
                    }
                    fx = atan(result(e->left_operand, x).value);
                    break;
                default:
                    fx = 0;
                    break;
            }
        }

    }
    r.value = fx;
    return r;
}


double test_evaluation() {
    double res = 0;
    Result r;
    Entity e = malloc(sizeof(struct entitySt));
    e->right_operand = malloc(sizeof(struct entitySt));
    e->left_operand = malloc(sizeof(struct entitySt));
    e->element.token = OPERATOR;
    e->element.value.operators = MULTIPLY;
    e->left_operand->element.token = REAL;
    e->left_operand->element.value.real = 6;
    e->right_operand->element.token = VARIABLE;

    r = result(e, 4);
    res = r.value;
    return res;
}

#include "codeInterpreter.h"


Result result (Entity e, double x){
    double fx = 0;
    Result r;
    r.value = 0;
    r.error = NO_ERROR;

    if (e == NULL){
    r.error = NO_INPUT;
    return r;
    }
    else {

    if (e->element.token == VARIABLE){
        e->element.value.real = x;
    }

    if (e->right_operand==NULL && e->left_operand==NULL){
        fx = e->element.value.real;
    } else {
        Result left = result(e->left_operand,x);
        if(left.error != NO_ERROR){
            r.error = left.error;
            r.value =0;
            return r;
        }
        result(e->left_operand,x);
    } if (e->element.token == OPERATOR){
        if (e->element.value.operators == MULTIPLY){
            fx = result(e->left_operand,x).value * result(e->right_operand,x).value;
        } else if (e->element.value.operators == DIVIDE){
            if (e->left_operand->element.value.real == 0){
                r.error = DIV_BY_ZERO;
            }
            fx = result(e->left_operand,x).value / result(e->right_operand,x).value;
        } else if (e->element.value.operators == PLUS){
            fx = result(e->left_operand,x).value + result(e->right_operand,x).value;
        } else if (e->element.value.operators == MINUS){
            fx = result(e->left_operand,x).value - result(e->right_operand,x).value;
        } else if (e->element.value.operators == POWER){
            fx = pow((result(e->left_operand,x).value),(result(e->right_operand,x).value));
        }
    } else if (e->element.token == FUNCTION){
        if (e->element.value.operators == SIN){
            fx = sin(result(e->left_operand, x).value);
        } else if (e->element.value.operators == COS){
            fx = cos(result(e->left_operand, x).value);
        } else if (e->element.value.operators == TAN){
            fx = tan(result(e->left_operand, x).value);
        } else if (e->element.value.operators == SINC){
            if (e->left_operand->element.value.real == 0){
                r.error = DIV_BY_ZERO;
            }
            fx = (sin(result(e->left_operand, x).value)/result(e->left_operand, x).value);
        } else if (e->element.value.operators == ABS){
            fx = fabs(result(e->left_operand, x).value);
        } else if (e->element.value.operators == EXP){
            fx = exp(result(e->left_operand, x).value);
        }else if (e->element.value.operators == LOG){
            if (e->left_operand->element.value.real <= 0){
                r.error = NON_REAL_OPERATION;
            } else
                fx = log10(result(e->left_operand, x).value);
        } else if (e->element.value.operators == LN){
            if (e->left_operand->element.value.real <= 0){
                r.error = NON_REAL_OPERATION;
            } else
                fx = log(result(e->left_operand, x).value);
        }
    }

}
    r.value = fx;
    return r;
}




double test_evaluation (){
    double res =0;
    Result r;
    Entity e = malloc(sizeof(struct entitySt *));
    e->right_operand = malloc(sizeof(struct entitySt *));
    e->left_operand = malloc(sizeof(struct entitySt *));
    e->element.token = OPERATOR;
    e->element.value.operators = MULTIPLY;
    e->left_operand->element.token = REAL;
    e->left_operand->element.value.real = 6;
    e->left_operand->element.value.real = VARIABLE;

    r = result(e, 4);
    res = r.value;
    return res;
}

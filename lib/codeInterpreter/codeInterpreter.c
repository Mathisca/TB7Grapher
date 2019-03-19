#include "codeInterpreter.h"

/*
Result result (Entity e, double x){
    double fx = 0;
if (e == NULL){
    return 0;
} else {
    if (e->element.token == VARIABLE){
        e->element.value.real = x;
    }
    if (e->right_operand==NULL && e->right_operand==NULL){
        fx = e->element.value.real;
    } else if (e->element.token == OPERATOR){
        if (e->element.value.operators == MULTIPLY){
            fx = result(e->left_operand,x) * result(e->right_operand,x);
        } else if (e->element.value.operators == DIVIDE){
            if (e->left_operand->element.value.real == 0){
                Entity error = malloc(sizeof(struct entitySt *));
                error->element.token = ERROR;
                error->element.value.error = DIV_BY_ZERO;
                error->left_operand =NULL;
                error->right_operand=NULL;
            }
            fx = result(e->left_operand,x) / result(e->right_operand,x);
        } else if (e->element.value.operators == PLUS){
            fx = result(e->left_operand,x) + result(e->right_operand,x);
        } else if (e->element.value.operators == MINUS){
            fx = result(e->left_operand,x) - result(e->right_operand,x);
        } else if (e->element.value.operators == POWER){
            fx = pow((result(e->left_operand,x)),(result(e->right_operand,x)));
        }
    } else if (e->element.token == FUNCTION){
        if (e->element.value.operators == SIN){
            fx = sin(result(e->left_operand, x));
        } else if (e->element.value.operators == COS){
            fx = cos(result(e->left_operand, x));
        } else if (e->element.value.operators == TAN){
            fx = tan(result(e->left_operand, x));
        } else if (e->element.value.operators == SINC){
            fx = (sin(result(e->left_operand, x))/result(e->left_operand, x));
        } else if (e->element.value.operators == ABS){
            fx = fabs(result(e->left_operand, x));
        } else if (e->element.value.operators == EXP){
            fx = exp(result(e->left_operand, x));
        }else if (e->element.value.operators == LOG){
            if (e->left_operand->element.value.real <= 0){
                Entity error = malloc(sizeof(struct entitySt *));
                error->element.token = ERROR;
                error->element.value.error = NON_REAL_OPERATION;
                error->left_operand =NULL;
                error->right_operand=NULL;
            } else
                fx = log10(result(e->left_operand, x));
        } else if (e->element.value.operators == LN){
            if (e->left_operand->element.value.real <= 0){
                Entity error = malloc(sizeof(struct entitySt *));
                error->element.token = ERROR;
                error->element.value.error = NON_REAL_OPERATION;
                error->left_operand =NULL;
                error->right_operand=NULL;
            } else
                fx = log(result(e->left_operand, x));
        }
    }

}
    //return fx;
}*/
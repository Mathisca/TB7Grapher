#include "codeInterpreter.h"


float result (Entity e, float x){
    char * fonction = NULL;
    float fx = 0;
if (e == NULL){
    return 0;
} else {
    if (e->token == VARIABLE){
        e->value =x;
    }
    if (e->left_operand !=NULL){
        fx = result(e->left_operand,x);
    }
    return fx;
}
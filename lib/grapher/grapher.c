#include "grapher.h"

void userInterface() {
    log_info("Veuillez saisir la fonction à tracer :");

    char * function = malloc(sizeof(char) * 100);
    scanf("%s", function);


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
}
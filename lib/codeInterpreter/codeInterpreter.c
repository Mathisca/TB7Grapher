/*
 * File: codeInterpreter.c
 * Names: AMYOT Flavie, SALIBA Louise
 */
#include "codeInterpreter.h"
#include "../tokens.h"

Result result(Entity e, double x) {
    Result r; // structure to return
    r.value = 0; //initializing the structure to return (type of error and value)
    r.error = NO_ERROR; //initializing the error type of the structure

    if (e == NULL) { // break case
        r.error = NO_INPUT; // if the tree is empty, or if there is previous errors (syntax...) assigning the type of error : NO_INPUT
        return r;// returns a structure with an error type and 0 as a value
    } else if (e->element.token == ERROR) {
        r.error = e->element.value.error;
        return r;
    } else {

        if (e->element.token == VARIABLE) { //if there is a variable
            e->element.value.real = x; //assigning the value x to the variable
        }

        if (e->right_operand == NULL && e->left_operand == NULL) { // if the tree doesn't have sons
            r.value = e->element.value.real; //the value of the result is the value in the node
        } else {
            Result left = result(e->left_operand, x); //checking for errors
            if (left.error != NO_ERROR) { //if there is an error
                r.error = left.error; //assigning the error to the result
                r.value = 0; //if there is an error, value of the result is 0
                return r;
            }
            result(e->left_operand, x); //calling the function on the left son
        }

        if (e->element.token == OPERATOR) { //management of the operators (+, -, *, /)
            switch (e->element.value.operators) { //in case the type of the node is an operator
                case MULTIPLY:
                    r.value = result(e->left_operand, x).value *
                              result(e->right_operand, x).value; //multiplying left and right sons
                    break;
                case DIVIDE:
                    if (e->left_operand->element.value.real == 0) { //non authorized value
                        r.error = DIV_BY_ZERO; //changing the error type : division by zero
                    }
                    r.value = result(e->left_operand, x).value /
                              result(e->right_operand, x).value; //dividing left son by right son
                    break;
                case PLUS:
                    r.value = result(e->left_operand, x).value +
                              result(e->right_operand, x).value; //additionning left and right sons
                    break;
                case MINUS:
                    r.value = result(e->left_operand, x).value -
                              result(e->right_operand, x).value; //left son minus right son
                    break;
                case POWER:
                    r.value = pow((result(e->left_operand, x).value),
                                  (result(e->right_operand, x).value)); //left son power right son
                    break;
            }
        } else if (e->element.token == FUNCTION) { //management of the functions
            switch (e->element.value.functions) { //in case the type of the node is a function
                case SIN:
                    r.value = sin(result(e->left_operand, x).value); // function(left son)
                    break;
                case COS:
                    r.value = cos(result(e->left_operand, x).value);
                    break;
                case TAN:
                    if (e->left_operand->element.value.real == M_2_PI) { //non authorized value
                        r.error = NON_REAL_OPERATION; //changing the type of error : non authorized operation
                    }
                    r.value = tan(result(e->left_operand, x).value);
                    break;
                case SINC:
                    if (e->left_operand->element.value.real == 0) { //non authorized value
                        r.error = DIV_BY_ZERO; //changing the type of error : division by zero
                    }
                    r.value = (sin(result(e->left_operand, x).value) /
                               result(e->left_operand, x).value); // definition of the function
                    break;
                case COSC:
                    if (e->left_operand->element.value.real == 0) { //non authorized value
                        r.error = DIV_BY_ZERO; //changing the type of error : division by zero
                    }
                    r.value = (cos(result(e->left_operand, x).value) /
                               result(e->left_operand, x).value); // definition of the function
                    break;
                case TANC:
                    if (e->left_operand->element.value.real == 0) { //non authorized value
                        r.error = DIV_BY_ZERO; //changing the type of error : division by zero
                    }
                    r.value = (tan(result(e->left_operand, x).value) /
                               result(e->left_operand, x).value); // definition of the function
                    break;
                case ABS:
                    r.value = fabs(result(e->left_operand, x).value);
                    break;
                case EXP:
                    r.value = exp(result(e->left_operand, x).value);
                    break;
                case LOG:
                    if (e->left_operand->element.value.real <= 0) { //non authorized value
                        r.error = NON_REAL_OPERATION; //changing the type of error : non authorized operation
                    }
                    r.value = log10(result(e->left_operand, x).value);
                    break;
                case LN:
                    if (e->left_operand->element.value.real <= 0) { //non authorized value
                        r.error = NON_REAL_OPERATION; //changing the type of error : non authorized operation
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
                    if (e->left_operand->element.value.real < 0) { //non authorized value
                        r.error = NON_REAL_OPERATION; //changing the type of error : non authorized operation
                    }
                    r.value = sqrt(result(e->left_operand, x).value);
                    break;
                case ARCSIN:
                    if (e->left_operand->element.value.real < -1 ||
                        e->left_operand->element.value.real > 1) { //non authorized values
                        r.error = NON_REAL_OPERATION; //changing the type of error : non authorized operation
                    }
                    r.value = asin(result(e->left_operand, x).value);
                    break;
                case ARCCOS:
                    if (e->left_operand->element.value.real < -1 ||
                        e->left_operand->element.value.real > 1) { //non authorized values
                        r.error = NON_REAL_OPERATION; //changing the type of error : non authorized operation
                    }
                    r.value = acos(result(e->left_operand, x).value);
                    break;
                case ARCTAN:
                    if (e->left_operand->element.value.real < -1 ||
                        e->left_operand->element.value.real > 1) { //non authorized values
                        r.error = NON_REAL_OPERATION; //changing the type of error : non authorized operation
                    }
                    r.value = atan(result(e->left_operand, x).value);
                    break;
                default: //if the function matches non of the cases above
                    r.value = 0; //assigning the value zero to the result because the function hasn't been recognized
                    break;
            }
        }

    }
    return r;
}


double test_evaluation() { //test function of the program : creating a tree and returning the value of f(x)
    double res = 0; //Value to return
    Result r;
    Entity e = malloc(sizeof(struct entitySt));

    /*
    // sin(9) x ln(2x)
    e->right_operand = malloc(sizeof(struct entitySt)); //allocating memory to the tree
    e->left_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand = malloc(sizeof(struct entitySt));
    e->left_operand->left_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand->right_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand->left_operand = malloc(sizeof(struct entitySt));

    e->element.token = OPERATOR; //main node is an operator
    e->element.value.operators = MULTIPLY; // the value of this operator is a multiply
    e->right_operand->element.token = FUNCTION; //right node is a function
    e->right_operand->element.value.functions = LN; // value of this function
    e->right_operand->left_operand->element.token = OPERATOR; // left node of the function is an operator
    e->right_operand->left_operand->element.value.operators = MULTIPLY;
    e->right_operand->left_operand->right_operand->element.token = REAL;
    e->right_operand->left_operand->left_operand->element.token = VARIABLE;
    e->right_operand->left_operand->right_operand->element.value.real = 2;
    e->left_operand->element.token = FUNCTION; //left node is a function
    e->left_operand->element.value.functions = SIN; // value of this function
    e->left_operand->left_operand->element.token = REAL; // left node of this function is a real
    e->left_operand->left_operand->element.value.real = 9; //value of this real

    e->left_operand->right_operand = NULL; // assigning NULL to every sons of node without sons
    e->left_operand->left_operand->left_operand = NULL;
    e->left_operand->left_operand->right_operand = NULL;
    e->right_operand->right_operand = NULL;
    e->right_operand->left_operand->right_operand->right_operand = NULL;
    e->right_operand->left_operand->right_operand->left_operand = NULL;
    e->right_operand->left_operand->left_operand->right_operand = NULL;
    e->right_operand->left_operand->left_operand->left_operand = NULL;
    */


    /*
    // exp(x) / cos(2x)
    e->right_operand = malloc(sizeof(struct entitySt)); //allocating memory to the tree
    e->left_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand = malloc(sizeof(struct entitySt));
    e->left_operand->left_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand->right_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand->left_operand = malloc(sizeof(struct entitySt));

    e->element.token = OPERATOR; //main node is an operator
    e->element.value.operators = DIVIDE; // the value of this operator is a divide
    e->right_operand->element.token = FUNCTION; //right node is a function
    e->right_operand->element.value.functions = COS; // value of this function
    e->right_operand->left_operand->element.token = OPERATOR; // left node of the function is an operator
    e->right_operand->left_operand->element.value.operators = MULTIPLY;
    e->right_operand->left_operand->right_operand->element.token = REAL;
    e->right_operand->left_operand->left_operand->element.token = VARIABLE;
    e->right_operand->left_operand->right_operand->element.value.real = 2;
    e->left_operand->element.token = FUNCTION; //left node is a function
    e->left_operand->element.value.functions = EXP; // value of this function
    e->left_operand->left_operand->element.token = VARIABLE; // left node of this function is a variable

    e->left_operand->right_operand = NULL; // assigning NULL to every sons of node without sons
    e->left_operand->left_operand->left_operand = NULL;
    e->left_operand->left_operand->right_operand = NULL;
    e->right_operand->right_operand = NULL;
    e->right_operand->left_operand->right_operand->right_operand = NULL;
    e->right_operand->left_operand->right_operand->left_operand = NULL;
    e->right_operand->left_operand->left_operand->right_operand = NULL;
    e->right_operand->left_operand->left_operand->left_operand = NULL;
    */


    // sqrt(x) - 6^x
    e->left_operand = malloc(sizeof(struct entitySt)); //allocating memory to the tree
    e->right_operand = malloc(sizeof(struct entitySt));
    e->left_operand->left_operand = malloc(sizeof(struct entitySt));
    e->right_operand->left_operand = malloc(sizeof(struct entitySt));
    e->right_operand->right_operand= malloc(sizeof(struct entitySt));

    e->element.token = OPERATOR; //main node is an operator
    e->element.value.operators = MINUS; // the value of this operator is a minus
    e->left_operand->element.token = FUNCTION; //left node is a function
    e->left_operand->element.value.operators = SQRT; // value of this function
    e->left_operand->left_operand->element.token = VARIABLE; // left node of this function is a variable
    e->right_operand->element.token = FUNCTION; //right node is a function
    e->right_operand->element.value.functions = POWER; // value of this function
    e->right_operand->left_operand->element.token = REAL; // left node of this function is a real
    e->right_operand->left_operand->element.value.real = 6;
    e->right_operand->right_operand->element.token = VARIABLE; //right node of this function is a variable

    e->left_operand->right_operand = NULL; // assigning NULL to every sons of node without sons
    e->left_operand->left_operand->left_operand = NULL;
    e->left_operand->left_operand->right_operand = NULL;
    e->right_operand->left_operand->left_operand = NULL;
    e->right_operand->left_operand->right_operand = NULL;
    e->right_operand->right_operand->left_operand = NULL;
    e->right_operand->right_operand->right_operand = NULL;



    r = result(e, 0.5); // calling the function that calculates f(x)
    res = r.value; //assigning the correct value to the returned value

    free( e->right_operand->left_operand);
    free (e->right_operand->right_operand) ;
    free(e->left_operand->left_operand );
    free( e->right_operand );
    free(e->left_operand );
    free (e);
    return res;
}
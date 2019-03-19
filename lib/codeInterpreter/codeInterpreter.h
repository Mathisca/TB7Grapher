#ifndef TB7GRAPHER_CODEINTERPRETER_H
#define TB7GRAPHER_CODEINTERPRETER_H


#include "../tokens.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

float result (Entity e, float x);
/**
 * @brief Calcule le f(x) du x donné en paramètre avce la focntion dans l'arbre en paramètre
 *
 * @param e l'arbre contenant la fonction
 * @param x la variable
 * @return f(x)
 *
 * @pre l'arbre existe
 * @post le calcul est valide
 * @invariant
 */


#endif //TB7GRAPHER_CODEINTERPRETER_H

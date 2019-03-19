#ifndef TB7GRAPHER_CODEINTERPRETER_H

#define TB7GRAPHER_CODEINTERPRETER_H


#include "../lib.h"

Result result (Entity e, double x);
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

double test_evaluation ();

#endif //TB7GRAPHER_CODEINTERPRETER_H

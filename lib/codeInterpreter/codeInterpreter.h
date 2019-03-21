/*
 * File: codeInterpreter.h
 * Names: AMYOT Flavie, SALIBA Louise
 */

#ifndef TB7GRAPHER_CODEINTERPRETER_H

#define TB7GRAPHER_CODEINTERPRETER_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include "../tokens.h"
/**
 * @brief Calcule le f(x) du x donné en paramètre avce la focntion dans l'arbre en paramètre
 *
 * @param e l'arbre contenant la fonction
 * @param x la variable
 * @return f(x)
 *
 * @pre l'arbre existe
 * @post le calcul est valide
 * @invariant //
 */
Result result (Entity e, double x);

/**
 * @brief Teste la fonction principale en créant un arbre comportant une fonction, appel de la fonction result pour obtenir f(x)
 *
 * @return f(x)
 *
 * @pre //
 * @post l'abre est crée et la fonction renvoie le résultat du calcul
 * @invariant //
 */
double test_evaluation ();


#endif //TB7GRAPHER_CODEINTERPRETER_H

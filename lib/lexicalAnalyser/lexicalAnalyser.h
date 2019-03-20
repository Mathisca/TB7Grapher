#include "../tokens.h"

#ifndef TB7GRAPHER_LEXICALANALYSER_H
#define TB7GRAPHER_LEXICALANALYSER_H


ElementList RecognizeLexemValue(ElementList e, char *saisie, int *i);

ElementList RecognizeLexemVariable(ElementList e, char *saisie, int *i);

ElementList RecognizeLexemOperators(ElementList e, char *saisie, int *i);

double convertirenreel(char *s);

ElementList RecognizeLexemParenthesis(ElementList e, char *saisie, int *i);

ElementList RecognizeLexemFunction(ElementList el, char *c, int *i);

ElementList RecognizeLexem(char *chaine);

ElementList Test();

#endif
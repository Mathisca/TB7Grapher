#ifndef TB7GRAPHER_SYNTAXANALYSER_H
#define TB7GRAPHER_SYNTAXANALYSER_H

#include "../lib.h"

Entity syntaxBuild(ElementList elementList);

ERRORS syntaxChecker(ElementList elementList);

Entity createEntity(Element e);

Entity createTree(ElementList elementList);

#endif //TB7GRAPHER_SYNTAXANALYSER_H

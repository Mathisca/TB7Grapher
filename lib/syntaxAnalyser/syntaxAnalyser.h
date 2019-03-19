#ifndef TB7GRAPHER_SYNTAXANALYSER_H
#define TB7GRAPHER_SYNTAXANALYSER_H

#include "../lib.h"

Entity syntaxBuild(ElementList);

ERRORS syntaxChecker(ElementList list);

Entity createEntity(Element);

Entity createTree(ElementList);

#endif //TB7GRAPHER_SYNTAXANALYSER_H

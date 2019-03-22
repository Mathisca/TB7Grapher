/*
 * File: syntaxAnalyser.h
 * Names: DELFORGE Bastien
 *        ALBRECHT Jérémy
 * Date: 20/03/2019
 */
#ifndef TB7GRAPHER_SYNTAXANALYSER_H
#define TB7GRAPHER_SYNTAXANALYSER_H

#include "../lib.h"

/**
 * @brief Check for the syntax of the expression and call createTree if syntax is correct, return an error otherwise
 * @param list Linked list of the user's input
 * @return Binary tree containing our expression, a single node with the error if there is one
 * @author DELFORGE Bastien
 * @author ALBRECHT Jérémy
 */
Entity syntaxBuild(ElementList);

/**
 * @brief Check for the expression syntax and return an error if the expression is incorrect and impossible to process
 * @param list Linked list containing the expression
 * @return NO_ERROR, or the given error
 *
 * @details 1. A bracket is mandatory after a declaration of a function
 * @details 2. Same number of opening and clsoing brackets
 * @details 3. No closing bracket before an opening one
 * @details 4. Mandatory expression in a function
 * @details 5. Two operators cannot be followed, unless it's a minus or a plus
 * @details 6. No operators like MULTIPLY, DIVIDE at the begin of expression
 *
 * @author DELFORGE Bastien
 * @author ALBRECHT Jérémy
 */
ERRORS syntaxChecker(ElementList);

/**
 * @brief Allocate the memory for a node of a binary tree
 *
 * @return an Entity object with left and right son NULL
 *
 * @author DELFORGE Bastien
 * @author ALBRECHT Jérémy
 */
Entity createEntity(Element);

/**
 * @brief Method used to create the binary tree
 * @attention is called recursively
 * @param list Linked list we want the binary tree
 * @return Entity
 * @author DELFORGE Bastien
 * @author ALBRECHT Jérémy
 */
Entity createTree(ElementList);

#endif //TB7GRAPHER_SYNTAXANALYSER_H

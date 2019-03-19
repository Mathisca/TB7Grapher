#ifndef TB7GRAPHER_GRAPHRENDERER_H
#define TB7GRAPHER_GRAPHRENDERER_H

#include "../lib.h"
#include "inputHandler.h"

void startMainLoop();

void render();

void processPoints();

static void makeText(char *text, int x, int y, int w, int h);

void reduceYSpan(int mod);

void increaseYSpan(int mod);

void nbGradChange(int mod);

void reduceXSpan(int mod);

void increaseXSpan(int mod);


#endif
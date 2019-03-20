#ifndef TB7GRAPHER_GRAPHRENDERER_H
#define TB7GRAPHER_GRAPHRENDERER_H

#include "../lib.h"
#include "inputHandler.h"

void * startMainLoop();

void render();

Point processPoints(Entity e);

void addEntity(Entity e, char *fct);

static void loadResources();

void recalculateAll();

static void makeText(char *text, int x, int y, int w, int h);

void nbGradChange(int mod);

void unzoom();

void zoom();

#endif
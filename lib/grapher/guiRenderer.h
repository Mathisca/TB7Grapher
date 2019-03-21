#ifndef TB7GRAPHER_GRAPHRENDERER_H
#define TB7GRAPHER_GRAPHRENDERER_H

#include "../lib.h"
#include "inputHandler.h"

#define ZOOMFACTOR 10
#define PRECISION 10000.0

void *startMainLoop();

void render();

static Point processPoints(Entity e);

void addEntity(Entity e, char *fct, SDL_Color color);

static void loadResources();

static void recalculateAll();

static void makeText(char *text, int x, int y, int w, int h);

void nbGradChange(int mod);

void unzoom();

void zoom();

#endif
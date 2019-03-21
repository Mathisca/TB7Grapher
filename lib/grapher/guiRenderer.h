#ifndef TB7GRAPHER_GRAPHRENDERER_H
#define TB7GRAPHER_GRAPHRENDERER_H

#include "../lib.h"
#include "inputHandler.h"

#define ZOOMFACTOR 10
#define DEFAULTSPAN 10.0
#define DEFAULTGRAD 10
#define PRECISION 10000.0

void *startMainLoop();

static void render();

static void freePoints(Point p);

static Point processPoints(Entity e);

void changeXSpan(int change);

void changeYSpan(int change);

void addEntity(Entity e, char *fct, SDL_Color color);

static void loadResources();

void togglePrintGrid();

static void recalculateAll();

static void makeText(char *text, int x, int y, int w, int h);

void nbGradChange(int mod);

void unzoom();

void zoom();

#endif
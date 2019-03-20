//
// Created by mathisca on 19/03/19.
//

#ifndef TB7GRAPHER_GUIMANAGER_H
#define TB7GRAPHER_GUIMANAGER_H

#include "../lib.h"

SDL_Window *gWindow;

static int initSDL();

static int createWindow();

static int createRenderer();

void getWindowWidth(int *w, int *h);

SDL_Renderer *getRenderer();

void startUserInterface();

void freeGraphics();

int initGraphics();

#endif //TB7GRAPHER_GUIMANAGER_H

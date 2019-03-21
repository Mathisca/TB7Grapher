//
// Created by mathisca on 19/03/19.
//

#ifndef TB7GRAPHER_INPUTHANDLER_H
#define TB7GRAPHER_INPUTHANDLER_H

#include "../lib.h"

#define CHANGEVALUE 2

void processEvents();

static void processKeyDown(SDL_Keysym);

void processConsoleInstructions();

void processMouseWheel(SDL_MouseWheelEvent event);

#endif //TB7GRAPHER_INPUTHANDLER_H

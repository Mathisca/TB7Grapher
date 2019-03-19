//
// Created by mathisca on 19/03/19.
//

#ifndef TB7GRAPHER_INPUTHANDLER_H
#define TB7GRAPHER_INPUTHANDLER_H

#include "../lib.h"

void processEvents();

static void processKeyDown(SDL_Keysym);

static void processMouseMotion(SDL_MouseMotionEvent key);

static void processMousePress(SDL_MouseButtonEvent key);

void processMouseWheel(SDL_MouseWheelEvent event);

#endif //TB7GRAPHER_INPUTHANDLER_H

#include "guiRenderer.h"
TTF_Font* Sans;  //this opens a font style and sets a size


void startMainLoop() {
    Sans = TTF_OpenFont("Sans.ttf", 1000);

    while(1) {
        processEvents();
        render();
    }
}


void render() {
    int width, height;
    getWindowWidth(&width, &height);


    SDL_Renderer *renderer = getRenderer();

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderDrawLine(renderer, width/3, 0, width/3, height);

    int graphX0 = width/3;
    int graphWidth = (width - graphX0);

    SDL_RenderDrawLine(renderer, graphX0, height/2, width, height/2);
    SDL_RenderDrawLine(renderer, (graphWidth) / 2 + graphX0, 0, (width - graphX0) / 2 + graphX0, height);


   // int gradInterval = (int) ((width - width / 3.0) / 20.0);

    for (int i = graphX0; i < width; i += (int) (width - width / 3.0) / 20.0) {
        SDL_RenderDrawLine(renderer, i, height/2 + 10, i, height/2 - 10);
    }



    if(Sans == NULL)
        log_error("Not found : %s", TTF_GetError());

    SDL_Color White = {0, 0, 0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "TB7Plotter", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = width/3; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect

//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture




    SDL_RenderPresent(renderer);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}
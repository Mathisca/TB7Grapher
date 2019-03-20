#include "grapher.h"

void userInterface() {
    log_info("Veuillez saisir la fonction à tracer :");

    char * function = malloc(sizeof(char) * 100);
    //scanf("%s", function);


    initGraphics();
    startMainLoop();

}
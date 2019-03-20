 #include "grapher.h"

void userInterface() {
    int select=0;
    int selectbis=0;
    int R,G,B,A;
    printf("Bienvenue sur TB7 Plotter, que voulez-vous faire? \n");
    printf("1. Ajouter une expression et la visualiser. \n");
    printf("2. Supprimer une expression. \n");
    scanf("%d", &select);
    switch (select) {
        case 1: {
            printf("Veuillez entrer votre expresion et appuyer sur Entrée. \n");
            char * function = malloc(sizeof(char) * 100);
            scanf("%s", function);
            printf("Appuyez sur 1 si vous souhaitez choisir la couleur de votre courbe. \n");
            printf("Appuyez sur 2 pour avoir la couleur par défaut. \n");
            scanf("%d", &selectbis);
            switch (selectbis){
                case 1: {
                    printf("Entrez le code RGBA correspondant en appuyant sur Entrée entre chaque code. \n");
                    scanf("%d %d %d %d", &R, &G, &B, &A);
                }
                case 2: {

                }
                default:{

                }
            }
            initGraphics();
            startMainLoop();
        }
        case 2: {
    }
        default: {

        }

    }
}
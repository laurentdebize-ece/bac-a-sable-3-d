#include "affichage.h"
#include "Jeu.h"
#include "COULEURS.h"


void afficher_la_grille(Jeu* jeu){
    for (int y = 0; y < jeu->ordre.y; y++) {
        for (int x = 0; x < jeu->ordre.x; x++) {
            printf("%d ", jeu->terrain[y][x]);
        }
        printf("\n");
    }
}

void afficher_menu_console(Jeu* jeu){
    int choix = 0;
    color(1, 0);
    printf("-------BIENVENUE DANS ECE-CITY CONSOLE -------- (v.APLHA)\n");
    color(15, 0);
    printf("\nMenu :\n\n");
    printf("1 : Lancer une partie\n");
    printf("2 : Sauvegarde \n");
    printf("3 : Charger une partie\n");
    printf("4 : Quitter\n");
    scanf(" %d", &choix);

    switch(choix){
        case 1:{
            afficher_la_grille(jeu);
            break;
        }
        case 2:{
            printf("\non a pas code\n");
            afficher_menu_console(jeu);
            break;
        }
        case 3:{
            printf("\non a pas code\n");
            afficher_menu_console(jeu);
            break;
        }
        case 4:{
            exit(0);
        }
    }
}



#include "affichage.h"
#include "Jeu.h"

void afficher_la_grille(Jeu* jeu){
    for (int y = 0; y < jeu->ordre_en_y; y++) {
        for (int x = 0; x < jeu->ordre_en_x; x++) {
            printf("%d ", jeu->terrain[y][x]);
        }
        printf("\n");
    }
}

void afficher_menu_console(Jeu* jeu){
    printf("");

}

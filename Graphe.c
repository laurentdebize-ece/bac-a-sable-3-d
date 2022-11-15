#include "Graphe.h"

Jeu *lire_graphe(char *nomFichier) {
    Jeu *grille;
    FILE *ifs = fopen(nomFichier, "r");
    int ordre_x;
    int ordre_y;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs, "%d", &ordre_x);
    fscanf(ifs, "%d", &ordre_y);
    grille = (Jeu *) malloc(sizeof(Jeu));
    grille->terrain = (int**) malloc(ordre_y * sizeof(int*));

    for (int i = 0; i < ordre_y; i++) {
        grille->terrain[i] = (int*) malloc(ordre_x * sizeof(int));
    }
    for (int i = 0; i < ordre_y; i++) {
        for (int j = 0; j < ordre_x; j++) {
            fscanf(ifs, " %d", &grille->terrain[i][j]);
        }
    }
    grille->ordre_en_x = ordre_x;
    grille->ordre_en_y = ordre_y;
    return grille;
}

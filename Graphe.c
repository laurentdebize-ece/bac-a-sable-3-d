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
    grille->fichier = nomFichier;
    grille->ordre.x = ordre_x;
    grille->ordre.y = ordre_y;
    return grille;
}


// creer graphe en fonction de la matrice (Sommet : case du jeu  et Aretes : poids de 1 liaison entre les cases)

// bfs pour chercher les chemins entre usine et habitation (en utilisant les routes (reseau))    cherche la distance

//creer graphe avec liste d'adjacence avec la distance entre les usines et les maisons en parcourant la route (dijstra)

//modifier graphe (meme liste d'adjacence) avec des flots pour l'alimentation des habitations





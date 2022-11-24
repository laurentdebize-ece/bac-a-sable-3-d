#ifndef TEMPLATE_RAYLIB_GRAPHE_H
#define TEMPLATE_RAYLIB_GRAPHE_H

#include "Jeu.h"

Jeu *lire_graphe(char *nomFichier);

void creer_matrice_centrale(int nb_centrale, int nb_maison);
int** init_conexite_route(Jeu* jeu);
int** destruction_centrale_matrice(Jeu jeu, int** matrice_centrale, int nb_maison, int nb_centrale, int num_centrale);
int** destruction_maison_matrice(Jeu jeu, int** matrice_centrale, int nb_maison, int nb_centrale, int num_maison);
int** construction_maison_matrice(Jeu jeu, int** matrice_centrale, int nb_maison, int nb_centrale);


#endif //TEMPLATE_RAYLIB_GRAPHE_H

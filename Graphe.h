#ifndef TEMPLATE_RAYLIB_GRAPHE_H
#define TEMPLATE_RAYLIB_GRAPHE_H
#include "Jeu.h"
void initialisation_Grille();
Jeu *lire_graphe();
void enregistrer_Grille(Jeu* jeu);
void ajout_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y);

#endif //TEMPLATE_RAYLIB_GRAPHE_H

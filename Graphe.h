#ifndef TEMPLATE_RAYLIB_GRAPHE_H
#define TEMPLATE_RAYLIB_GRAPHE_H
#include "Jeu.h"
void initialisation_Grille();
void lire_graphe(Jeu* jeu);
void enregistrer_Grille(Jeu* jeu);
void suppression_batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute);


#endif //TEMPLATE_RAYLIB_GRAPHE_H

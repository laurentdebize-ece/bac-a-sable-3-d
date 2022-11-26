#ifndef TEMPLATE_RAYLIB_GRAPHE_H
#define TEMPLATE_RAYLIB_GRAPHE_H
#include "Jeu.h"
//
void initialisation_Grille();
void lire_graphe(Jeu* jeu);
Jeu *lire_graphe_console();
void enregistrer_Grille(Jeu* jeu);
void ajout_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute);
void suppression_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute);


Coordonnee position_maison(Jeu jeu, int x, int y);
Coordonnee position_usine(Jeu jeu, int x, int y, int type_usine);
Coordonnee position_batiment(Jeu jeu, int x, int y);

#endif //TEMPLATE_RAYLIB_GRAPHE_H

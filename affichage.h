#ifndef TEMPLATE_RAYLIB_AFFICHAGE_H
#define TEMPLATE_RAYLIB_AFFICHAGE_H
#include "Jeu.h"
#include <raylib.h>
#include <stdlib.h>
#define RESOLUTION_X 1024
#define RESOLUTION_Y 768

void afficher_fenetre();
void afficher_la_grille(Jeu* jeu);
void afficherJeu(Jeu* jeu);

typedef struct Map {
    unsigned int tilesX;            // Number of tiles in X axis
    unsigned int tilesY;            // Number of tiles in Y axis
    unsigned char *tileIds;         // Tile ids (tilesX*tilesY), defines type of tile to draw
    unsigned char *tileFog;         // Tile fog state (tilesX*tilesY), defines if a tile has fog or half-fog
} Map;



#endif //TEMPLATE_RAYLIB_AFFICHAGE_H

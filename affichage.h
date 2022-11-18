#ifndef TEMPLATE_RAYLIB_AFFICHAGE_H
#define TEMPLATE_RAYLIB_AFFICHAGE_H
#include "Jeu.h"

void affichage_Boucle_G(Jeu* jeu);
void afficher_fenetre_menu(Jeu* jeu, Vector2 pos_Souris, int* timer, float* rectAplha, float* sonAlpha);
void afficher_animation(Jeu* jeu, int* ballPositionX, int* ballRadius, float* ballAlpha, int* state, int* framesCounter);
void afficher_la_grille(Jeu* jeu);
void affi_bouton(Jeu* jeu, int page, int image, Vector2 mousePoint, char* nom);
void afficherJeu(Jeu* jeu);

typedef struct Map {
    unsigned int x;            // Number of tiles in X axis
    unsigned int y;            // Number of tiles in Y axis
    unsigned char *tileIds;         // Tile ids (tilesX*tilesY), defines type of tile to draw
    unsigned char *tileFog;         // Tile fog state (tilesX*tilesY), defines if a tile has fog or half-fog
} Map;



#endif //TEMPLATE_RAYLIB_AFFICHAGE_H

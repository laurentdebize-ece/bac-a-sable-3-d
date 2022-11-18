#ifndef TEMPLATE_RAYLIB_JEU_H
#define TEMPLATE_RAYLIB_JEU_H
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
enum {animation_Lancement, menu_principale, en_jeu, regles, credis, nbPages};
enum {img_menu, img_boutonoff, img_boutonJouer, img_boutonSauvegarder, img_boutonRegles, img_boutonCredits, nbImages};

enum {vide, reseau, maison, chateau_deau, usine_electrique, nbBatiments};

enum {son_Bouton, son_menu, nbSons};

typedef struct S_Image{
    bool charge;
    Texture2D texture2D;
    Image image2D;
    Rectangle source_Rec;
    Rectangle pos_Rec;
    int x;
    int y;
    float frame_hauteur;
    float frame_longueur;
    bool action_sur_click;
}S_Image;

typedef struct Batiment{
    char* nom;
    int capacite;
    int nb_habitants;
}Batiment;

typedef struct Jeu{
    bool quitter;
    int page_actuel;
    int** terrain;
    int ordre_en_x;
    int ordre_en_y;
    int nb_habitants_tot;
    int argent;
    int production_eau_restante;
    int production_elec_restante;
    Batiment batiments[nbBatiments];
    S_Image tabImages[nbPages][nbImages];
    Sound tabSon[nbSons];
}Jeu;


#include "Macros.h"
#include "initialisation.h"
#include "affichage.h"
#include "raylib.h"
#include "Graphe.h"
#include "reasings.h"


#endif //TEMPLATE_RAYLIB_JEU_H

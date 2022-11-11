#ifndef TEMPLATE_RAYLIB_JEU_H
#define TEMPLATE_RAYLIB_JEU_H
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>

enum {vide, reseau, maison, chateau_deau, usine_electrique, nbBatiments};
enum {boutonoff, nbImages};

typedef struct Batiment{
    char* nom;
    int capacite;
    int nb_habitants;
}Batiment;

typedef struct Jeu{
    int** terrain;
    int ordre_en_x;
    int ordre_en_y;
    int nb_habitants_tot;
    int argent;
    int production_eau_restante;
    int production_elec_restante;
    Batiment* batiments;
    Texture2D TabImages[nbImages];
}Jeu;


#include "Macros.h"
#include "initialisation.h"
#include "affichage.h"
#include "Graphe.h"


#endif //TEMPLATE_RAYLIB_JEU_H

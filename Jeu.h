#ifndef TEMPLATE_RAYLIB_JEU_H
#define TEMPLATE_RAYLIB_JEU_H
#include <stdio.h>
//#include <raylib.h>
#include <stdlib.h>

enum {vide, reseau, maison, chateau_deau, usine_electrique, nbBatiments};

typedef struct Batiment{
    char* nom;
    int capacite;
    int nb_habitants;
}Batiment;

typedef struct Jeu{
    int** terrain;
    int fenetre;
    int ordre_en_x;
    int ordre_en_y;
    int nb_habitants_tot;
    int argent;
    int production_eau_restante;
    int production_elec_restante;
    Batiment* batiments;
}Jeu;


#endif //TEMPLATE_RAYLIB_JEU_H

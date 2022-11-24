#ifndef TEMPLATE_RAYLIB_JEU_H
#define TEMPLATE_RAYLIB_JEU_H
#include <stdio.h>
//#include <raylib.h>
#include <stdlib.h>
#include "Graphe.h"
#include "Macros.h"
enum {vide, route, terrain_vague, chateau_deau, centrale, nbBatiments};

typedef struct Coordonnee {
    int x;
    int y;
}Coordonnee;

typedef struct Batiment{
    Coordonnee* cases_adjacentes;
    Coordonnee* cases;
    char* nom;
    int capacite;
    int nb_habitants;
}Batiment;

typedef struct Jeu{
    char* fichier;
    int** terrain;
    Coordonnee ordre;
    int nb_habitants_tot;
    int argent;
    int production_eau_restante;
    int production_elec_restante;
    Batiment batiments[nbBatiments];
}Jeu;

Coordonnee* initialisation_case_ajacentes(Coordonnee coordonnee_batiment,int longueur, int hauteur );
#endif //TEMPLATE_RAYLIB_JEU_H

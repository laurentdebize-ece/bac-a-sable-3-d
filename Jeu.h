#ifndef TEMPLATE_RAYLIB_JEU_H
#define TEMPLATE_RAYLIB_JEU_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

//TODO: LISTE CHAINE POUR BATIMENTS
//#include <raylib.h>

enum {vide, reseau, maison, chateau_deau, usine_electrique, nbBatiments};

typedef struct Coordonnee {
    int x;
    int y;
}Coordonnee;

typedef struct Batiment{
    Coordonnee taille;
    Coordonnee cases;
    char* nom;
    int capacite;
    int nb_habitants;
    struct Batiment* next;
}Batiment;

typedef struct Jeu{
    bool en_cours;
    bool fichier;
    int** terrain;
    Coordonnee ordre;
    int nb_habitants_tot;
    int argent;
    int production_eau_restante;
    int production_elec_restante;
    Batiment batiments[nbBatiments];
}Jeu;

// TODO: NE PAS CHANGER LORDRE DES INCLUDES IMPORTANT !!!

//mettez vos includes ici :)
#include "Macros.h"
#include "affichage.h"
#include "Graphe.h"
#include "COULEURS.h"

int difference_entre_2_nombres_VALEURABSOLUE(int a, int b);
Jeu* initialisation();
void initialisation_CONSTANTE(Jeu* j);


#endif

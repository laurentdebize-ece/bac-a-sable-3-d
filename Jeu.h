#ifndef TEMPLATE_RAYLIB_JEU_H
#define TEMPLATE_RAYLIB_JEU_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

//#include <raylib.h>

enum {vide, reseau, maison, chateau_deau, usine_electrique, nbBatiments};

typedef struct Coordonnee {
    int x;
    int y;
}Coordonnee;

typedef struct Batiment{
    Coordonnee taille;
    Coordonnee** cases;
    char* nom;
    int capacite;
    int nb_habitants;
}Batiment;

typedef struct Jeu{
    bool fichier;
    int** terrain;
    Coordonnee ordre;
    int nb_habitants_tot;
    int argent;
    int production_eau_restante;
    int production_elec_restante;
    Batiment* batiments[nbBatiments];
}Jeu;

// TODO: NE PAS CHANGER LORDRE DES INCLUDES IMPORTANT !!!

//mettez vos includes ici :)
#include "Macros.h"
#include "affichage.h"
#include "Graphe.h"
#include "COULEURS.h"

Jeu* initialisation();

void initialise(char* nomFichier,Jeu* j);
void sauvegarder(char* nomFichier,Jeu* j);
void modifier(char* nomFichier,Jeu* j);
#endif

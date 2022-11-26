#ifndef BAC_A_SABLE_2_MATRICE_ADJACENCE_H
#define BAC_A_SABLE_2_MATRICE_ADJACENCE_H

#include "Jeu.h"


void ajouter_batiment_matrice_adjacence(Jeu* jeu, int type_batiment, Coordonnee coordonnee_nouveau);
void alimenter_1_maison_elec(Jeu* jeu, int numero_maison, int numero_centrale);
void distribuer_electricite(Jeu* jeu, int** matrice_adjacence);

#endif //BAC_A_SABLE_2_MATRICE_ADJACENCE_H



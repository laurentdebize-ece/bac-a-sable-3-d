//
// Created by chape on 24/11/2022.
//

#include "matrice_adjacence.h"

int** creer_matrice_adjacence(Jeu* jeu, int type_batiment){
    int** matrice = (int**) calloc(jeu->batiments[maison]->nb_batiment, sizeof(int*));
    for (int i = 0; i < jeu->batiments[maison]->nb_batiment; i++) {
        matrice[i] = (int*) calloc(jeu->batiments[type_batiment]->nb_batiment, sizeof(int));
    }
    return matrice;
}
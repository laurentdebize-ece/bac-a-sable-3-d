#include "matrice_adjacence.h"

int** creer_matrice_adjacence(Jeu* jeu, int type_batiment){
    switch (type_batiment) {
        case chateau_deau: {
            int** matrice = (int**) calloc(jeu->nb_maison, sizeof(int*));
            for (int i = 0; i < jeu->nb_maison; i++) {
                matrice[i] = (int*) calloc(jeu->nb_chateau_eau, sizeof(int));
            }
            return matrice;
        }
        case usine_electrique: {
            int** matrice = (int**) calloc(jeu->nb_maison, sizeof(int*));
            for (int i = 0; i < jeu->nb_maison; i++) {
                matrice[i] = (int*) calloc(jeu->nb_usine_electrique, sizeof(int));
            }
            return matrice;
        }
        default:{
            break;
        }
    }
}

void alimenter_1_maison_elec(Jeu* jeu, int numero_maison, int numero_centrale){
    Batiment* liste_maison = jeu->batiments[maison];
    Batiment* liste_centrale = jeu->batiments[usine_electrique];
    while (numero_maison != 0){
        liste_maison = liste_maison->next;
        numero_maison--;
    }
    while (numero_centrale != 0){
        liste_centrale = liste_maison->next;
        numero_centrale--;
    }
    if (liste_maison->alimente_elec == FALSE && (liste_maison->nb_habitants >= liste_centrale->capacite)){
        liste_maison->alimente_elec = TRUE;
        liste_centrale->capacite -= liste_maison->nb_habitants;
    }
}

void distribuer_electricite(Jeu* jeu, int** matrice_adjacence){
    for (int i = 0; i < jeu->nb_maison; i++) {
        for (int j = 0; j < jeu->nb_usine_electrique; ++j) {
            if (matrice_adjacence[i][j] == 1){
                alimenter_1_maison_elec(jeu, i, j);
            }
        }
    }
}
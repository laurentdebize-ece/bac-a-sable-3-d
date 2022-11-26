#include "matrice_adjacence.h"
#include "jeu.h"

int** creer_matrice_adjacence(Jeu* jeu, int type_batiment){
    switch (type_batiment) {
        case chateau_deau: {
            Matrice_batiment** matrice = (Matrice_batiment **) calloc(jeu->batiments[maison]->nb_batiment, sizeof(Matrice_batiment *));
            for (int i = 0; i < jeu->batiments[maison]->nb_batiment; i++) {
                matrice[i] = (Matrice_batiment*) calloc(jeu->batiments[chateau_deau]->nb_batiment + 1, sizeof(Matrice_batiment));
            }
            return matrice;
        }
        case usine_electrique: {
            Matrice_batiment **matrice = (Matrice_batiment **) calloc(jeu->batiments[maison]->nb_batiment,
                                                                      sizeof(Matrice_batiment *));
            for (int i = 0; i < jeu->batiments[maison]->nb_batiment; i++) {
                matrice[i] = (Matrice_batiment *) calloc(jeu->batiments[usine_electrique]->nb_batiment + 1, sizeof(Matrice_batiment));
            }
            for (int i = 0; i < jeu->batiments[maison]->nb_batiment; i++) {
                for (int j = 0; j < (jeu->batiments[usine_electrique]->nb_batiment + 1); j++) {
                    if (j == (jeu->batiments[usine_electrique]->nb_batiment)) {
                        matrice[i][j].batiments[0].x = jeu->matrice_connexite_electricite[i][j - 1].batiments[0].x;
                        matrice[i][j].batiments[0].y = jeu->matrice_connexite_electricite[i][j - 1].batiments[0].y;
                        matrice[i][j].batiments[1].x = coordonnee_nouveau.x;
                        matrice[i][j].batiments[1].y = coordonnee_nouveau.y;
                    } else {
                        matrice[i][j].batiments[0].x = jeu->matrice_connexite_electricite[i][j].batiments[0].x;
                        matrice[i][j].batiments[0].y = jeu->matrice_connexite_electricite[i][j].batiments[0].y;
                        matrice[i][j].batiments[1].x = jeu->matrice_connexite_electricite[i][j].batiments[1].x;
                        matrice[i][j].batiments[1].y = jeu->matrice_connexite_electricite[i][j].batiments[1].y;
                        matrice[i][j].distance = jeu->matrice_connexite_electricite[i][j].distance;
                        matrice[i][j].connexite = jeu->matrice_connexite_electricite[i][j].connexite;
                        matrice[i][j].capacite_utilise = jeu->matrice_connexite_electricite[i][j].capacite_utilise;
                    }
                }
            }
            for (int i = 0; i < jeu->batiments[maison]->nb_batiment; i++) {
                free(jeu->matrice_connexite_electricite[i]);
                jeu->matrice_connexite_electricite[i] = NULL;
            }
            free(jeu->matrice_connexite_electricite);
            jeu->matrice_connexite_electricite = NULL;
            jeu->matrice_connexite_electricite = (Matrice_batiment **) calloc(jeu->batiments[maison]->nb_batiment,sizeof(Matrice_batiment *));
            for (int i = 0; i < jeu->batiments[maison]->nb_batiment; i++) {
                jeu->matrice_connexite_electricite[i] = (Matrice_batiment *) calloc(jeu->batiments[usine_electrique]->nb_batiment + 1, sizeof(Matrice_batiment));
            }
            for (int i = 0; i < jeu->batiments[maison]->nb_batiment; i++) {
                for (int j = 0; j < (jeu->batiments[usine_electrique]->nb_batiment + 1); j++) {
                    jeu->matrice_connexite_electricite[i][j].batiments[0].x = matrice[i][j].batiments[0].x;
                    jeu->matrice_connexite_electricite[i][j].batiments[0].y = matrice[i][j].batiments[0].y;
                    jeu->matrice_connexite_electricite[i][j].batiments[1].x = matrice[i][j].batiments[1].x;
                    jeu->matrice_connexite_electricite[i][j].batiments[1].y = matrice[i][j].batiments[1].y;
                    jeu->matrice_connexite_electricite[i][j].distance = matrice[i][j].distance;
                    jeu->matrice_connexite_electricite[i][j].connexite = matrice[i][j].connexite;
                    jeu->matrice_connexite_electricite[i][j].capacite_utilise = matrice[i][j].capacite_utilise;
                }
            }
            for (int i = 0; i < jeu->batiments[maison]->nb_batiment ; i++) {
                free(matrice[i]);
                matrice[i]=NULL;
            }
            free(matrice);
            matrice = NULL;
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
    for (int i = 0; i < jeu->batiments[maison]->nb_batiment; i++) {
        for (int j = 0; j < jeu->batiments[usine_electrique]->nb_batiment; ++j) {
            if (matrice_adjacence[i][j] == 1){
                alimenter_1_maison_elec(jeu, i, j);
            }
        }
    }
}
//
// Created by RENAUD Maxime on 24/11/2022.
//

#include "BFS.h"

// BFS pour les composantes connexes des routes
// matrices d'adjacences entre les composantes connexe des routes, les centrales, les chateaux d'eaux
// et les maisons
void BFS_connexite(int** matrice_connexite_route, int** matrice_centrale, int** matrice_chateau_eau, Coordonnee tuile, int num_connexite){
    Coordonnee* cases_adjacentes = initialisation_case_ajacentes(tuile, 1, 1 );
    Coordonnee** new_cases_adjacentes;// pour switch
    matrice_connexite_route[tuile.y][tuile.x] = num_connexite; //route parcouru, route marqué
    // nombre d'adjacences théorique si on prend en comptes toutes les adjacences possiles des cases marquées (même celles avec des coordonnées négatives)
    int nb_adjacence_theorique = 4; // 4 fois le nombre de cases marquées car chaque cases ont 4 adjacences
    int nb_adjacence = 0; // nombre de routes découvertes
    int new_nb_adjacence;
    int* valeur_adjacence = calloc(nb_adjacence_theorique,sizeof(int));// valeurs des cases adjacentes découvertes initialisé à 0
    for (int i = 0; i < nb_adjacence_theorique; i++){
        // si case adjacente = route pas marquée, valeur_adjacence prend la valeur de la route et on incrémente le nombre de routes découvertes
        if((cases_adjacentes[i].y >= 0) && (cases_adjacentes[i].x) ) {
            if (matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x] != 0
                && matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x] != 2
                && matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x] != 3
                && matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x] != 4
                && matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x] != num_connexite) {
                valeur_adjacence[i] = matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x];
                nb_adjacence++;
            }
        }
    }
    new_cases_adjacentes = (Coordonnee**) malloc(nb_adjacence * sizeof(Coordonnee*));
    int y = 0;
    for (int i = 0; i < nb_adjacence_theorique ; i++){

        if (valeur_adjacence[i] != 0){
            new_cases_adjacentes[y] = initialisation_case_ajacentes(cases_adjacentes[i], 1, 1);
            y++;
            if (valeur_adjacence[i] == 1){
                valeur_adjacence[i] = num_connexite;

            }
            else {
                if (valeur_adjacence[i] < num_connexite){

                    for(int k = 0; k < ORDRE_EN_Y; k++){
                        for(int l = 0; l < ORDRE_EN_X ; l++){
                            if (matrice_connexite_route[k][l] == num_connexite){
                                matrice_connexite_route[k][l] = valeur_adjacence[i];
                            }
                        }
                    }
                    num_connexite = valeur_adjacence[i];
                }
                else{
                    for(int k = 0; k < ORDRE_EN_Y ; k++){
                        for(int l = 0; l < ORDRE_EN_X ; l++){
                            if (matrice_connexite_route[k][l] == valeur_adjacence[i]){
                                matrice_connexite_route[k][l] = num_connexite;
                            }
                        }
                    }
                }
            }
        }

    }
    new_nb_adjacence = nb_adjacence;
    free (cases_adjacentes);
    cases_adjacentes = NULL;
    free(valeur_adjacence);
    valeur_adjacence = NULL;

    while (new_cases_adjacentes != NULL) {
        if (nb_adjacence != 0) {


            cases_adjacentes = calloc(nb_adjacence_theorique * nb_adjacence, sizeof(Coordonnee));
            int x = 0;
            for (int i = 0; i < nb_adjacence; i++) {
                for (int j = 0; j < nb_adjacence_theorique; j++) {
                    cases_adjacentes[x].y = new_cases_adjacentes[i][j].y;
                    cases_adjacentes[x].x = new_cases_adjacentes[i][j].x;
                    x++;
                }
            }
            for (int i = 0; i < nb_adjacence_theorique; i++) {
                free(new_cases_adjacentes[i]);
                new_cases_adjacentes[i] = NULL;
            }
            free(new_cases_adjacentes);
            new_cases_adjacentes = NULL;
            nb_adjacence = new_nb_adjacence;
            new_nb_adjacence = 0;
            valeur_adjacence = calloc(nb_adjacence_theorique * nb_adjacence,
                                      sizeof(int));// valeurs des cases adjacentes découvertes initialisé à 0
            for (int i = 0; i < nb_adjacence_theorique * nb_adjacence; i++) {
                // si case adjacente = route pas marquée, valeur_adjacence prend la valeur de la route et on incrémente le nombre de routes découvertes
                if ((cases_adjacentes[i].y >= 0) && (cases_adjacentes[i].x)) {
                    if (matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x] != 0
                        && matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x] != 2
                        && matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x] != 3
                        && matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x] != 4
                        && matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x] != num_connexite) {
                        valeur_adjacence[i] = matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x];
                        new_nb_adjacence++;
                    }
                }
            }
            new_cases_adjacentes = (Coordonnee **) malloc(nb_adjacence * sizeof(Coordonnee *));
            y = 0;
            for (int i = 0; i < nb_adjacence_theorique; i++) {

                if (valeur_adjacence[i] != 0) {
                    new_cases_adjacentes[y] = initialisation_case_ajacentes(cases_adjacentes[i], 1, 1);
                    y++;
                    if (valeur_adjacence[i] == 1) {
                        valeur_adjacence[i] = num_connexite;

                    } else {
                        if (valeur_adjacence[i] < num_connexite) {

                            for (int k = 0; k < ORDRE_EN_Y; k++) {
                                for (int l = 0; l < ORDRE_EN_X; l++) {
                                    if (matrice_connexite_route[k][l] == num_connexite) {
                                        matrice_connexite_route[k][l] = valeur_adjacence[i];
                                    }
                                }
                            }
                            num_connexite = valeur_adjacence[i];
                        } else {
                            for (int k = 0; k < ORDRE_EN_Y; k++) {
                                for (int l = 0; l < ORDRE_EN_X; l++) {
                                    if (matrice_connexite_route[k][l] == valeur_adjacence[i]) {
                                        matrice_connexite_route[k][l] = num_connexite;
                                    }
                                }
                            }
                        }
                    }
                }

            }
            new_nb_adjacence = nb_adjacence;
            free(cases_adjacentes);
            cases_adjacentes = NULL;
            free(valeur_adjacence);
            valeur_adjacence = NULL;

        } else{
            for (int i = 0; i < nb_adjacence_theorique; i++) {
                free(new_cases_adjacentes[i]);
                new_cases_adjacentes[i] = NULL;
            }
            free(new_cases_adjacentes);
            new_cases_adjacentes = NULL;
        }
    }
 }

/* BFS_PCC(batiment, matrice_chateau_eau){
 for (i, i < (LONGUEUR*LARGEUR); i++){
    if(batiment.adjacence[i]==
*/
int** init_conexite_route(Jeu* jeu){
    int** matrice_connexite_route = (int**) malloc(ORDRE_EN_Y * sizeof(int*));
    for (int i = 0; i < ORDRE_EN_Y; ++i) {
        matrice_connexite_route[i] = (int*) malloc(ORDRE_EN_X * sizeof(int));
    }
    for (int j = maison; j < nbBatiments ; j++) {
        int longueur = jeu->batiments[j]->taille.x;
        int largeur = jeu->batiments[j]->taille.y;
        if (jeu->batiments[j]->next != NULL) {
            int num_connexite = 50;
            for (jeu->batiments[j]->next; jeu->batiments[j]->next != NULL; jeu->batiments[j]->next = jeu->batiments[j]->next->next) {
                for (int i; i < (longueur * largeur );
                i++){
                    if (matrice_connexite_route[jeu->batiments[j]->next->cases_adjacentes[i].y][jeu->batiments[j]->next->cases_adjacentes[i].x] == 1) {
                        BFS_connexite(matrice_connexite_route, jeu->batiments[j]->next->cases_adjacentes[i], num_connexite);
                        num_connexite++;
                    }

                }
            }
        }
    }
    return matrice_connexite_route;
}

#include "BFS.h"

// BFS pour les composantes connexes des routes
// matrices d'adjacences entre les composantes connexe des routes, les centrales, les chateaux d'eaux
// et les maisons
void BFS_connexite(int** matrice_connexite_route, Coordonnee tuile, int num_connexite){
    Coordonnee* cases_adjacentes = initialisation_case_ajacentes(tuile, 1, 1 );
    Coordonnee** new_cases_adjacentes;// pour switch
    matrice_connexite_route[tuile.y][tuile.x] = num_connexite; //route parcourue, route marqué
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
    printf("ok 1\n");
    if (nb_adjacence != 0) {
        new_cases_adjacentes = (Coordonnee **) malloc(nb_adjacence * sizeof(Coordonnee *));
        int y = 0;
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
    } else{
        new_cases_adjacentes == NULL;
    }
    new_nb_adjacence = nb_adjacence;
    free (cases_adjacentes);
    cases_adjacentes = NULL;
    free(valeur_adjacence);
    valeur_adjacence = NULL;
    printf("ok 2\n");
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
            int y = 0;
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
    Batiment* batiment = calloc(1, sizeof(Batiment));

    int** matrice_connexite_route = (int**) malloc(ORDRE_EN_Y * sizeof(int*));
    for (int i = 0; i < ORDRE_EN_Y; i++) {
        matrice_connexite_route[i] = (int*) malloc(ORDRE_EN_X * sizeof(int));
    }
    for (int i = 0; i < ORDRE_EN_Y; i++) {
        for (int j = 0; j < ORDRE_EN_X; j++) {
            matrice_connexite_route[i][j] = jeu->terrain[i][j];
        }
    }
    printf("matrice_connexite_route initialiser\n");
    for (int j = maison; j < nb_type_batiments ; j++) {
        batiment->next = jeu->batiments[j]->next;
        int nb_batiment;
        switch (j) {
            case maison :
                nb_batiment = jeu->batiments[maison]->nb_batiment;
                break;
            case chateau_deau :
                nb_batiment = jeu->batiments[chateau_deau]->nb_batiment;
                break;
            case usine_electrique :
                nb_batiment = jeu->batiments[usine_electrique]->nb_batiment;
                break;
        }
        printf("switch case ok %d\n",nb_batiment);
        int longueur = jeu->batiments[j]->taille.x;
        int largeur = jeu->batiments[j]->taille.y;
        if (jeu->batiments[j]->next != NULL) {
            int num_connexite = 50;
            for (int k=0; k < nb_batiment ; k++) {
                if (k!=0){
                    batiment->next = batiment->next->next;
                }
                for (int i; i < ((longueur + largeur) * 2);i++){
                    if (matrice_connexite_route[batiment->next->cases_adjacentes[i].y][batiment->next->cases_adjacentes[i].x] == 1) {
                        BFS_connexite(matrice_connexite_route, batiment->next->cases_adjacentes[i], num_connexite);
                        num_connexite++;
                    }

                }
            }
        }
    }
    return matrice_connexite_route;
}

void connexite_route_ajout_batiment(Jeu* jeu, Batiment* nouveau){
    for (int i = 0; i < nouveau->taille.y; i++) {
        for (int j = 0; j < nouveau->taille.x; ++j) {
            jeu->matrice_connexite_route[nouveau->co.y + i][nouveau->co.x +j] = jeu->terrain[nouveau->co.y + i][nouveau->co.x +j];
        }
    }
    for (int i = 0; i < ((nouveau->taille.x + nouveau->taille.y ) * 2 ); i++) {
        if (jeu->matrice_connexite_route[nouveau->cases_adjacentes[i].y][nouveau->cases_adjacentes[i].x] == 1){
            BFS_connexite(jeu->matrice_connexite_route,nouveau->cases_adjacentes[i],jeu->num_connexite);
            jeu->num_connexite++;
        }
    }
}

void connexite_route_ajout_route(Jeu* jeu, Coordonnee debut, Coordonnee fin){
    int connexe = 0;
    int batiment_a_cote = 0;
    Coordonnee* cases_adjacentes = initialisation_case_ajacentes(debut,debut.x - fin.x + 1, debut.y - fin.y + 1);
    for (int i = 0; i < ((debut.x - fin.x + 1 + debut.y - fin.y + 1) * 2); i++){
        if (jeu->matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x]> 10){
            if (connexe == 0) {
                connexe = 1;
                for (int j = 0; j < (debut.y - fin.y); j++) {
                    for (int k = 0; k < (debut.x - fin.y); k++) {
                        jeu->matrice_connexite_route[debut.y + j][debut.x +j] = jeu->matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x];
                    }
                }
            }
            else{
                if (jeu->matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x] < jeu->matrice_connexite_route[debut.x][debut.y]){
                    int num_c = jeu->matrice_connexite_route[debut.x][debut.y];
                    for (int j = 0; j < ORDRE_EN_Y; j++) {
                        for (int k = 0; k < ORDRE_EN_X; k++) {
                            if (jeu->matrice_connexite_route[j][k] == num_c){
                                jeu->matrice_connexite_route[j][k] = jeu->matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x];
                            }
                        }
                    }
                } else{
                    int num_c = jeu->matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x];
                    for (int j = 0; j < ORDRE_EN_Y; j++) {
                        for (int k = 0; k < ORDRE_EN_X; k++) {
                            if (jeu->matrice_connexite_route[j][k] == num_c){
                                jeu->matrice_connexite_route[j][k] = jeu->matrice_connexite_route[debut.x][debut.y];
                            }
                        }
                    }
                }
            }
        }
        else if ((connexe == 0) && (batiment_a_cote == 0) && ((jeu->matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x] > 1) && (jeu->matrice_connexite_route[cases_adjacentes[i].y][cases_adjacentes[i].x] < 10))){
            batiment_a_cote = 1;
            jeu->num_connexite++;
            for (int j = 0; j < (debut.y - fin.y); j++) {
                for (int k = 0; k < (debut.x - fin.y); k++) {
                    jeu->matrice_connexite_route[debut.y + j][debut.x +j] = jeu->num_connexite;
                }
            }
        }
    }
    if (connexe && batiment_a_cote){
        jeu->num_connexite++;
    }
}

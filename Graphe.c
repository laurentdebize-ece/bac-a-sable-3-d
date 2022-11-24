#include "Graphe.h"

Jeu *lire_graphe(char *nomFichier) {
    Jeu *grille;
    FILE *ifs = fopen(nomFichier, "r");
    int ordre_x;
    int ordre_y;

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs, "%d", &ordre_x);
    fscanf(ifs, "%d", &ordre_y);
    grille = (Jeu *) malloc(sizeof(Jeu));
    grille->terrain = (int**) malloc(ordre_y * sizeof(int*));

    for (int i = 0; i < ordre_y; i++) {
        grille->terrain[i] = (int*) malloc(ordre_x * sizeof(int));
    }
    for (int i = 0; i < ordre_y; i++) {
        for (int j = 0; j < ordre_x; j++) {
            fscanf(ifs, " %d", &grille->terrain[i][j]);
        }
    }
    grille->fichier = nomFichier;
    grille->ordre.x = ordre_x;
    grille->ordre.y = ordre_y;
    return grille;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////CREATION MATRICE//////////////////////////////////////////////////////////////

void creer_matrice_centrale(int nb_centrale, int nb_maison){
    if (nb_centrale != 0 && nb_maison != 0){
        int** matrice_centrale = (int**) calloc(nb_maison,sizeof(int*));
        for (int i = 0; i < nb_maison; i++) {
            matrice_centrale[i] = (int*) calloc(nb_centrale, sizeof(int));
        }
    }
}

/*Coordonnee* cases_adjacentes(Coordonnee case_actuelle){
    Coordonnee tab_adjacence_case[4];
    tab_adjacence_case[0].x = case_actuelle.x - 1;
    tab_adjacence_case[1].x = case_actuelle.x;
    tab_adjacence_case[2].x = case_actuelle.x + 1;
    tab_adjacence_case[3].x = case_actuelle.x;
    tab_adjacence_case[0].y = case_actuelle.y;
    tab_adjacence_case[1].y = case_actuelle.y + 1;
    tab_adjacence_case[2].y = case_actuelle.y;
    tab_adjacence_case[3].y = case_actuelle.y - 1;
    return tab_adjacence_case;
}*/

void actualiser_matrice_adjacence_centrale_construction_maison(Jeu jeu, int** matrice_centrale, int nb_maison){
    Coordonnee case_actuelle;
    Coordonnee* tab_adjacence_case = initialisation_case_ajacentes(case_actuelle,1,1);

}
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

                    for(int k = 0; k < LARGEUR ; k++){
                        for(int l = 0; l < LONGUEUR ; l++){
                            if (matrice_connexite_route[k][l] == num_connexite){
                                matrice_connexite_route[k][l] = valeur_adjacence[i];
                            }
                        }
                    }
                    num_connexite = valeur_adjacence[i];
                }
                else{
                    for(int k = 0; k < LARGEUR ; k++){
                        for(int l = 0; l < LONGUEUR ; l++){
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

                            for (int k = 0; k < LARGEUR; k++) {
                                for (int l = 0; l < LONGUEUR; l++) {
                                    if (matrice_connexite_route[k][l] == num_connexite) {
                                        matrice_connexite_route[k][l] = valeur_adjacence[i];
                                    }
                                }
                            }
                            num_connexite = valeur_adjacence[i];
                        } else {
                            for (int k = 0; k < LARGEUR; k++) {
                                for (int l = 0; l < LONGUEUR; l++) {
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
    int** matrice_connexite_route = (int**) malloc(LARGEUR * sizeof(int*));
    for (int i = 0; i < LARGEUR; ++i) {
        matrice_connexite_route[i] = (int*) malloc(LONGUEUR * sizeof(int));
    }
    if (Batiment!= NULL){
        int num_connexite = 50;
        for ( batiment->next; batiment!=NULL; batiment->next){
            for(int i; i<(longueur*largeur batiment) ; i++){
                if(matrice_connexite_route[batiment.adjacence[i].y][batiment.adjacence[i].x] == 1){
                BFS_connexite(matrice_connexite_route, batiment.adjacence[i], num_connexite);
                num_connexite++;
            }

        }
    }
    return matrice_connexite_route;
}
//
void actualiser_matrice_connexite_route(int**);

void actualiser_matrice_adjacence(Jeu jeu, int** matrice_centrale, int batiment_action){
    //BFS POUR rechercher les plus courts chemin entre les chateaux d'eaux et les maisons
    /*  M1 M2 M3
     C1
     C2
     C3
     */
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////MODIFICATION TAILLE MATRICE///////////////////////////////////////////////////


int** destruction_centrale_matrice(Jeu jeu, int** matrice_centrale, int nb_maison, int nb_centrale, int num_centrale){
    int** new_matrice_centrale = (int**) calloc(nb_maison, sizeof(int*));
    for (int i = 0; i < nb_maison; i++) {
        new_matrice_centrale[i] = (int*) calloc(nb_centrale - 1, sizeof(int));
    }

    for (int i = 0; i < nb_maison; i++){
        for (int j = 0; j < nb_centrale; j++) {
            if ( j < num_centrale) {
                new_matrice_centrale[i][j] = matrice_centrale[i][j];
            }
            else if  (j > num_centrale){
                new_matrice_centrale[i][j-1] = matrice_centrale[i][j];
            }
        }
    }
    for (int i = 0; i < nb_maison; i++) {
        free(matrice_centrale[i]);
    }
    free(matrice_centrale);
    return new_matrice_centrale;
}

int** construction_centrale_matrice(Jeu jeu, int** matrice_centrale, int nb_maison, int nb_centrale){
    int** new_matrice_centrale = (int**) calloc(nb_maison, sizeof(int*));
    for (int i = 0; i < nb_maison; i++) {
        new_matrice_centrale[i] = (int*) calloc(nb_centrale + 1, sizeof(int));
    }

    for (int i = 0; i < nb_maison; i++){
        for (int j = 0; j < nb_centrale; j++) {
            new_matrice_centrale[i][j] = matrice_centrale[i][j];
        }
    }
    for (int i = 0; i < nb_maison; i++) {
        free(matrice_centrale[i]);
    }
    free(matrice_centrale);
    return new_matrice_centrale;
}

int** destruction_maison_matrice(Jeu jeu, int** matrice_centrale, int nb_maison, int nb_centrale, int num_maison){
    int** new_matrice_centrale = (int**) calloc(nb_maison - 1, sizeof(int*));
    for (int i = 0; i < nb_maison; i++) {
        new_matrice_centrale[i] = (int*) calloc(nb_centrale, sizeof(int));
    }

    for (int i = 0; i < nb_maison; i++){
        for (int j = 0; j < nb_centrale; j++) {
            if ( i < num_maison) {
                new_matrice_centrale[i][j] = matrice_centrale[i][j];
            }
            else if  (i > num_maison){
                new_matrice_centrale[i-1][j] = matrice_centrale[i][j];
            }
        }
    }
    for (int i = 0; i < nb_maison; i++) {
        free(matrice_centrale[i]);
    }
    free(matrice_centrale);
    return new_matrice_centrale;
}

int** construction_maison_matrice(Jeu jeu, int** matrice_centrale, int nb_maison, int nb_centrale){
    int** new_matrice_centrale = (int**) calloc(nb_maison + 1, sizeof(int*));
    for (int i = 0; i < nb_maison; i++) {
        new_matrice_centrale[i] = (int*) calloc(nb_centrale, sizeof(int));
    }

    for (int i = 0; i < nb_maison; i++){
        for (int j = 0; j < nb_centrale; j++) {
            new_matrice_centrale[i][j] = matrice_centrale[i][j];
        }
    }
    for (int i = 0; i < nb_maison; i++) {
        free(matrice_centrale[i]);
    }
    free(matrice_centrale);
    return new_matrice_centrale;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////MODIFICATION CONTENU MATRICE///////////////////////////////////////////////////







// bfs pour chercher les chemins entre usine et habitation (en utilisant les routes (reseau))   cherche la distance entre les deux
//a partir du fichier texte

//creer matrice d'adjacence

// pour les centrales pas de poids

// pour les chateau deau avec poids = distance






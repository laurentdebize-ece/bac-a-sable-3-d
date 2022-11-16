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


void actualiser_matrice_adjacence(Jeu jeu, int** matrice_centrale, int batiment_action){
    //BFS POUR REMPLIR LA MATRICE D'ADJACENCE
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






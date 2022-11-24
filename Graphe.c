#include "Graphe.h"

void lire_graphe(Jeu* jeu) {
    FILE *ifs = fopen(NOM_DU_FICHIER, "r");
    int ordre_x;
    int ordre_y;
    int argent;

    if (!ifs) {
        printf("Vous n'avez pas encore de graphe\n");
        initialisation_Grille();
        ifs = fopen(NOM_DU_FICHIER, "r");
    }

    fscanf(ifs, "%d", &ordre_x);
    fscanf(ifs, "%d", &ordre_y);
    fscanf(ifs, "%d", &argent);

    if(jeu->en_cours ==0)jeu->terrain = (int**) malloc(ordre_y * sizeof(int*));

    for (int i = 0; i <= ordre_y; i++) {
        if (jeu->en_cours == 0) jeu->terrain[i] = (int*) malloc(ordre_x * sizeof(int));
    }
    jeu->en_cours = 1;
    for (int i = 0; i <= ordre_y; i++) {
        for (int j = 0; j <= ordre_x; j++) {
            fscanf(ifs, " %d", &jeu->terrain[i][j]);
        }

    }
    /*if(grille->terrain[0][0] == NULL){
        color(5, 0);
        printf("Vous n'avez pas encore de graphe\n");
        color(14, 0);
        printf("Creation d'un graphe ... ...\n");
        color(15, 0);
        initialisation_Grille();
        ifs = fopen(NOM_DU_FICHIER, "r");
    }*/
    jeu->ordre.x = ordre_x;
    jeu->ordre.y = ordre_y;
    jeu->argent = argent;
    fclose(ifs);
}

void initialisation_Grille(){
    printf("Creation d'un graphe ... ...\n");
    FILE *ifs = fopen(NOM_DU_FICHIER, "w");
    fprintf(ifs, "%d\n", ORDRE_EN_X);
    fprintf(ifs, "%d\n", ORDRE_EN_Y);
    fprintf(ifs, "%d\n", ARGENT_DE_DEBUT);
    for (int i = 0; i <= ORDRE_EN_Y; i++) {
        for (int j = 0; j <= ORDRE_EN_X; j++) {
            fprintf(ifs, "%d ", vide);
        }
        fprintf(ifs, "\n");
    }
    fclose(ifs);
    //on ne ferme pas ce fichier car nous allons le lire juste apres dans le cas ou nous avons pas de fichier
}

void supprimerGrille(){
    FILE *ifs = fopen(NOM_DU_FICHIER, "w");
}


void enregistrer_Grille(Jeu* jeu){
    FILE *ifs = fopen(NOM_DU_FICHIER, "w");
    if(ifs==NULL){
        printf("Erreur lors de l'1ouverture d'un fichier");
        exit(1);
    }
    fprintf(ifs, "%d\n",jeu->ordre.x);
    fprintf(ifs, "%d\n",jeu->ordre.y);
    fprintf(ifs, "%d\n",jeu->argent);
    for (int i = 0; i <= jeu->ordre.y; i++) {
        for (int j = 0; j <= jeu->ordre.x; j++) {
            fprintf(ifs, "%d ", jeu->terrain[i][j]);
        }
        fprintf(ifs, "\n");
    }
    fclose(ifs);
}



void suppression_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute){
    //il me faut les co des batiments deja place (x,y) grace au liste chaine donc j'att...
}
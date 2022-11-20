#include "Graphe.h"

Jeu *lire_graphe() {
    Jeu* grille;
    FILE *ifs = fopen(NOM_DU_FICHIER, "r");
    int ordre_x;
    int ordre_y;
    int argent;

    if (!ifs) {
        color(5, 0);
        printf("Vous n'avez pas encore de graphe\n");
        color(15, 0);
        initialisation_Grille();
        ifs = fopen(NOM_DU_FICHIER, "r");
    }

    fscanf(ifs, "%d", &ordre_x);
    fscanf(ifs, "%d", &ordre_y);
    fscanf(ifs, "%d", &argent);

    grille = (Jeu *) malloc(sizeof(Jeu));
    grille->terrain = (int**) malloc(ordre_y * sizeof(int*));

    for (int i = 0; i <= ordre_y; i++) {
        grille->terrain[i] = (int*) malloc(ordre_x * sizeof(int));
    }
    for (int i = 0; i <= ordre_y; i++) {
        for (int j = 0; j <= ordre_x; j++) {
            fscanf(ifs, " %d", &grille->terrain[i][j]);
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
    grille->ordre.x = ordre_x;
    grille->ordre.y = ordre_y;
    grille->argent = argent;
    fclose(ifs);
    return grille;
}

void initialisation_Grille(){
    color(14, 0);
    printf("Creation d'un graphe ... ...\n");
    sleep(1);
    color(15, 0);
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

void ajout_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute){
    bool obstacle = FALSE;
    int y_temporaire = co_y;

    if (co_xroute !=-1 || co_yroute != -1){
        int x_temporaire = co_x;
        int x_distance=difference_entre_2_nombres_VALEURABSOLUE(co_x, co_xroute), y_distance=difference_entre_2_nombres_VALEURABSOLUE(co_y, co_yroute);
        for (int i = 0; i < x_distance ; i++) {
            if (jeu->terrain[co_y][x_temporaire] != 0){
                obstacle = TRUE;
                break;
            }
            if (co_x < co_xroute){
                x_temporaire++;
            }else x_temporaire--;
        }
        for (int i = 0; i <= y_distance ; i++) {
            if (jeu->terrain[y_temporaire][co_x] != 0){
                obstacle = TRUE;
                break;
            }
            if (co_y < co_yroute){
                y_temporaire++;
            }else y_temporaire--;
        }
        x_temporaire = co_x;
        y_temporaire = co_y;
        if (obstacle == FALSE){
            for (int i = 0; i < x_distance ; i++) {
                jeu->terrain[co_y][co_x] = nomDuBatiment;
                if (co_x < co_xroute){
                    co_x++;
                }else co_x--;
            }
            for (int i = 0; i <= y_distance ; i++) {
                jeu->terrain[co_y][co_x] = nomDuBatiment;
                if (co_y < co_yroute){
                    co_y++;
                }else co_y--;
            }
            color(1, 0);
            printf("La construction : %s, est un succes !\n", jeu->batiments[nomDuBatiment].nom);
            color(15, 0);
        } else {
            color(5, 0);
            printf("Vous ne pouvez pas construire ici, un obstacle vous en empeche !\n");
            color(15, 0);
        }
    }else{
        for (int i = 0; i < jeu->batiments[nomDuBatiment]->taille.y ; i++) {
            for (int j = 0; j < jeu->batiments[nomDuBatiment]->taille.x; j++) {
                if (jeu->terrain[co_y][co_x + j] != 0){
                    obstacle = TRUE;
                    break;
                }
            }
            if (obstacle == TRUE){
                break;
            }
            y_temporaire ++;
        }
        if (obstacle == FALSE){
            for (int i = 0; i < jeu->batiments[nomDuBatiment]->taille.y ; i++) {
                for (int j = 0; j < jeu->batiments[nomDuBatiment]->taille.x; j++) {
                    jeu->terrain[co_y][co_x + j] = nomDuBatiment;
                }co_y ++;
            }
            color(1, 0);
            printf("La construction : %s, est un succes !\n", jeu->batiments[nomDuBatiment]->nom);
            color(15, 0);
        } else {
            color(5, 0);
            printf("Vous ne pouvez pas construire ici, un obstacle vous en empeche !\n");
            color(15, 0);
        }
    }
}


void suppression_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute){
    //il me faut les co des batiments deja place (x,y) grace au liste chaine donc j'att...
}
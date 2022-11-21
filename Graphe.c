#include "Graphe.h"

Jeu *lire_graphe() {
    Jeu* grille;
    FILE *ifs = fopen(NOM_DU_FICHIER, "r");
    int ordre_x;
    int ordre_y;
    int argent;

    int retenueMaison = -1;
    int retenurChateauEau = 0;
    int usineElectrique = 0;
    bool enCours = FALSE;

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
            if(grille->terrain[i][j] == 2 || grille->terrain[i][j] == 3 || grille->terrain[i][j] == 4){
                chargementListe(grille,grille->terrain[i][j],i,&j,&ifs);
            }
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
            printf("La construction : %s, est un succes !\n", jeu->batiments[nomDuBatiment]->nom);
            color(15, 0);
        } else {
            color(5, 0);
            printf("Vous ne pouvez pas construire ici, un obstacle vous en empeche !\n");
            detruireBatiment(jeu,co_x,co_y,nomDuBatiment);
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
            detruireBatiment(jeu,co_x,co_y,nomDuBatiment);
            color(15, 0);
        }
    }
}


void suppression_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute){
    //il me faut les co des batiments deja place (x,y) grace au liste chaine donc j'att...
}



Coordonnee position_maison(Jeu jeu, int x, int y){
    Coordonnee position_maison;
    position_maison.x = -1;
    position_maison.y = -1;
    bool batiment_trouve = FALSE;
    Batiment* batiment_actuel = jeu.batiments[maison];
    while(batiment_trouve == FALSE){
        for(int i = 0; i < TAILLE_MAISON; i++){
            if (x - i == batiment_actuel->x){
                position_maison.x = batiment_actuel->x;
            }
            if (y - i == batiment_actuel->y){
                position_maison.y = batiment_actuel->y;
            }
        }
        if (position_maison.x != -1 && position_maison.y != -1){
            batiment_trouve = TRUE;
        }
        batiment_actuel = batiment_actuel->next;
    }
    return position_maison;
}

Coordonnee position_usine(Jeu jeu, int x, int y, int type_usine){
    Coordonnee position_usine;
    position_usine.x = -1;
    position_usine.y = -1;
    bool batiment_trouve = FALSE;
    Batiment* batiment_actuel = jeu.batiments[type_usine];
    while(batiment_trouve == FALSE){
        for(int i = 0; i < LONGUEUR_BATIMENTS; i++) {
            if (x - i == batiment_actuel->x) {
                position_usine.x = batiment_actuel->x;
            }
        }
        for(int i = 0; i < LARGEUR_BATIMENTS; i++) {
            if (y - i == batiment_actuel->y) {
                position_usine.y = batiment_actuel->y;
            }
        }
        if (position_usine.x != -1 && position_usine.y != -1){
            batiment_trouve = TRUE;
        }
        batiment_actuel = batiment_actuel->next;
    }
    return position_usine;
}

Coordonnee position_batiment(Jeu jeu, int x, int y){
    Coordonnee postion_batiment;
    int type_batiment = jeu.terrain[y][x];
    switch (type_batiment) {
        case vide : {
            break;
        }
        case reseau : {
            postion_batiment.x = x;
            postion_batiment.y = y;
            break;
        }
        case maison : {
            postion_batiment = position_maison(jeu, x, y);
            break;
        }
        case chateau_deau : {
            postion_batiment = position_usine(jeu, x, y, chateau_deau);
            break;
        }
        case usine_electrique : {
            postion_batiment = position_usine(jeu, x, y, usine_electrique);
            break;
        }
        default : {
            break;
        }

    }
    return postion_batiment;
}



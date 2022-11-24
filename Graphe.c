#include "Graphe.h"

/*void lire_graphe(Jeu* jeu) {
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
}*/
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
    fscanf(ifs,"%d",&grille->modeDeJeu);
    for (int i = 0; i <= ordre_y; i++) {
        grille->terrain[i] = (int*) malloc(ordre_x * sizeof(int));
    }

    for (int i = 0; i < nbBatiments; i++){
        grille->batiments[i] = (Batiment*) malloc(sizeof (Batiment));
    }
    grille->batiments[maison] = NULL;
    grille->batiments[chateau_deau] = NULL;
    grille->batiments[usine_electrique] = NULL;


    for (int i = 0; i <= ordre_y; i++) {
        for (int j = 0; j <= ordre_x; j++) {
            fscanf(ifs, " %d", &grille->terrain[i][j]);
        }
    }

    for (int y = 0; y <= ordre_y; y++) {
        for (int x = 0; x <= ordre_x; x++) {
            int stadeEvo = 0;
            if(grille->terrain[y][x] == 2 || grille->terrain[y][x] == 3 || grille->terrain[y][x] == 4 || grille->terrain[y][x] >= 20){
                if(grille->terrain[y][x] >= 20){
                    stadeEvo = grille->terrain[y][x] - 20;
                    grille->terrain[y][x] = 2;
                }
                chargementListe(grille,grille->terrain[y][x],y,&x,&ifs,stadeEvo);
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
    Batiment* parcours = jeu->batiments[maison];
    FILE *ifs = fopen(NOM_DU_FICHIER, "w");
    if(ifs==NULL){
        printf("Erreur lors de l'1ouverture d'un fichier");
        exit(1);
    }
    fprintf(ifs, "%d\n",jeu->ordre.x);
    fprintf(ifs, "%d\n",jeu->ordre.y);
    fprintf(ifs, "%d\n",jeu->argent);
    fprintf(ifs,"%d\n",jeu->modeDeJeu);
    for (int i = 0; i <= jeu->ordre.y; i++) {
        for (int j = 0; j <= jeu->ordre.x; j++) {
            bool passe = FALSE;
            if(jeu->terrain[i][j] == 2 && jeu->batiments[maison] != NULL){
                do{
                    if(i == parcours->y && j == parcours->x){
                        fprintf(ifs, "%d ", jeu->terrain[i][j] + 18 + parcours->stadeEvolution);
                        passe = TRUE;
                    }
                    parcours = parcours->next;
                }while(parcours == jeu->batiments[maison]);
                if(passe == FALSE){
                    fprintf(ifs, "%d ", jeu->terrain[i][j]);
                }

            }
            else{fprintf(ifs, "%d ", jeu->terrain[i][j]);}
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
                if (jeu->argent - COUT_ROUTE >= 0){
                    jeu->terrain[co_y][co_x] = nomDuBatiment;
                    jeu->argent-= COUT_ROUTE;
                    if (co_x < co_xroute){
                        co_x++;
                    }else co_x--;
                }

            }
            for (int i = 0; i <= y_distance ; i++) {
                if (jeu->argent - COUT_ROUTE >= 0){
                    jeu->terrain[co_y][co_x] = nomDuBatiment;
                    jeu->argent-= COUT_ROUTE;
                    if (co_y < co_yroute){
                        co_y++;
                    }else co_y--;
                }

            }
            color(1, 0);
            printf("La construction : route, est un succes !\n");
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
        if (obstacle == TRUE){
            for (int i = 0; i < x_distance ; i++) {
                jeu->terrain[co_y][co_x] = 0;
                if (co_x < co_xroute){
                    co_x++;
                }else co_x--;
            }
            for (int i = 0; i <= y_distance ; i++) {
                jeu->terrain[co_y][co_x] = 0;
                if (co_y < co_yroute){
                    co_y++;
                }else co_y--;
            }
            color(1, 0);
            printf("La destruction : route, est un succes !\n");
            color(15, 0);
        } else {
            color(5, 0);
            printf("Il n'y a pas de route a detruire !\n");
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
        if (obstacle == TRUE){
            for (int i = 0; i < jeu->batiments[nomDuBatiment]->taille.y ; i++) {
                for (int j = 0; j < jeu->batiments[nomDuBatiment]->taille.x; j++) {
                    jeu->terrain[co_y][co_x + j] = 0;
                }co_y ++;
            }
            color(1, 0);
            printf("La destruction : %s, est un succes !\n", jeu->batiments[nomDuBatiment]->nom);
            color(15, 0);
        } else {
            color(5, 0);
            printf("Il n'y a rien a detruire ici !\n");
            color(15, 0);
        }
    }
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
            printf("Cette case est vide\n");
            postion_batiment.x = -1;
            postion_batiment.y = -1;
            break;
        }
        case reseau : {
            postion_batiment.x = x;
            postion_batiment.y = y;
            printf("Cette case est une route placée en (%d,%d)\n", x, y);
            break;
        }
        case maison : {
            postion_batiment = position_maison(jeu, x, y);
            printf("Cette case correspond a une maison placee en (%d,%d)\n", postion_batiment.x, postion_batiment.y);
            break;
        }
        case chateau_deau : {
            postion_batiment = position_usine(jeu, x, y, chateau_deau);
            printf("Cette case correspond a un chateau d'eau place en (%d,%d)\n", postion_batiment.x, postion_batiment.y);
            break;
        }
        case usine_electrique : {
            postion_batiment = position_usine(jeu, x, y, usine_electrique);
            printf("Cette case correspond a une centrale electrique placee en (%d,%d)\n", postion_batiment.x, postion_batiment.y);
            break;
        }
        default : {
            break;
        }

    }
    return postion_batiment;
}
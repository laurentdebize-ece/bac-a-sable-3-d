#include "verification.h"

/*void verification_batiment_peut_se_placer(Jeu* jeu, int nomDuBatiment, Vector2 position1, Vector2 co_route){
    ajout_Batiment_Grille(jeu, nomDuBatiment, position1.x, position1.y, co_route.x, co_route.y);
}

void ajout_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute){
    bool obstacle = 0;
    int y_temporaire = co_y;

    if (co_xroute !=-1 || co_yroute != -1){
        int x_temporaire = co_x;
        int x_distance=difference_entre_2_nombres_VALEURABSOLUE(co_x, co_xroute), y_distance=difference_entre_2_nombres_VALEURABSOLUE(co_y, co_yroute);
        for (int i = 0; i < x_distance ; i++) {
            if (jeu->terrain[co_y][x_temporaire] != 0){
                obstacle = 1;
                break;
            }
            if (co_x < co_xroute){
                x_temporaire++;
            }else x_temporaire--;
        }
        for (int i = 0; i <= y_distance ; i++) {
            if (jeu->terrain[y_temporaire][co_x] != 0){
                obstacle = 1;
                break;
            }
            if (co_y < co_yroute){
                y_temporaire++;
            }else y_temporaire--;
        }
        x_temporaire = co_x;
        y_temporaire = co_y;
        if (obstacle == 0){
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
            printf("La construction : route, est un succes !\n");
        } else {
            printf("Vous ne pouvez pas construire ici, un obstacle vous en empeche !\n");
            detruireBatiment(jeu,co_x,co_y,nomDuBatiment);
        }
    }else{
        for (int i = 0; i < jeu->batiments[nomDuBatiment]->taille.y ; i++) {
            for (int j = 0; j < jeu->batiments[nomDuBatiment]->taille.x; j++) {
                if (jeu->terrain[co_y][co_x + j] != 0){
                    obstacle = 1;
                    break;
                }
            }
            if (obstacle == 1){
                break;
            }
            y_temporaire ++;
        }
        if (obstacle == 0){
            for (int i = 0; i < jeu->batiments[nomDuBatiment]->taille.y ; i++) {
                for (int j = 0; j < jeu->batiments[nomDuBatiment]->taille.x; j++) {
                    jeu->terrain[co_y][co_x + j] = nomDuBatiment;
                }co_y ++;
            }
            printf("La construction : %s, est un succes !\n", jeu->batiments[nomDuBatiment]->nom);
        } else {
            printf("Vous ne pouvez pas construire ici, un obstacle vous en empeche !\n");
            detruireBatiment(jeu,co_x,co_y,nomDuBatiment);
        }
    }
}*/
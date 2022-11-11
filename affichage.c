#include "Jeu.h"
void print_message_error_construire_hors_map(){
    color (12, 0);
    printf("\n VOUS NE POUVEZ PAS CONSTRUIRE EN DEHORS DES LIMITES DE LA MAP !!!\n\n");
    color(15, 0);
}

void afficher_menu_console(Jeu* jeu){
    int choix = 0;
    color(1, 0);
    printf("-------BIENVENUE DANS ECE-CITY CONSOLE -------- (v.APLHA)\n");
    color(15, 0);
    printf("\nMenu :\n\n");
    printf("0 : Revenir a la partie en cours\n");
    printf("1 : Lancer une partie\n");
    printf("2 : Sauvegarde \n");
    printf("3 : Charger une partie\n");
    printf("4 : Quitter\n");
    printf("9 : delet.txt\n");
    scanf(" %d", &choix);
    switch(choix){
        case 0:{
            if (jeu == NULL){
                color(12, 0);
                printf("Vous ne pouvez pas revenir a une partie que vous n'avez pas commence\n");
                color(15, 0);
                break;
            } else{
                afficher_choix_joueur(jeu);
            }
        }
        case 1:{
            jeu = initialisation();
            afficher_choix_joueur(jeu);
            break;
        }
        case 2:{
            if (jeu == NULL){
                printf("vous ne pouvez pas sauvegarder car vous n'avez pas charge de partie.\n");
                break;
            }else {
                printf("SAUVEGARDE EN COURS...\n");
                enregistrer_Grille(jeu);
                sleep(2);
                printf("SAUVEGARDE EFFECTUEE\n");
                break;
            }

        }
        case 3:{
            printf("CHARGEMENT EN COURS...\n");
            jeu = lire_graphe(jeu);
            sleep(1);
            initialisation_CONSTANTE(jeu);
            printf("CHARGEMENT TERMINE !\n");
            afficher_choix_joueur(jeu);
            break;

        }
        case 4:{
            exit(0);
        }
        case 9:{
            remove(NOM_DU_FICHIER);
            color (5, 0);
            printf("\nFICHIER DETRUIT\n");
            color (15, 0);
        }
    }
    afficher_menu_console(jeu);
}

void afficher_choix_joueur(Jeu* jeu){
    int choix = 0;
    int co_x=0, co_y=0, co_x1=-1, co_y1=-1;
    color(12, 0);
    printf("\t\t\t\t------------------- ECE - CITY -------------------\t\t\t\t");
    color(15, 0);
    printf("Temps : \n");
    printf("argent : %d\t\t\t", jeu->argent);
    color(11, 0);
    printf("eau total restant : %d\t\t\t", jeu->production_eau_restante);
    color(14, 0);
    printf("elec total restant : %d\n", jeu->production_elec_restante);
    color(15, 0);
    printf("\nChoix :\n");
    printf("0 : Revenir au Menu Principale\n");
    printf("1 : placer une route\n");
    printf("2 : placer une maison\n");
    printf("3 : placer un chateau d eau\n");
    printf("4 : placer une usine elec\n");
    printf("9 : ~~~~ AFFICHER LA MAP ~~~~\n");
    scanf(" %d", &choix);
    switch (choix) {
        case 0:{
            afficher_menu_console(jeu);
        }
        case reseau:{
            color(10, 0);
            printf("\nCoordonnees du point initiale? (x / y)\n");
            scanf(" %d %d", &co_x, &co_y);
            printf("\nCoordonnees du point final? (x / y)\n");
            color(15, 0);
            scanf(" %d %d", &co_x1, &co_y1);
            if (co_x<0 || co_y<0 || co_x1<0 || co_y1<0 || co_x>ORDRE_EN_X || co_y>ORDRE_EN_Y || co_x1>ORDRE_EN_X || co_y1>ORDRE_EN_Y){
                print_message_error_construire_hors_map();
                break;
            }
            ajout_Batiment_Grille(jeu, reseau, co_x, co_y, co_x1, co_y1);
            sleep(1);
            break;
        }
        case maison:{
            color(10, 0);
            printf("\nCoordonnees ? (x / y)\n");
            color(15, 0);
            scanf(" %d %d", &co_x, &co_y);
            if (co_x<0 || co_y<0 ||  co_x>ORDRE_EN_X || co_y>ORDRE_EN_Y){
                print_message_error_construire_hors_map();
                break;
            }
            ajout_Batiment_Grille(jeu, maison, co_x, co_y, co_x1, co_y1);
            sleep(1);
            break;
        }
        case chateau_deau:{
            color(10, 0);
            printf("\nCoordonnees ? (x / y)\n");
            color(15, 0);
            scanf(" %d %d", &co_x, &co_y);
            if (co_x<0 || co_y<0 ||  co_x>ORDRE_EN_X || co_y>ORDRE_EN_Y){
                print_message_error_construire_hors_map();
                break;
            }
            ajout_Batiment_Grille(jeu, chateau_deau, co_x, co_y, co_x1, co_y1);
            sleep(1);
            break;
        }
        case usine_electrique:{
            color(10, 0);
            printf("\nCoordonnees ? (x / y)\n");
            color(15, 0);
            scanf(" %d %d", &co_x, &co_y);
            if (co_x<0 || co_y<0 ||  co_x>ORDRE_EN_X || co_y>ORDRE_EN_Y){
                print_message_error_construire_hors_map();
                break;
            }
            ajout_Batiment_Grille(jeu, usine_electrique, co_x, co_y, co_x1, co_y1);
            sleep(1);
            break;
        }
        case 9:{
            afficher_la_grille(jeu);
            break;
        }

    }
    afficher_choix_joueur(jeu);
}

void afficher_la_grille(Jeu* jeu){
    for (int y = 0; y < jeu->ordre.y; y++) {
        for (int x = 0; x < jeu->ordre.x; x++) {
            if (jeu->terrain[y][x] == vide){
                color(0, 0);
            }else if(jeu->terrain[y][x] == reseau){
                color(8, 0);
            }else if(jeu->terrain[y][x] == maison){
                color(12, 0);
            }else if(jeu->terrain[y][x] == chateau_deau){
                color(11, 0);
            }else if(jeu->terrain[y][x] == usine_electrique){
                color(14, 0);
            }
            printf("%d ", jeu->terrain[y][x]);
            color(15, 0);
        }
        printf("\n");
    }
}




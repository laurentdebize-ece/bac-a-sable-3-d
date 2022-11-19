#include "Jeu.h"


void afficher_menu_console(Jeu* jeu){
    int choix = 0;
    Batiment* listeMaison = NULL;
    Batiment* listeChateauEau = NULL;
    Batiment* listeUsineElectrique = NULL;

    color(1, 0);
    printf("-------BIENVENUE DANS ECE-CITY CONSOLE -------- (v.APLHA)\n");
    color(15, 0);
    printf("\nMenu :\n\n");
    printf("1 : Lancer une partie\n");
    printf("2 : Sauvegarde \n");
    printf("3 : Charger une partie\n");
    printf("4 : Quitter\n");
    printf("9 : delet.txt");
    scanf(" %d", &choix);
    switch(choix){
        case 1:{
            jeu = initialisation();
            //time_t timestamp = time( NULL );
            //struct tm * timeInfos = localtime( & timestamp );
            afficher_choix_joueur(jeu,listeMaison,listeChateauEau,listeUsineElectrique);
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
            printf("CHARGEMENT TERMINE !\n");
            chargeBatiment(&listeMaison,&listeChateauEau,&listeUsineElectrique);
            afficher_choix_joueur(jeu,listeMaison,listeChateauEau,listeUsineElectrique);
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

void afficher_choix_joueur(Jeu* jeu,Batiment* listeMaison,Batiment* listeChateauEau,Batiment* listeUsineElectrique){
    int choix = 0, co_x = 0, co_y = 0;
    afficher_la_grille(jeu);
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
    printf("5 : afficher\n");
    printf("6 : Detruire batiment\n");
    scanf(" %d", &choix);
    switch (choix) {
        case 0:{
            sauvBatiment(listeMaison,listeChateauEau,listeUsineElectrique);
            liberationListe(&listeMaison,&listeChateauEau,&listeUsineElectrique);
            afficher_menu_console(jeu);
        }
        case reseau:{
            color(10, 0);
            printf("\nCoordonnees ? (x / y)\n");
            color(15, 0);
            scanf(" %d %d", &co_x, &co_y);
            ajout_Batiment_Grille(jeu, reseau, co_x, co_y);
            printf("Ajout d'une route ...\n");
            sleep(1);
            break;
        }
        case maison:{
            color(10, 0);
            printf("\nCoordonnees ? (x / y)\n");
            color(15, 0);
            scanf(" %d %d", &co_x, &co_y);
            ajout_Batiment_Grille(jeu, maison, co_x, co_y);
            ajouterBatiment(&listeMaison,&listeChateauEau,&listeUsineElectrique,co_x,co_y,choix);
            printf("Ajout d'une maison ...\n");
            sleep(1);
            break;
        }
        case chateau_deau:{
            color(10, 0);
            printf("\nCoordonnees ? (x / y)\n");
            color(15, 0);
            scanf(" %d %d", &co_x, &co_y);
            ajout_Batiment_Grille(jeu, chateau_deau, co_x, co_y);
            ajouterBatiment(&listeMaison,&listeChateauEau,&listeUsineElectrique,co_x,co_y,choix);
            printf("Ajout d'un chateau d'eau ...\n");
            sleep(1);
            break;
        }
        case usine_electrique:{
            color(10, 0);
            printf("\nCoordonnees ? (x / y)\n");
            color(15, 0);
            scanf(" %d %d", &co_x, &co_y);
            ajout_Batiment_Grille(jeu, usine_electrique, co_x, co_y);
            ajouterBatiment(&listeMaison,&listeChateauEau,&listeUsineElectrique,co_x,co_y,choix);
            printf("Ajout d'une usine electrique ...\n");
            sleep(1);
            break;
        }
        case 5:{
            afficherM(listeMaison);
            break;
        }
        case 6:{
            int x = 0,y = 0,type = 0;
            printf("Type?\n");
            scanf("%d",&type);
            printf("Coordonnee:\n");
            scanf("%d  %d",&x,&y);
            switch(type){
                case 2:{
                    detruireBatiment(&listeMaison,&listeChateauEau,&listeUsineElectrique,x,y,maison,jeu);
                    break;
                }
                case 3:{
                    detruireBatiment(&listeMaison,&listeChateauEau,&listeUsineElectrique,x,y,chateau_deau,jeu);
                    break;
                }
                case 4:{
                    detruireBatiment(&listeMaison,&listeChateauEau,&listeUsineElectrique,x,y,usine_electrique,jeu);
                    break;
                }
            }

        }
    }
    afficher_choix_joueur(jeu,listeMaison,listeChateauEau,listeUsineElectrique);
}



void afficher_la_grille(Jeu* jeu){
    for (int y = 0; y < jeu->ordre.y; y++) {
        for (int x = 0; x < jeu->ordre.x; x++) {
            printf("%d ", jeu->terrain[y][x]);
        }
        printf("\n");
    }
}


void ohdi(Jeu* j) {
    int i =0;
    //while (    j->batiments[maison][] != NULL){

    //}
}


//
// Created by chape on 09/11/2022.
//

#include "initialisation.h"

void initialiser_jeu(Jeu* jeu){

    // Initialiser compteurs

    jeu->nb_habitants_tot = 0;
    jeu->argent = 500000;
    jeu->production_eau_restante = 0;
    jeu->production_elec_restante = 0;

    // Initialiser batiments

    jeu->batiments[vide].taille.x = TAILLE_VIDE;
    jeu->batiments[vide].taille.y = TAILLE_VIDE;
    jeu->batiments[vide].nom = "Vide";


    jeu->batiments[route].taille.x = TAILLE_ROUTE;
    jeu->batiments[route].taille.y = TAILLE_ROUTE;
    jeu->batiments[route].nom = "Route";

    jeu->batiments[chateau_deau].taille.x = LONGUEUR_USINE;
    jeu->batiments[chateau_deau].taille.y = LARGEUR_USINE;
    jeu->batiments[chateau_deau].nom = "Chateau d'eau";
    jeu->batiments[chateau_deau].capacite = CAPACITE_USINE;

    jeu->batiments[centrale].taille.x = LONGUEUR_USINE;
    jeu->batiments[centrale].taille.y = LARGEUR_USINE;
    jeu->batiments[centrale].nom = "Centrale";
    jeu->batiments[centrale].capacite = CAPACITE_USINE;

    jeu->batiments[terrain_vague].taille.x = TAILLE_TERRAIN_VAGUE;
    jeu->batiments[terrain_vague].taille.y = TAILLE_TERRAIN_VAGUE;
    jeu->batiments[terrain_vague].nom = "Terrain vague";
    jeu->batiments[terrain_vague].capacite = CAPACITE_MAISON;
    jeu->batiments[terrain_vague].nb_habitants = 0;
}

void ajouter_batiment(Jeu* jeu){

    // Version console

    //Ou construire ?
    int emplacement_x, emplacement_y;
    printf("Ou voulez vous construire le batiment sur les x ?\n");
    scanf(" %d", &emplacement_x);
    printf("Ou voulez vous construire le batiment sur les y ?\n");
    scanf(" %d", &emplacement_y);

    //Construire quoi ?
    char choix_construction;
    printf("Quel batiment voulez vous construire ?\nR : Route\nC : Centrale \nE : Chateau d'eau\nT : Terrain Vague\n");
    scanf(" %c", &choix_construction);
    switch (choix_construction) {
        case 'R' : {
            if (jeu->argent >= PRIX_ROUTE){
                jeu->terrain[emplacement_y][emplacement_x] = route;
                jeu->argent -= PRIX_ROUTE;
            }
            break;
        }
        case 'C' : {
            if (jeu->argent >= PRIX_CENTRALE){
                jeu->terrain[emplacement_y][emplacement_x] = centrale;
                jeu->argent -= PRIX_CENTRALE;
            }
            break;
        }
        case 'E' : {
            if (jeu->argent >= PRIX_CHATEAU_EAU){
                jeu->terrain[emplacement_y][emplacement_x] = chateau_deau;
                jeu->argent -= PRIX_CHATEAU_EAU;
            }
            break;
        }
        case 'T' : {
            if (jeu->argent >= PRIX_TERRAIN_VAGUE){
                jeu->terrain[emplacement_y][emplacement_x] = terrain_vague;
                jeu->argent -= PRIX_TERRAIN_VAGUE;
            }
            break;
        }

    }

}
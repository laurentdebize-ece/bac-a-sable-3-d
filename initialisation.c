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


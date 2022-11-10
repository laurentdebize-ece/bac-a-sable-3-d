#include "Jeu.h"

int difference_entre_2_nombres_VALEURABSOLUE(int a, int b){
    if (a<b){
        return b-a;
    }else return a-b;
}

Jeu* initialisation(){
    Jeu* j;
    remove(NOM_DU_FICHIER);
    j = lire_graphe();

    j->argent = 500000;
    j->production_eau_restante = 0;
    j->production_elec_restante = 0;
    initialisation_CONSTANTE(j);

    return j;
}

void initialisation_CONSTANTE(Jeu* j){
    j->batiments[vide].taille.x = TAILLE_VIDE;
    j->batiments[vide].taille.y = TAILLE_VIDE;
    j->batiments[vide].nom = "Vide";

    j->batiments[reseau].taille.x = TAILLE_ROUTE;
    j->batiments[reseau].taille.y = TAILLE_ROUTE;
    j->batiments[reseau].nom = "Route";

    j->batiments[maison].taille.x = TAILLE_MAISON;
    j->batiments[maison].taille.y = TAILLE_MAISON;
    j->batiments[maison].nom = "Maison";

    j->batiments[chateau_deau].taille.x = LONGUEUR_BATIMENTS;
    j->batiments[chateau_deau].taille.y = LARGEUR_BATIMENTS;
    j->batiments[chateau_deau].nom = "Chateau d'eau";

    j->batiments[usine_electrique].taille.x = LONGUEUR_BATIMENTS;
    j->batiments[usine_electrique].taille.y = LARGEUR_BATIMENTS;
    j->batiments[usine_electrique].nom = "Usine electrique";

}





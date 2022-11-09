#include "Jeu.h"

Jeu* initialisation(){
    Jeu* j;
    remove(NOM_DU_FICHIER);
    j = lire_graphe();
    j->argent = 500000;

    //afficher_fenetre();

    return j;
}




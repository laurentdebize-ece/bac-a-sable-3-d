#include "Jeu.h"

Jeu* initialisation(){
    Jeu* j;
    remove(NOM_DU_FICHIER);
    j = lire_graphe();

    j->argent = 500000;
    j->production_eau_restante = 0;
    j->production_elec_restante = 0;

    return j;
}



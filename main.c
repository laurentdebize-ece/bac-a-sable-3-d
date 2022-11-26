#include "Jeu.h"

int main() {
    /*
    ChangeDirectory(GetApplicationDirectory());
    ChangeDirectory("../FILE");
    Jeu* j = (Jeu *) malloc(sizeof(Jeu));
    j->en_cours = 0;
    lire_graphe(j);
    j->page_actuel = animation_Lancement;
    affichage_Boucle_G(j);
     */
    int nb_case_adj;
    Coordonnee* case_adjacente;
    Coordonnee co_bat;
    co_bat.x = 6;
    co_bat.y = 6;
    nb_case_adj = initialisation_cases_adjacentes_V2(case_adjacente, 3, co_bat);
    return 0;
}


#include "Jeu.h"
#include "affichage.h"
#include "Graphe.h"
#include "initialisation.h"

int main() {
    ChangeDirectory(GetApplicationDirectory());
    ChangeDirectory("../FILE");
    Jeu* j = (Jeu *) malloc(sizeof(Jeu));
    j->en_cours = 0;
    lire_graphe(j);
    j->page_actuel = animation_Lancement;
    affichage_Boucle_G(j);
    int nb_case_adj;
    Vector2* case_adjacente;
    Vector2 co_bat;
    co_bat.x = 6;
    co_bat.y = 6;
    //nb_case_adj = initialisation_cases_adjacentes_V2(case_adjacente, 3, co_bat);

    Jeu* j = lire_graphe("Grille_de_jeu.txt");
    initialiser_jeu(j);
    afficher_la_grille(j);
    ajouter_batiment(j);
    afficher_la_grille(j);
    //afficher_fenetre();

    return 0;
}


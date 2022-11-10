#include "affichage.h"
#include "Graphe.h"
#include "initialisation.h"

int main() {

    Jeu* j = lire_graphe("Grille_de_jeu.txt");
    initialiser_jeu(j);
    afficher_la_grille(j);
    ajouter_batiment(j);
    afficher_la_grille(j);
    //afficher_fenetre();

    return 0;
}


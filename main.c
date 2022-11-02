#include "affichage.h"
#include "Graphe.h"

int main() {
    Jeu* j = lire_graphe("Grille_de_jeu.txt");
    afficher_la_grille(j);
    afficher_fenetre();

    return 0;
}


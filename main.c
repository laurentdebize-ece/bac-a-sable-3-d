#include "affichage.h"
#include "Graphe.h"


int main() {
    ChangeDirectory("../IMAGES");
    Jeu* j = lire_graphe("Grille_de_jeu.txt");
    //initialisation_Images(j);
    //afficher_la_grille(j);
    afficher_fenetre_menu(j);
    //afficherJeu(j);

    return 0;
}


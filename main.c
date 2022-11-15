#include "Jeu.h"


int main() {
    ChangeDirectory(GetApplicationDirectory());
    ChangeDirectory("../IMAGES");
    Jeu* j = lire_graphe("Grille_de_jeu.txt");


    //afficher_la_grille(j);
    afficher_fenetre_menu(j);
    //afficherJeu(j);

    return 0;
}


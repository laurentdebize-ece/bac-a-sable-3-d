#include "Jeu.h"


int main() {
    ChangeDirectory(GetApplicationDirectory());
    ChangeDirectory("../FILE");
    Jeu* j = lire_graphe("Grille_de_jeu.txt");


    //afficher_la_grille(j);
    affichage_Boucle_G(j);
    //afficherJeu(j);

    return 0;
}


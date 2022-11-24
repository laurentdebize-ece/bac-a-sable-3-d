#include "Jeu.h"

int main() {
    Jeu* j;
    afficher_menu_console(j);

    ChangeDirectory(GetApplicationDirectory());
    ChangeDirectory("../FILE");
    Jeu* j = (Jeu *) malloc(sizeof(Jeu));
    j->en_cours = 0;
    j->choix_politique = -1;
    lire_graphe(j);
    j->page_actuel = animation_Lancement;
    affichage_Boucle_G(j);
    return 0;
}


#include "Jeu.h"

void initialise(char* nomFichier,Jeu* j){

    FILE *ifs = fopen(nomFichier, "r");

    if (!ifs) {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    j->argent = 500000;
}


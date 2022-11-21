#include "initialisation.h"


/*Jeu* initialisation_structure(Jeu* grille){
    return grille;
}*/

void initialisation_Grille(){
    color(14, 0);
    printf("Creation d'un graphe ... ...\n");
    sleep(1);
    color(15, 0);
    FILE *ifs = fopen(NOM_DU_FICHIER, "w");
    fprintf(ifs, "%d\n", ORDRE_EN_X);
    fprintf(ifs, "%d\n", ORDRE_EN_Y);
    fprintf(ifs, "%d\n", ARGENT_DE_DEBUT);
    for (int i = 0; i <= ORDRE_EN_Y; i++) {
        for (int j = 0; j <= ORDRE_EN_X; j++) {
            fprintf(ifs, "%d ", vide);
        }
        fprintf(ifs, "\n");
    }
    fclose(ifs);
    //on ne ferme pas ce fichier car nous allons le lire juste apres dans le cas ou nous avons pas de fichier
}

Jeu* initialisation_sans_save(){
    Jeu* j;
    color(8, 0);
    printf("Destruction de votre ancien fichier de sauvegarde (si vous en aviez un)\n");
    color(15, 0);
    remove(NOM_DU_FICHIER);
    j = lire_graphe();

    j->argent = ARGENT_DE_DEBUT;
    j->production_eau_restante = 0;
    j->production_elec_restante = 0;

    return j;
}

/*Jeu* initialisation_CONSTANTE(int choix) {
     Jeu *j;

    switch(choix) {
        case 2: {
            j->batiments[maison]->taille.x = TAILLE_MAISON;
            j->batiments[maison]->taille.y = TAILLE_MAISON;
            j->batiments[maison]->nom = "Maison";
            break;
        }

        case 3: {
            j->batiments[chateau_deau]->taille.x = LONGUEUR_BATIMENTS;
            j->batiments[chateau_deau]->taille.y = LARGEUR_BATIMENTS;
            j->batiments[chateau_deau]->nom = "Chateau d'eau";
            break;
        }

        case 4: {
            j->batiments[usine_electrique]->taille.x = LONGUEUR_BATIMENTS;
            j->batiments[usine_electrique]->taille.y = LARGEUR_BATIMENTS;
            j->batiments[usine_electrique]->nom = "Usine electrique";
            break;
        }
    }
    return j;
}*/

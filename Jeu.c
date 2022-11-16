#include "Jeu.h"

void construction_batiment(Jeu jeu){

}

Coordonnee* initialisation_case_ajacentes(Coordonnee coordonnee_batiment,int longueur, int hauteur ){
    Coordonnee* case_adjacente = malloc(longueur*hauteur*2* sizeof(Coordonnee));
    for (int i = 0; i < longueur*hauteur*2; i++) {
        if (i < hauteur){
            case_adjacente[i].x = coordonnee_batiment.x - 1;
            case_adjacente[i].y = coordonnee_batiment.y + i;
        }
        else if ( i < (hauteur + longueur)){
            case_adjacente[i].x = coordonnee_batiment.x + i - hauteur;
            case_adjacente[i].y = coordonnee_batiment.y + hauteur;
        }
        else if (i < (hauteur*2 + longueur)){
            case_adjacente[i].x = coordonnee_batiment.x + longueur;
            case_adjacente[i].y = coordonnee_batiment.y - i + hauteur*2 + longueur;
        }
        else{
            case_adjacente[i].x = coordonnee_batiment.x - i + hauteur*2 + longueur*2;
            case_adjacente[i].y = coordonnee_batiment.y - 1;
        }
    }
    return case_adjacente;
}



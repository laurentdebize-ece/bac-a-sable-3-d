#ifndef BAC_A_SABLE_2_INITIALISATION_H
//
// Created by chape on 09/11/2022.
//

#define BAC_A_SABLE_2_INITIALISATION_H

#include "Jeu.h"


void initialisation_Images(Jeu* jeu);
void initialisation_Sons(Jeu* jeu);
void ini_fond_jeu(Jeu* jeu);
void ini_bouton(Jeu* jeu);
void initialiser_jeu(Jeu* jeu);
void unload_all(Jeu* jeu);
//Jeu* initialisation_structure(Jeu* jeu);
void initialisation_Grille();
Jeu* initialisation_sans_save();
//Batiment* initialisation_CONSTANTE(int choix);
#include "Macros.h"

void ajouter_batiment(Jeu* jeu);
void initialiser_jeu(Jeu* jeu);

#endif //BAC_A_SABLE_2_INITIALISATION_H

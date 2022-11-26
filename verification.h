#ifndef BAC_A_SABLE_2_VERIFICATION_H
#define BAC_A_SABLE_2_VERIFICATION_H
//
#include "Jeu.h"

bool verification_batiment_peut_se_placer(Jeu* jeu, int nomDuBatiment, Vector2 pos_ini_batiment);
void ajout_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute);
void poser_batiment(Jeu* jeu);
void maj_batiment_timer(Jeu* jeu);


#endif //BAC_A_SABLE_2_VERIFICATION_H

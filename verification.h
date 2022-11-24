#ifndef BAC_A_SABLE_2_VERIFICATION_H
#define BAC_A_SABLE_2_VERIFICATION_H

#include "Jeu.h"

void verification_batiment_peut_se_placer(Jeu* jeu, int nomDuBatiment, Vector2 position1, Vector2 co_route);
void ajout_Batiment_Grille(Jeu* jeu, int nomDuBatiment, int co_x, int co_y, int co_xroute, int co_yroute);


#endif //BAC_A_SABLE_2_VERIFICATION_H

#ifndef BAC_A_SABLE_2_BFS_H
#define BAC_A_SABLE_2_BFS_H

#include "Macros.h"
#include "Graphe.h"

void BFS_connexite(int** matrice_connexite_route, Coordonnee tuile, int num_connexite);
int** init_conexite_route(Jeu* jeu);

#endif //BAC_A_SABLE_2_BFS_H

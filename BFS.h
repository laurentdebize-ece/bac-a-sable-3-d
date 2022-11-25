#ifndef BAC_A_SABLE_2_BFS_H
#define BAC_A_SABLE_2_BFS_H

#include "Macros.h"
#include "Graphe.h"

void BFS_connexite(Jeu* jeu, Coordonnee tuile);
int** init_conexite_route(Jeu* jeu);
void connexite_route_ajout_batiment(Jeu* jeu, Batiment* nouveau);
void connexite_route_ajout_route(Jeu* jeu, Coordonnee debut, Coordonnee fin);
#endif //BAC_A_SABLE_2_BFS_H

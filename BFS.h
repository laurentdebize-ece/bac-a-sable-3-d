#ifndef BAC_A_SABLE_2_BFS_H
#define BAC_A_SABLE_2_BFS_H
//
#include "Macros.h"
#include "Graphe.h"
#include "verification.h"

void BFS_connexite(Jeu* jeu, Vector2 tuile, int num_connexite_teste);
int** init_conexite_route(Jeu* jeu);
void connexite_route_ajout_batiment(Jeu* jeu, Batiment* nouveau);
void connexite_route_ajout_route(Jeu* jeu, Vector2 route);
#endif //BAC_A_SABLE_2_BFS_H

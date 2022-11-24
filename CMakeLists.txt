cmake_minimum_required(VERSION 3.23)
project(bac_a_sable_2 C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(raylib)

add_executable(bac_a_sable_2 main.c Jeu.c Jeu.h affichage.c affichage.h Graphe.c Graphe.h COULEURS.c COULEURS.h Macros.h initialisation.c initialisation.h matrice_adjacence.c matrice_adjacence.h BFS.c BFS.h)
#add_executable(bac_a_sable_2 main.c)

target_link_libraries(bac_a_sable_2 raylib)


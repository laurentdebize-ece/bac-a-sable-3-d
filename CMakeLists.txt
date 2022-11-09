cmake_minimum_required(VERSION 3.23)
project(bac_a_sable_2 C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(raylib)


add_executable(bac_a_sable_2 main.c Jeu.c Jeu.h affichage.c affichage.h Graphe.c Graphe.h Macros.h)

target_link_libraries(bac_a_sable_2 raylib)
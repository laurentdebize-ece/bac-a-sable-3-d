#ifndef TEMPLATE_RAYLIB_JEU_H
#define TEMPLATE_RAYLIB_JEU_H
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

//TODO: LISTE CHAINE POUR BATIMENTS

enum {communisme, capitalisme};
enum {animation_Lancement, menu_principale, selection_choix_jeu,en_jeu, regles, credis, nb_pages};
enum {img_menu, img_boutonoff, img_boutonJouer, img_boutonSauvegarder, img_boutonRegles, img_boutonCredits, img_bouton_suppSave, img_bouton_Communisme, img_bouton_Capitalisme, img_fond_ChoixJeu, img_fondJeu1, img_fondJeu2, img_fondJeu3, img_fondJeu4, img_logosJeu, img_boutonRetourMenu, img_route, img_maison, img_usine, img_chateauDO, img_niveau_0, img_niveau_1, img_niveau_2, img_demolition, img_logo_argent, img_logo_eau, img_logo_elec, img_logo_habitant, img_logo_warning, img_fond_panneau_affichage, img_fond_credits, nb_img};
enum {mode_neutre, mode_reseau ,mode_maison, mode_usine, mode_chateauDO, mode_demolition, nb_modes};
enum {vide, reseau, maison, chateau_deau, usine_electrique, demolition, nb_type_batiments};
enum {son_Bouton, son_menu, nb_sons};


typedef struct {
    int distance;
    int numero_batiment;
    int numero_maison;
}Stockage_batiment;
#include "Graphe.h"
#include "Macros.h"
enum {vide, route, terrain_vague, chateau_deau, centrale, nbBatiments};

typedef struct Coordonnee {
    int x;
    int y;
}Coordonnee;

typedef struct Batiment{
    Coordonnee* cases_adjacentes;
    Coordonnee* cases;
    char* nom;
    int capacite;
    int nb_habitants;
}Batiment;

typedef struct Jeu{
    int** terrain;
    int ordre_en_x;
    int ordre_en_y;
    int nb_habitants_tot;
    int argent;
    int production_eau_restante;
    int production_elec_restante;
    Batiment* batiments;
}Jeu;


#endif //TEMPLATE_RAYLIB_JEU_H

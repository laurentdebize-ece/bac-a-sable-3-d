#ifndef TEMPLATE_RAYLIB_JEU_H
#define TEMPLATE_RAYLIB_JEU_H
#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
enum {animation_Lancement, menu_principale, en_jeu, regles, credis, nb_pages};
enum {img_menu, img_boutonoff, img_boutonJouer, img_boutonSauvegarder, img_boutonRegles, img_boutonCredits, img_suppSave, img_fondJeu1, img_fondJeu2, img_fondJeu3, img_fondJeu4, img_logosJeu, img_boutonRetourMenu, img_route, img_maison, img_usine, img_chateauDO, nb_img};
enum {mode_neutre, mode_reseau ,mode_maison, mode_usine, mode_chateauDO, mode_demolition, nb_modes};
enum {vide, reseau, maison, chateau_deau, usine_electrique, demolition, nb_batiments};
enum {son_Bouton, son_menu, nb_sons};

typedef struct Coordonnee {
    int x;
    int y;
}Coordonnee;
typedef struct S_Image{
    bool charge;
    Texture2D texture2D;
    Image image2D;
    Rectangle source_Rec;
    Rectangle pos_Rec;
    int x;
    int y;
    float frame_hauteur;
    float frame_longueur;
    float alpha;
    bool action_sur_click;
}S_Image;

typedef struct Batiment{
    Coordonnee taille;
    Coordonnee cases;
    char* nom;
    int capacite;
    int nb_habitants;
    int experience;
    struct Batiment* next;
}Batiment;

typedef struct Jeu{
    bool Communisme;
    bool en_cours;
    bool fichier;
    bool quitter;
    int mode_Jeu;
    int page_actuel;
    int** terrain;
    Coordonnee ordre;
    Coordonnee selection;
    int nb_habitants_tot;
    int argent;
    int production_eau_restante;
    int production_elec_restante;
    int timer_jeu;
    Batiment batiments[nb_batiments];
    S_Image tabImages[nb_pages][nb_img];
    Sound tabSon[nb_sons];
}Jeu;

// TODO: NE PAS CHANGER LORDRE DES INCLUDES IMPORTANT !!!

#include "Macros.h"
#include "initialisation.h"
#include "affichage.h"
#include "raylib.h"
#include "Graphe.h"
#include "reasings.h"


int difference_entre_2_nombres_VALEURABSOLUE(int a, int b);
Jeu* initialisation();
void initialisation_CONSTANTE(Jeu* j);


#endif //TEMPLATE_RAYLIB_JEU_H

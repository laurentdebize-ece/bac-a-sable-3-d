#ifndef TEMPLATE_RAYLIB_MACROS_H
#define TEMPLATE_RAYLIB_MACROS_H

#define VOLUME_GLOBAL 0.3f

//Affichage

#define TRUE 1
#define FALSE 0
#define LARGEUR_FENETRE 920
#define LONGUEUR_FENETRE 780
#define LONGUEUR 45
#define LARGEUR 35

#define TEMPS_DEFILEMENT_FOND 7
#define TEMPS_FONDU_FOND 2

#define RESOLUTION_X 1920
#define RESOLUTION_Y 1080
#define LARGEUR_FENETRE 1920
#define LONGUEUR_FENETRE 1080

//IMAGES
#define NB_FRAMES_BOUTON  3       // Nombre de frame pour le Bouton
#define NB_FRAMES_MAISON 6
#define MOUSE_SCALE_MARK_SIZE   12

#define MAP_TILE_SIZE    32         // Tiles size 32x32 pixels
#define PLAYER_SIZE      16         // Taille du carre rouge
#define PLAYER_TILE_VISIBILITY  2   // Player can see 2 tiles around its position


// dimensions batiments
#define TAILLE_TERRAIN_VAGUE 3
#define TAILLE_ROUTE 1
#define TAILLE_VIDE 1
#define LONGUEUR_USINE 6
#define LARGEUR_USINE 4
#define CASE_ADJACENTE_MAISON 12
#define CASE_ADJACENTE_USINE 20
#define LONGUEUR_BATIMENTS 6
#define LARGEUR_BATIMENTS 4

// capacité
#define CAPACITE_USINE 5000
#define CAPACITE_CHATEAU_EAU 5000

//nbBatiment en fonction du noiveau de la maison
#define HABITANT_NIVEAU_MAISON1 10
#define HABITANT_NIVEAU_MAISON2 50
#define HABITANT_NIVEAU_MAISON3 100
#define HABITANT_NIVEAU_MAISON4 1000

//Cout
#define COUT_MAISON 1000
#define COUT_CHATEAU_EAU 100000
#define COUT_USINE_ELECTRIQUE 100000
#define COUT_ROUTE 10

#define IMPOTS_PAR_HABITANT 10


// prix
#define PRIX_TERRAIN_VAGUE 1000
#define PRIX_CENTRALE 100000
#define PRIX_CHATEAU_EAU 100000
#define PRIX_ROUTE 10

#endif //TEMPLATE_RAYLIB_MACROS_H

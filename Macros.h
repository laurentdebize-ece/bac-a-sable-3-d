#ifndef TEMPLATE_RAYLIB_MACROS_H
#define TEMPLATE_RAYLIB_MACROS_H

#define VOLUME_GLOBAL 0.3f

//Affichage

#define TRUE 1
#define FALSE 0

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

#define TAILLE_CASE_GRILLE    25      // taille des cases
#define PLAYER_SIZE      16         // Taille du carre rouge
#define PLAYER_TILE_VISIBILITY  2   // Player can see 2 tiles around its position


//PARAMETRAGE DU JEU

#define ORDRE_EN_X 46
#define ORDRE_EN_Y 36

#define NOM_DU_FICHIER "Grille_de_jeu.txt"

#define ARGENT_DE_DEBUT 500000



// dimensions batiments
#define TAILLE_MAISON 3
#define TAILLE_ROUTE 1
#define TAILLE_VIDE 1
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

#endif //TEMPLATE_RAYLIB_MACROS_H

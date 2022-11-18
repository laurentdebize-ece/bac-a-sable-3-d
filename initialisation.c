#include "initialisation.h"


void initialisation_Images(Jeu* jeu){
    // TODO: NE PAS OUBLIER DE Unload des imgs apres les avoir mises en texture /!\
    //  AVEC CA :  UnloadImage(jeu->tabImages[NOMDELIMAGE].image2D);

    //exemple d'init img et redimension
    /*jeu->tabImages[boutonoff].image2D = LoadImage("off-button.png");
    int x = jeu->tabImages[boutonoff].image2D.width;
    int y = jeu->tabImages[boutonoff].image2D.height;
    ImageCrop(&jeu->tabImages[boutonoff].image2D, (Rectangle){0, 0, x / 1.5, y / 1.5 });
    ImageResize(&jeu->tabImages[boutonoff].image2D, jeu->tabImages[boutonoff].x = x / 11, jeu->tabImages[boutonoff].y = y / 11);
    jeu->tabImages[boutonoff].texture2D = LoadTextureFromImage(jeu->tabImages[boutonoff].image2D);*/

    //pour init une img en boutton
    ini_bouton(jeu);
    jeu->tabImages[menu_principale][img_menu].texture2D = LoadTexture("Menu.png");
    jeu->tabImages[menu_principale][img_menu].charge = 1;


}

void initialisation_Sons(Jeu* jeu){
    jeu->tabSon[son_Bouton] = LoadSound("bouton_son.mp3");
    SetSoundVolume(jeu->tabSon[img_boutonoff], 0.4);

    jeu->tabSon[son_menu] = LoadSound("musique_ambiance_menu.mp3");
    SetSoundVolume(jeu->tabSon[son_menu], 0.6);
}


void ini_bouton(Jeu* jeu){
    jeu->tabImages[menu_principale][img_boutonoff].charge = 1;

    //Bouton QUITTER
    Texture2D bouton_texture =LoadTexture("button.png");
    float frame_hauteur= (float)bouton_texture.height / NB_FRAMES_BOUTON;
    jeu->tabImages[menu_principale][img_boutonoff].texture2D = bouton_texture; // Load button texture
    jeu->tabImages[menu_principale][img_boutonoff].frame_hauteur = frame_hauteur;
    Rectangle sourceRec = {0, 0, (float)jeu->tabImages[menu_principale][img_boutonoff].texture2D.width, jeu->tabImages[menu_principale][img_boutonoff].frame_hauteur };
    jeu->tabImages[menu_principale][img_boutonoff].source_Rec = sourceRec;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos1 = {RESOLUTION_X / 2.0f - bouton_texture.width / 2.0f, RESOLUTION_Y / 2.0f - bouton_texture.height / NB_FRAMES_BOUTON + 4*(frame_hauteur + 5), (float)bouton_texture.width, frame_hauteur };
    jeu->tabImages[menu_principale][img_boutonoff].pos_Rec = pos1;

    //Bouton JOUER
    jeu->tabImages[menu_principale][img_boutonJouer].texture2D = bouton_texture; // Load button texture
    jeu->tabImages[menu_principale][img_boutonJouer].frame_hauteur = frame_hauteur;
    jeu->tabImages[menu_principale][img_boutonJouer].source_Rec = sourceRec;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos2 = {RESOLUTION_X / 2.0f - bouton_texture.width / 2.0f, RESOLUTION_Y / 2.0f - bouton_texture.height / NB_FRAMES_BOUTON - (frame_hauteur + 5), (float)bouton_texture.width, frame_hauteur };
    jeu->tabImages[menu_principale][img_boutonJouer].pos_Rec = pos2;

    //Bouton SAUVEGARDER
    jeu->tabImages[menu_principale][img_boutonSauvegarder].texture2D = bouton_texture; // Load button texture
    jeu->tabImages[menu_principale][img_boutonSauvegarder].frame_hauteur = frame_hauteur;
    jeu->tabImages[menu_principale][img_boutonSauvegarder].source_Rec = sourceRec;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos5 = {RESOLUTION_X / 2.0f - bouton_texture.width / 2.0f, RESOLUTION_Y / 2.0f - bouton_texture.height / NB_FRAMES_BOUTON , (float)bouton_texture.width, frame_hauteur };
    jeu->tabImages[menu_principale][img_boutonSauvegarder].pos_Rec = pos5;

    //Bouton Regles
    jeu->tabImages[menu_principale][img_boutonRegles].texture2D = bouton_texture; // Load button texture
    jeu->tabImages[menu_principale][img_boutonRegles].frame_hauteur = frame_hauteur;
    jeu->tabImages[menu_principale][img_boutonRegles].source_Rec = sourceRec;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos3 = {RESOLUTION_X / 2.0f - bouton_texture.width / 2.0f, RESOLUTION_Y / 2.0f - bouton_texture.height / NB_FRAMES_BOUTON + (frame_hauteur + 5), (float)bouton_texture.width, frame_hauteur };
    jeu->tabImages[menu_principale][img_boutonRegles].pos_Rec = pos3;

    //Bouton Credits
    jeu->tabImages[menu_principale][img_boutonCredits].texture2D = bouton_texture; // Load button texture
    jeu->tabImages[menu_principale][img_boutonCredits].frame_hauteur = frame_hauteur;
    jeu->tabImages[menu_principale][img_boutonCredits].source_Rec = sourceRec;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos4 = {RESOLUTION_X / 2.0f - bouton_texture.width / 2.0f, RESOLUTION_Y / 2.0f - bouton_texture.height / NB_FRAMES_BOUTON + 2*(frame_hauteur + 5), (float)bouton_texture.width, frame_hauteur };
    jeu->tabImages[menu_principale][img_boutonCredits].pos_Rec = pos4;

    //Bouton RESET
    jeu->tabImages[menu_principale][img_suppSave].texture2D = bouton_texture; // Load button texture
    jeu->tabImages[menu_principale][img_suppSave].frame_hauteur = frame_hauteur;
    jeu->tabImages[menu_principale][img_suppSave].source_Rec = sourceRec;
    // Definie l emplacement du boutton sur ecran (la ou l'on veut l afficher)
    Rectangle pos6 = {RESOLUTION_X / 2.0f - bouton_texture.width / 2.0f, RESOLUTION_Y / 2.0f - bouton_texture.height / NB_FRAMES_BOUTON + 3*(frame_hauteur + 5), (float)bouton_texture.width, frame_hauteur };
    jeu->tabImages[menu_principale][img_suppSave].pos_Rec = pos6;
}
void unload_all(Jeu* jeu){
    for (int i = 0; i < nbPages; i++) {
        for (int j = 0; j < nbImages; j++) {
            if(jeu->tabImages[i][j].charge==1){
                UnloadTexture(jeu->tabImages[i][j].texture2D);
            }
        }

    }
    for (int i = 0; i < nbSons; i++) {
        UnloadSound(jeu->tabSon[i]);
    }
}


void initialiser_jeu(Jeu* jeu){

    jeu->batiments[vide].taille.x = TAILLE_VIDE;
    jeu->batiments[vide].taille.y = TAILLE_VIDE;
    jeu->batiments[vide].nom = "Vide";

    jeu->batiments[reseau].taille.x = TAILLE_ROUTE;
    jeu->batiments[reseau].taille.y = TAILLE_ROUTE;
    jeu->batiments[reseau].nom = "Route";

    jeu->batiments[maison].taille.x = TAILLE_MAISON;
    jeu->batiments[maison].taille.y = TAILLE_MAISON;
    jeu->batiments[maison].nom = "Maison";

    jeu->batiments[chateau_deau].taille.x = LONGUEUR_BATIMENTS;
    jeu->batiments[chateau_deau].taille.y = LARGEUR_BATIMENTS;
    jeu->batiments[chateau_deau].nom = "Chateau d'eau";

    jeu->batiments[usine_electrique].taille.x = LONGUEUR_BATIMENTS;
    jeu->batiments[usine_electrique].taille.y = LARGEUR_BATIMENTS;
    jeu->batiments[usine_electrique].nom = "Usine electrique";

    // Initialiser compteurs

    jeu->nb_habitants_tot = 0;
    jeu->argent = ARGENT_DE_DEBUT;
    jeu->production_eau_restante = 0;
    jeu->production_elec_restante = 0;

    // Initialiser batiments

    /*jeu->batiments[vide].taille.x = TAILLE_VIDE;
    jeu->batiments[vide].taille.y = TAILLE_VIDE;
    jeu->batiments[vide].nom = "Vide";


    jeu->batiments[route].taille.x = TAILLE_ROUTE;
    jeu->batiments[route].taille.y = TAILLE_ROUTE;
    jeu->batiments[route].nom = "Route";

    jeu->batiments[chateau_deau].taille.x = LONGUEUR_USINE;
    jeu->batiments[chateau_deau].taille.y = LARGEUR_USINE;
    jeu->batiments[chateau_deau].nom = "Chateau d'eau";
    jeu->batiments[chateau_deau].capacite = CAPACITE_USINE;

    jeu->batiments[centrale].taille.x = LONGUEUR_USINE;
    jeu->batiments[centrale].taille.y = LARGEUR_USINE;
    jeu->batiments[centrale].nom = "Centrale";
    jeu->batiments[centrale].capacite = CAPACITE_USINE;

    jeu->batiments[terrain_vague].taille.x = TAILLE_TERRAIN_VAGUE;
    jeu->batiments[terrain_vague].taille.y = TAILLE_TERRAIN_VAGUE;
    jeu->batiments[terrain_vague].nom = "Terrain vague";
    jeu->batiments[terrain_vague].capacite = CAPACITE_MAISON;
    jeu->batiments[terrain_vague].nb_habitants = 0;*/
}


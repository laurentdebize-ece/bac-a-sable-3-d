#include "verification.h"

// 1 quand pas d obstacle
// 0 quand obstacle
//
bool verification_colision_batiment(Jeu* jeu, int nomDuBatiment){
    int co_x = (int)jeu->selection.x-1;
    int co_y = (int)jeu->selection.y-1;
    if (nomDuBatiment == reseau){
        if ((co_x + 1)<0 || (co_y + 1)<0) return 0;
        else if (jeu->terrain[co_y + 1][co_x + 1] != 0) return 0;
    }
    else if (nomDuBatiment == maison){
        for (int i = 0; i < TAILLE_MAISON ; i++) {
            for (int j = 0; j < TAILLE_MAISON; j++) {
                if (jeu->terrain[co_y + i][co_x + j] != 0) return 0;
            }
        }
    }
    else if (nomDuBatiment == usine_electrique || nomDuBatiment == chateau_deau){
        for (int i = 0; i < LARGEUR_BATIMENTS ; i++) {
            for (int j = 0; j < LONGUEUR_BATIMENTS; j++) {
                if (jeu->terrain[co_y + i][co_x + j] != 0){
                    return 0;
                }
            }
        }

    }
    return 1;
}

bool verification_batiment_peut_se_placer(Jeu* jeu, int nomDuBatiment, Vector2 pos_ini_batiment){
    int longueur;
    int largeur;
    Vector2 pos_souris = GetMousePosition();
    if (pos_souris.x <0 || pos_souris.y <0 || pos_souris.x > TAILLE_CASE_GRILLE*jeu->ordre.x || pos_souris.y> TAILLE_CASE_GRILLE*jeu->ordre.y) {
        return 0;
    } else{
        switch (nomDuBatiment) {
            case reseau:
                if (pos_ini_batiment.x >= 0 && pos_ini_batiment.y >= 0 && pos_ini_batiment.x <= jeu->ordre.x && pos_ini_batiment.y <= jeu->ordre.y){
                    if (verification_colision_batiment(jeu, nomDuBatiment) == 1) return 1;
                }
                return 0;
            case maison:
                longueur = TAILLE_MAISON;
                largeur = TAILLE_MAISON; //car c'est un carre pour la maison
                if (pos_ini_batiment.x >= 0 && pos_ini_batiment.y >= 0 && pos_ini_batiment.x + longueur <= jeu->ordre.x && pos_ini_batiment.y + largeur <= jeu->ordre.y){
                    if (verification_colision_batiment(jeu, nomDuBatiment) == 1) return 1;
                }
                return 0;
            case usine_electrique:
            case chateau_deau:
                longueur = LONGUEUR_BATIMENTS;
                largeur = LARGEUR_BATIMENTS;
                if (pos_ini_batiment.x >= 0 && pos_ini_batiment.y >= 0 && pos_ini_batiment.x + longueur <= jeu->ordre.x && pos_ini_batiment.y + largeur <= jeu->ordre.y) {
                    if (verification_colision_batiment(jeu, nomDuBatiment) == 1) return 1;
                }
                return 0;
            default:
                return 0;
        }
    }
}

void ajout_batiment_terrain(Jeu* jeu, int nomDuBatiment, Vector2 pos1) {
    if (nomDuBatiment != reseau) {
        for (int y = 0; y < (int)jeu->batiments[nomDuBatiment]->taille.y; y++) {
            for (int x = 0; x < (int)jeu->batiments[nomDuBatiment]->taille.x; x++) {
                jeu->terrain[(int) pos1.y + y][(int) pos1.x + x] = nomDuBatiment;
            }
        }
        printf("%s construite\n", jeu->batiments[nomDuBatiment]->nom);
    } else {
        jeu->terrain[(int) pos1.y][(int) pos1.x] = reseau;
    }
}

void poser_batiment(Jeu* jeu){
    Vector2 posBatiment = jeu->selection;
    posBatiment.x -= 1;
    posBatiment.y -= 1;
    if (jeu->page_actuel == en_jeu) {
        switch (jeu->mode_de_selection) {
            case mode_neutre:
                break;
            case mode_reseau:
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    jeu->onClickSouris = true;
                }
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    jeu->onClickSouris = false;
                }
                if (jeu->onClickSouris == true){
                    if (verification_batiment_peut_se_placer(jeu, reseau, jeu->selection) == 1) {
                        ajout_batiment_terrain(jeu, reseau, jeu->selection);
                    } else jeu->timer_affichage = 0;
                }
                break;
            case mode_maison:
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    if (verification_batiment_peut_se_placer(jeu, maison, posBatiment) == 1) {
                        //ajout batiment
                        ajouterBatiment_ListeChainee(jeu, (int)posBatiment.x, (int)posBatiment.y, maison);
                        ajout_batiment_terrain(jeu, maison, posBatiment);
                    } else {
                        jeu->timer_affichage = 0;
                    }

                }
                break;
            case mode_usine:
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    if (verification_batiment_peut_se_placer(jeu, usine_electrique, posBatiment) == 1) {
                        //ajout batiment
                        ajouterBatiment_ListeChainee(jeu, (int)posBatiment.x, (int)posBatiment.y, usine_electrique);
                        ajout_batiment_terrain(jeu, usine_electrique, posBatiment);

                    } else {
                        jeu->timer_affichage = 0;
                    }

                }
                break;
            case mode_chateauDO:
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    if (verification_batiment_peut_se_placer(jeu, chateau_deau, posBatiment) == 1) {
                        //ajout batiment
                        ajouterBatiment_ListeChainee(jeu, (int)posBatiment.x, (int)posBatiment.y, chateau_deau);
                        ajout_batiment_terrain(jeu, chateau_deau, posBatiment);
                    } else {
                        jeu->timer_affichage = 0;
                    }
                }
                break;
            case demolition:
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {

                }
                break;
            default:
                break;
        }
    }
}

void maj_batiment_timer(Jeu* jeu){
    if(jeu->batiments[maison] != NULL) {
        Batiment *list_maison = jeu->batiments[maison];
        for (int m = 0; m < jeu->batiments[maison]->nb_batiment; m++) {
            list_maison->timer++;
            list_maison = list_maison->next;
        }
    }
    if(jeu->batiments[chateau_deau] != NULL) {
        Batiment *list_chateauDO = jeu->batiments[chateau_deau];
        for (int c = 0; c < jeu->batiments[chateau_deau]->nb_batiment; c++) {
            list_chateauDO->timer++;
            list_chateauDO = list_chateauDO->next;
        }
    }
    if(jeu->batiments[usine_electrique] != NULL){
        Batiment* list_usine = jeu->batiments[usine_electrique];
        for (int u = 0; u < jeu->batiments[usine_electrique]->nb_batiment; u++) {
            list_usine->timer++;
            list_usine = list_usine->next;
        }
    }
}
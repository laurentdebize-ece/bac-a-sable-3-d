#include "affichage.h"

void affichage_Boucle_G(Jeu* jeu){
    InitWindow(RESOLUTION_X, RESOLUTION_Y, "ECE-CITY BETA/ALPHA de L'OMEGA");
    InitAudioDevice();      // Initialise le haut-parleur
    jeu->quitter = 0;
    jeu->mode_Jeu = mode_neutre;
    initialisation_Images(jeu);
    initialisation_Sons(jeu);
    ini_fond_jeu(jeu);
    ToggleFullscreen();

    int ballPositionX = -100;
    int ballRadius = 20;
    float ballAlpha = 0.0f;
    int state = 0;
    int timer = 0;
    jeu->timer_jeu =0;
    float fade = 1;
    float fadeson = 0;

    SetWindowPosition(0, 25);
    SetTargetFPS(60);
    while (!jeu->quitter) {
        jeu->quitter = WindowShouldClose();
        if(IsKeyPressed(KEY_SPACE))jeu->page_actuel = en_jeu;
        Vector2 pos_Souris = GetMousePosition();
        switch (jeu->page_actuel) {
            case animation_Lancement:
                afficher_animation(jeu, &ballPositionX, &ballRadius, &ballAlpha, &state, &timer);
                break;
            case menu_principale:
                afficher_fenetre_menu(jeu, pos_Souris, &timer,&fade, &fadeson);
                break;
            case en_jeu:
                afficherJeu(jeu, pos_Souris, &timer);
                break;
        }
        timer++;
        jeu->timer_jeu++;
    }
    unload_all(jeu);
    CloseAudioDevice();
    CloseWindow();
}

void afficher_fenetre_menu(Jeu* jeu, Vector2 pos_Souris, int* timer, float* rectAplha, float* sonAlpha){
    BeginDrawing();
    if(IsSoundPlaying(jeu->tabSon[son_menu])==0){
        PlaySound(jeu->tabSon[son_menu]);
    }
    ClearBackground(BLACK);
    DrawTexture(jeu->tabImages[menu_principale][img_menu].texture2D, 0, 0, WHITE);
    affi_bouton(jeu, jeu->page_actuel, img_boutonCredits, pos_Souris, "CREDITS", timer);
    affi_bouton(jeu, jeu->page_actuel, img_boutonRegles, pos_Souris, "RULES", timer);
    affi_bouton(jeu, jeu->page_actuel, img_boutonJouer, pos_Souris, "START", timer);
    affi_bouton(jeu, jeu->page_actuel, img_boutonSauvegarder, pos_Souris, "SAVE", timer);
    affi_bouton(jeu, jeu->page_actuel, img_boutonoff, pos_Souris, "EXIT", timer);
    affi_bouton(jeu, jeu->page_actuel, img_suppSave, pos_Souris, "RESET", timer);
    if (*timer <=300){
        *rectAplha -= 0.01f;
        *sonAlpha += 0.035f;
        if(*sonAlpha < 0.6f){
            SetSoundVolume(jeu->tabSon[son_menu], *sonAlpha);
        }
        DrawRectangle(0, 0, RESOLUTION_X, RESOLUTION_Y, Fade(BLACK, *rectAplha));
    }

    EndDrawing();
}

void afficher_animation(Jeu* jeu, int* ballPositionX, int* ballRadius, float* ballAlpha, int* state, int* framesCounter){
    if (*state == 0){
        *ballPositionX = (int)EaseElasticOut((float)*framesCounter, -100, RESOLUTION_X / 2.0f + 100, 120);

        if (*framesCounter >= 120){
            *framesCounter = 0;
            *state = 1;
        }
    }
    else if (*state == 1){
        *ballRadius = (int)EaseElasticIn((float)*framesCounter, 20, 5000, 200);

        if (*framesCounter >= 200)
        {
            *framesCounter = 0;
            *state = 2;
        }
    }
    else if (*state == 2){
        *ballAlpha = EaseCubicOut((float)*framesCounter, 0.0f, 1.0f, 200);

        if (*framesCounter >= 150)
        {
            *framesCounter = 0;
            *state = 3;
        }
    }
    BeginDrawing();

    ClearBackground(RAYWHITE);
    if (*state >= 2) {
        DrawRectangle(0, 0, RESOLUTION_X, RESOLUTION_Y, BLACK);
        DrawText("ECE - CITY", RESOLUTION_X/2 - 95, RESOLUTION_Y/2, 30, BLUE);
    }
    DrawCircle(*ballPositionX, RESOLUTION_Y/2, (float)*ballRadius, Fade(BLUE, 1.0f - *ballAlpha));

    if (*state == 3) {
        *framesCounter = 0;
        jeu->page_actuel = menu_principale;
    }
    EndDrawing();
}

void affi_bouton(Jeu* jeu, int page, int image, Vector2 pos_souris, char* nom, int* timer){
    int btnState;
    bool btnAction;
    btnAction = false;
    Rectangle hit_box_bouton = {jeu->tabImages[page][image].pos_Rec.x, jeu->tabImages[page][image].pos_Rec.y, jeu->tabImages[page][image].pos_Rec.width, jeu->tabImages[page][image].pos_Rec.height-18};
    if (CheckCollisionPointRec(pos_souris, hit_box_bouton))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
        else btnState = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
    }
    else btnState = 0;
    if (btnAction)
    {
        PlaySound(jeu->tabSon[son_Bouton]); // +ce qu'on souhaite faire en appuyant sur l'image
        switch (image) {
            case img_boutonoff:
                jeu->quitter = 1;
                break;
            case img_boutonJouer:
                ini_fond_jeu(jeu);
                *timer = 0;
                jeu->page_actuel = en_jeu;
                break;
            case img_suppSave:
                printf("Destruction de votre ancien fichier de sauvegarde (si vous en aviez un)\n");
                remove(NOM_DU_FICHIER);
                lire_graphe(jeu);
                break;
            case img_boutonRetourMenu:
                //faire la save ici
                *timer = 0;
                jeu->page_actuel = menu_principale;
                break;
            default:
                break;
        }
    }
    jeu->tabImages[page][image].source_Rec.y = btnState * jeu->tabImages[page][image].frame_hauteur;
    DrawTextureRec(jeu->tabImages[page][image].texture2D, jeu->tabImages[page][image].source_Rec, (Vector2){jeu->tabImages[page][image].pos_Rec.x, jeu->tabImages[page][image].pos_Rec.y }, WHITE);
    DrawText(nom, jeu->tabImages[page][image].pos_Rec.x + 40, jeu->tabImages[page][image].pos_Rec.y + 40, 30, BLACK);
}

void afficher_jeu_logo_interactionAvecClick(Jeu* jeu, Vector2 pos_souris){
    float alphalogojeu1 = 0.5f;
    float alphalogojeu2 = 0.85f;
    Rectangle logo_reseau = {0, TAILLE_CASE_GRILLE*(jeu->ordre.y+1), jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur, jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur};
    Rectangle logo_maison = {90, TAILLE_CASE_GRILLE*(jeu->ordre.y+1), jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur, jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur};
    Rectangle logo_usine = {180, TAILLE_CASE_GRILLE*(jeu->ordre.y+1), jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur, jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur};
    Rectangle logo_chateauDO = {270, TAILLE_CASE_GRILLE*(jeu->ordre.y+1), jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur, jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur};
    Rectangle logo_demolition = {360, TAILLE_CASE_GRILLE*(jeu->ordre.y+1), jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur, jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur};
    int selection = -1;
    DrawRectangle(0, TAILLE_CASE_GRILLE*(jeu->ordre.y+1), jeu->tabImages[en_jeu][img_logosJeu].texture2D.width, jeu->tabImages[en_jeu][img_logosJeu].frame_hauteur,Fade(BLUE, 0.7f));
    DrawTexture(jeu->tabImages[en_jeu][img_logosJeu].texture2D, 0, TAILLE_CASE_GRILLE*(jeu->ordre.y+1), WHITE);
    if (CheckCollisionPointRec(pos_souris, logo_reseau)){
        selection = reseau;
    }
    if (CheckCollisionPointRec(pos_souris, logo_maison)){
        selection = maison;
    }
    if (CheckCollisionPointRec(pos_souris, logo_usine)){
        selection = usine_electrique;
    }
    if (CheckCollisionPointRec(pos_souris, logo_chateauDO)){
        selection = chateau_deau;
    }
    if (CheckCollisionPointRec(pos_souris, logo_demolition)){
        selection = demolition;
    }
    if (selection != -1){
        switch (selection) {
            case 0:
                jeu->mode_Jeu = mode_neutre;
                break;
            case reseau:
                DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_reseau, (Vector2){0, TAILLE_CASE_GRILLE*(jeu->ordre.y+1)}, Fade(PURPLE, alphalogojeu1));
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    jeu->mode_Jeu = (jeu->mode_Jeu != mode_reseau) ? mode_reseau : mode_neutre;
                }
                break;
            case maison:
                DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_maison, (Vector2){90, TAILLE_CASE_GRILLE*(jeu->ordre.y+1)}, Fade(PURPLE, alphalogojeu1));
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    jeu->mode_Jeu = (jeu->mode_Jeu != mode_maison) ? mode_maison : mode_neutre;
                }
                break;
            case usine_electrique:
                DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_usine, (Vector2){180, TAILLE_CASE_GRILLE*(jeu->ordre.y+1)}, Fade(PURPLE, alphalogojeu1));
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    jeu->mode_Jeu = (jeu->mode_Jeu != mode_usine) ? mode_usine : mode_neutre;
                }
                break;
            case chateau_deau:
                DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_chateauDO, (Vector2){270, TAILLE_CASE_GRILLE*(jeu->ordre.y+1)}, Fade(PURPLE, alphalogojeu1));
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    jeu->mode_Jeu = (jeu->mode_Jeu != mode_chateauDO) ? mode_chateauDO : mode_neutre;
                }
                break;
            case demolition:
                DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_demolition, (Vector2){360, TAILLE_CASE_GRILLE*(jeu->ordre.y+1)}, Fade(PURPLE, alphalogojeu1));
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                    jeu->mode_Jeu = (jeu->mode_Jeu != mode_demolition) ? mode_demolition : mode_neutre;
                }
                break;
            default:
                break;
        }
    }
    if (jeu->mode_Jeu == mode_reseau)DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_reseau, (Vector2){0, TAILLE_CASE_GRILLE*jeu->ordre.y+20}, Fade(BLUE, alphalogojeu2));
    if (jeu->mode_Jeu == mode_maison)DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_maison, (Vector2){90, TAILLE_CASE_GRILLE*jeu->ordre.y+20}, Fade(BLUE, alphalogojeu2));
    if (jeu->mode_Jeu == mode_usine)DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_usine, (Vector2){180, TAILLE_CASE_GRILLE*jeu->ordre.y+20}, Fade(BLUE, alphalogojeu2));
    if (jeu->mode_Jeu == mode_chateauDO)DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_chateauDO, (Vector2){270, TAILLE_CASE_GRILLE*jeu->ordre.y+20}, Fade(BLUE, alphalogojeu2));
    if (jeu->mode_Jeu == mode_demolition)DrawTextureRec(jeu->tabImages[en_jeu][img_logosJeu].texture2D, logo_demolition, (Vector2){360, TAILLE_CASE_GRILLE*jeu->ordre.y+20}, Fade(BLUE, alphalogojeu2));
}
void afficher_construction_batiment(Jeu* jeu, Vector2 pos_souris){
    Vector2 pos_souris_maison = pos_souris;
    pos_souris_maison.x -= TAILLE_CASE_GRILLE*3/2;
    pos_souris_maison.y -= TAILLE_CASE_GRILLE*3/2;
    Color color_construction = Fade(WHITE, 0.5f);
    switch (jeu->mode_Jeu) {
        case mode_neutre:
            break;
        case mode_reseau:
            DrawTexture(jeu->tabImages[en_jeu][img_route].texture2D, (int)pos_souris.x-TAILLE_CASE_GRILLE/2, (int)pos_souris.y-TAILLE_CASE_GRILLE/2, color_construction);
            break;
        case mode_maison:
            jeu->tabImages[en_jeu][img_maison].source_Rec.x = 0 * jeu->tabImages[en_jeu][img_maison].frame_longueur; //c normal c pour me souvenir qu'il faut utiliser la mm structure de code pour augmenter les niv
            DrawTextureRec(jeu->tabImages[en_jeu][img_maison].texture2D, jeu->tabImages[en_jeu][img_maison].source_Rec, pos_souris_maison, color_construction);
            break;
        case mode_usine:
            DrawTexture(jeu->tabImages[en_jeu][img_usine].texture2D, (int)pos_souris.x-TAILLE_CASE_GRILLE*6/2, (int)pos_souris.y-TAILLE_CASE_GRILLE*4/2, color_construction);
            break;
        case mode_chateauDO:
            DrawTexture(jeu->tabImages[en_jeu][img_chateauDO].texture2D, (int)pos_souris.x-TAILLE_CASE_GRILLE*6/2, (int)pos_souris.y-TAILLE_CASE_GRILLE*4/2, color_construction);
            break;
        default:
            break;
    }
}
void afficher_batiment_Raylib(Jeu* jeu, Vector2 pos_souris){
    /*Vector2 playerPosition = { 0, 0 };
    playerPosition.x = pos_souris.x - 8;
    playerPosition.y = pos_souris.y - 8;*/

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){


    }

}
void affichage_defilement_fond(Jeu* jeu, int *timer){
    float alpha_fondu = 0.01f;
    if (*timer < 60*TEMPS_DEFILEMENT_FOND){
        DrawTexture(jeu->tabImages[en_jeu][img_fondJeu1].texture2D, 0, 0, Fade(WHITE, jeu->tabImages[en_jeu][img_fondJeu1].alpha));
    }else if (*timer < 60*(TEMPS_DEFILEMENT_FOND*2)){
        DrawTexture(jeu->tabImages[en_jeu][img_fondJeu2].texture2D, 0, 0, Fade(WHITE, jeu->tabImages[en_jeu][img_fondJeu2].alpha));
    }else if (*timer < 60*(TEMPS_DEFILEMENT_FOND*3)){
        DrawTexture(jeu->tabImages[en_jeu][img_fondJeu3].texture2D, 0, 0, Fade(WHITE, jeu->tabImages[en_jeu][img_fondJeu3].alpha));
    }else if (*timer < 60*(TEMPS_DEFILEMENT_FOND*4)){
        DrawTexture(jeu->tabImages[en_jeu][img_fondJeu4].texture2D, 0, 0, Fade(WHITE, jeu->tabImages[en_jeu][img_fondJeu4].alpha));
    }else if (*timer >= 60*(TEMPS_DEFILEMENT_FOND*4)) *timer = 0;
    if (*timer < 60*2)jeu->tabImages[en_jeu][img_fondJeu1].alpha += alpha_fondu;
    else if (*timer > 60*5 && *timer < 60*7)jeu->tabImages[en_jeu][img_fondJeu1].alpha -= alpha_fondu;
    else if (*timer > 60*7 && *timer < 60*9)jeu->tabImages[en_jeu][img_fondJeu2].alpha += alpha_fondu;
    else if (*timer > 60*12 && *timer < 60*14)jeu->tabImages[en_jeu][img_fondJeu2].alpha -= alpha_fondu;
    else if (*timer > 60*14 && *timer < 60*16)jeu->tabImages[en_jeu][img_fondJeu3].alpha += alpha_fondu;
    else if (*timer > 60*19 && *timer < 60*21)jeu->tabImages[en_jeu][img_fondJeu3].alpha -= alpha_fondu;
    else if (*timer > 60*21 && *timer < 60*23)jeu->tabImages[en_jeu][img_fondJeu4].alpha += alpha_fondu;
    else if (*timer > 60*26 && *timer < 60*28)jeu->tabImages[en_jeu][img_fondJeu4].alpha -= alpha_fondu;
}
void afficherJeu(Jeu* jeu, Vector2 pos_souris, int* timer){
    Vector2 playerPosition = { 0, 0 };
    int playerTileX = 0;
    int playerTileY = 0;
    playerPosition.x = pos_souris.x - 8;
    playerPosition.y = pos_souris.y - 8;

    if (playerPosition.x < 0) playerPosition.x = 0;
    else if ((playerPosition.x + PLAYER_SIZE) > ((jeu->ordre.x +1)* TAILLE_CASE_GRILLE )) playerPosition.x = (jeu->ordre.x+1) * TAILLE_CASE_GRILLE - PLAYER_SIZE;
    if (playerPosition.y < 0) playerPosition.y = 0;
    else if ((playerPosition.y + PLAYER_SIZE) > ((jeu->ordre.y +1)* TAILLE_CASE_GRILLE )) playerPosition.y = (jeu->ordre.y+1) * TAILLE_CASE_GRILLE - PLAYER_SIZE;


    playerTileX = (int)((playerPosition.x + TAILLE_CASE_GRILLE / 2) / TAILLE_CASE_GRILLE);
    playerTileY = (int)((playerPosition.y + TAILLE_CASE_GRILLE / 2) / TAILLE_CASE_GRILLE);

    ClearBackground(RAYWHITE);
    /*for (int y = 0; y < jeu->ordre.y; y++)
        for (int x = 0; x < jeu->ordre.x; x++)
            if (ordre.tileFog[y * ordre.x + x] == 0) DrawRectangle(x, y, 1, 1, WHITE);
            else if (ordre.tileFog[y * ordre.x + x] == 2) DrawRectangle(x, y, 1, 1, Fade(WHITE, 0.8f));*/
    BeginDrawing();

    ClearBackground(BLACK);

    affichage_defilement_fond(jeu, timer);

    for (int y = 0; y <= jeu->ordre.y; y++){
        for (int x = 0; x <= jeu->ordre.x; x++){
            DrawRectangle(x * TAILLE_CASE_GRILLE, (y) * TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, WHITE);
            DrawRectangle(x * TAILLE_CASE_GRILLE, (y) * TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, Fade(BLACK, 0.8f));
            DrawRectangleLines(x * TAILLE_CASE_GRILLE, (y) * TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, Fade(WHITE, 0.6f));
        }
    }
    affi_bouton(jeu, jeu->page_actuel, img_boutonRetourMenu, pos_souris, "MENU", timer);
    afficher_jeu_logo_interactionAvecClick(jeu, pos_souris);
    afficher_construction_batiment(jeu, pos_souris);

    DrawRectangleV(playerPosition, (Vector2){ PLAYER_SIZE, PLAYER_SIZE }, RED);
    DrawText(TextFormat("Case Actuelle: [%i,%i]", playerTileX, playerTileY), RESOLUTION_X-220, 0, 20, WHITE);
    jeu->selection.x = playerTileX;
    jeu->selection.y = playerTileY;
    EndDrawing();
}




#include "affichage.h"

void affichage_Boucle_G(Jeu* jeu){
    InitWindow(RESOLUTION_X, RESOLUTION_Y, "ECE-CITY BETA/ALPHA de L'OMEGA");
    InitAudioDevice();      // Initialise le haut-parleur
    jeu->quitter = 0;
    initialisation_Images(jeu);
    initialisation_Sons(jeu);
    ToggleFullscreen();

    int ballPositionX = -100;
    int ballRadius = 20;
    float ballAlpha = 0.0f;
    int state = 0;
    int timer = 0;
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
                afficherJeu(jeu);
                break;
        }
        timer++;
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
    affi_bouton(jeu, jeu->page_actuel, img_boutonCredits, pos_Souris, "CREDITS");
    affi_bouton(jeu, jeu->page_actuel, img_boutonRegles, pos_Souris, "RULES");
    affi_bouton(jeu, jeu->page_actuel, img_boutonJouer, pos_Souris, "START");
    affi_bouton(jeu, jeu->page_actuel, img_boutonSauvegarder, pos_Souris, "SAVE");
    affi_bouton(jeu, jeu->page_actuel, img_boutonoff, pos_Souris, "EXIT");
    affi_bouton(jeu, jeu->page_actuel, img_suppSave, pos_Souris, "RESET");
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


void affi_bouton(Jeu* jeu, int page, int image, Vector2 mousePoint, char* nom){
    int btnState;
    bool btnAction;
    btnAction = false;
    if (CheckCollisionPointRec(mousePoint, jeu->tabImages[page][image].pos_Rec))
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
                jeu->page_actuel = en_jeu;
                break;
            case img_suppSave:
                printf("Destruction de votre ancien fichier de sauvegarde (si vous en aviez un)\n");
                remove(NOM_DU_FICHIER);
                lire_graphe(jeu);
                break;
        }
    }
    jeu->tabImages[page][image].source_Rec.y = btnState * jeu->tabImages[page][image].frame_hauteur;
    DrawTextureRec(jeu->tabImages[page][image].texture2D, jeu->tabImages[page][image].source_Rec, (Vector2){jeu->tabImages[page][image].pos_Rec.x, jeu->tabImages[page][image].pos_Rec.y }, WHITE);
    DrawText(nom, jeu->tabImages[page][image].pos_Rec.x + 40, jeu->tabImages[page][image].pos_Rec.y + 40, 30, BLACK);
}

void afficherJeu(Jeu* jeu){
    Vector2 playerPosition = { 0, 0 };
    int playerTileX = 0;
    int playerTileY = 0;
    Vector2 mousePosition = { 0 };
    SetTargetFPS(60);

    mousePosition = GetMousePosition();
    playerPosition.x = mousePosition.x-8;
    playerPosition.y = mousePosition.y-8;

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

        ClearBackground(RAYWHITE);

        for (int y = 0; y <= jeu->ordre.y; y++){
            for (int x = 0; x <= jeu->ordre.x; x++){
                // Draw tiles from id (and tile borders)
                DrawRectangle(x * TAILLE_CASE_GRILLE, (y) * TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, Fade(BLACK, 0.3f));
                DrawRectangleLines(x * TAILLE_CASE_GRILLE, (y) * TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, TAILLE_CASE_GRILLE, Fade(WHITE, 0.5f));
            }
        }

        DrawRectangleV(playerPosition, (Vector2){ PLAYER_SIZE, PLAYER_SIZE }, RED);

        DrawText(TextFormat("Current tile: [%i,%i]", playerTileX, playerTileY), RESOLUTION_X-200, 0, 20, BLACK);
    EndDrawing();
}


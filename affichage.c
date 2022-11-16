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
        Vector2 pos_Souris = GetMousePosition();
        if(jeu->page_actuel == animation_Lancement) afficher_animation(jeu, &ballPositionX, &ballRadius, &ballAlpha, &state, &timer);
        else if(jeu->page_actuel == menu_principale) afficher_fenetre_menu(jeu, pos_Souris, &timer,&fade, &fadeson);
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
    affi_bouton(jeu, jeu->page_actuel, img_boutonRegles, pos_Souris, "REGLES");
    affi_bouton(jeu, jeu->page_actuel, img_boutonJouer, pos_Souris, "START");
    affi_bouton(jeu, jeu->page_actuel, img_boutonoff, pos_Souris, "EXIT");
    if (*timer <=300){
        *rectAplha -= 0.01f;
        *sonAlpha += 0.01f;
        if(*sonAlpha < 0.06f){
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
    DrawCircle(*ballPositionX, RESOLUTION_Y/2, (float)*ballRadius, Fade(RED, 1.0f - *ballAlpha));

    if (*state == 3) {
        *framesCounter = 0;
        jeu->page_actuel = menu_principale;
    }
    EndDrawing();
}

void afficher_la_grille(Jeu* jeu){
    for (int y = 0; y < jeu->ordre_en_y; y++) {
        for (int x = 0; x < jeu->ordre_en_x; x++) {
            printf("%d ", jeu->terrain[y][x]);
        }
        printf("\n");
    }
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
        if(image == img_boutonoff){
            jeu->quitter = 1;
        }
    }
    jeu->tabImages[page][image].source_Rec.y = btnState * jeu->tabImages[page][image].frame_hauteur;
    DrawTextureRec(jeu->tabImages[page][image].texture2D, jeu->tabImages[page][image].source_Rec, (Vector2){jeu->tabImages[page][image].pos_Rec.x, jeu->tabImages[page][image].pos_Rec.y }, WHITE);
    DrawText(nom, jeu->tabImages[page][image].pos_Rec.x + 40, jeu->tabImages[page][image].pos_Rec.y + 40, 30, BLACK);
}




void afficherJeu(Jeu* jeu){
    InitWindow(RESOLUTION_X, RESOLUTION_Y, "ECE-CITY BETA/ALPHA de L'OMEGA |||||PROTOTYPE|||||");
    SetWindowPosition(0, 50);

    Map map = { 0 };
    map.tilesX = jeu->ordre_en_x;
    map.tilesY = jeu->ordre_en_y;
    map.tileIds = (unsigned char *)calloc(map.tilesX*map.tilesY, sizeof(unsigned char));
    map.tileFog = (unsigned char *)calloc(map.tilesX*map.tilesY, sizeof(unsigned char));

    for (int i = 0; i < map.tilesY*map.tilesX; i++) map.tileIds[i] = GetRandomValue(0, 1);

    Vector2 playerPosition = { 0, 0 };
    int playerTileX = 0;
    int playerTileY = 0;
    Vector2 mousePosition = { 0 };
    SetTargetFPS(60);


    while (!WindowShouldClose())
    {

        mousePosition = GetMousePosition();
        playerPosition.x = mousePosition.x-8;
        playerPosition.y = mousePosition.y-8;

        if (playerPosition.x < 0) playerPosition.x = 0;
        else if ((playerPosition.x + PLAYER_SIZE) > (map.tilesX*MAP_TILE_SIZE)) playerPosition.x = map.tilesX*MAP_TILE_SIZE - PLAYER_SIZE;
        if (playerPosition.y < 0) playerPosition.y = 0;
        else if ((playerPosition.y + PLAYER_SIZE) > (map.tilesY*MAP_TILE_SIZE)) playerPosition.y = map.tilesY*MAP_TILE_SIZE - PLAYER_SIZE;

        for (int i = 0; i < map.tilesX*map.tilesY; i++) if (map.tileFog[i] == 1) map.tileFog[i] = 2;

        playerTileX = (int)((playerPosition.x + MAP_TILE_SIZE/2)/MAP_TILE_SIZE);
        playerTileY = (int)((playerPosition.y + MAP_TILE_SIZE/2)/MAP_TILE_SIZE);

        ClearBackground(RAYWHITE);
        for (int y = 0; y < map.tilesY; y++)
            for (int x = 0; x < map.tilesX; x++)
                if (map.tileFog[y*map.tilesX + x] == 0) DrawRectangle(x, y, 1, 1, WHITE);
                else if (map.tileFog[y*map.tilesX + x] == 2) DrawRectangle(x, y, 1, 1, Fade(WHITE, 0.8f));

        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int y = 0; y < map.tilesY; y++){
            for (int x = 0; x < map.tilesX; x++){
                // Draw tiles from id (and tile borders)
                DrawRectangle(x*MAP_TILE_SIZE, y*MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, Fade(BLACK, 0.3f));
                DrawRectangleLines(x*MAP_TILE_SIZE, y*MAP_TILE_SIZE, MAP_TILE_SIZE, MAP_TILE_SIZE, Fade(WHITE, 0.5f));
            }
        }

        DrawRectangleV(playerPosition, (Vector2){ PLAYER_SIZE, PLAYER_SIZE }, RED);

        DrawText(TextFormat("Current tile: [%i,%i]", playerTileX, playerTileY), 10, 10, 20, BLACK);

        EndDrawing();
    }
    free(map.tileIds);
    free(map.tileFog);
    CloseWindow();
}


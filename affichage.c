#include "affichage.h"
#include "Jeu.h"

#define MAP_TILE_SIZE    20
#define PLAYER_SIZE      16

#define MOUSE_SCALE_MARK_SIZE   12

bool mouseScaleReady = false;
bool mouseScaleMode = false;


void afficher_fenetre(){
    InitWindow(RESOLUTION_X, RESOLUTION_Y, "bonjour je suis un test");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowPosition(0, 50);
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        float f = (float)GetScreenWidth() / (float)GetScreenHeight();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("la co de l'ecole est eclatee", 12 * f, 12 * f, 20 * f, WHITE);
        EndDrawing();
    }
}

void afficher_la_grille(Jeu* jeu){
    for (int y = 0; y < jeu->ordre_en_y; y++) {
        for (int x = 0; x < jeu->ordre_en_x; x++) {
            printf("%d ", jeu->terrain[y][x]);
        }
        printf("\n");
    }
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

        for (int y = 0; y < map.tilesY; y++)
        {
            for (int x = 0; x < map.tilesX; x++)
            {
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



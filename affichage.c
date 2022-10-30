#include "affichage.h"
#include "Jeu.h"

/*void afficher_fenetre(){
    InitWindow(RESOLUTION_X, RESOLUTION_Y, "bonjour je suis un test");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowPosition(0, 50);

    while (!WindowShouldClose()) {
        float f = (float)GetScreenWidth() / (float)GetScreenHeight();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("la co de l'ecole est eclatee", 12 * f, 12 * f, 20 * f, WHITE);
        EndDrawing();
    }
}*/

void afficher_la_grille(Jeu* jeu){
    for (int y = 0; y < jeu->ordre_en_y; y++) {
        for (int x = 0; x < jeu->ordre_en_x; x++) {
            printf("%d ", jeu->terrain[y][x]);
        }
        printf("\n");
    }
}


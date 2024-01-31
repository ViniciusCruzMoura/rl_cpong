#include "game.h"

void InitTitleScreen() {}

void UpdateTitleScreen() {
    // Update TITLE screen data here!
    game.framesCounter++;
    if (IsKeyPressed(KEY_ENTER)) game.currentScreen = GAMEPLAY;
    UpdateMenu(&game.menu);
}

void DrawTitleScreen() {
    // Draw TITLE screen here!
    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
    if ((game.framesCounter/30)%2 == 0) DrawText("PRESS [ENTER] to START", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to START", 20)/2, GetScreenHeight()/2 + 60, 20, DARKGRAY);
    DrawMenu(game.menu);
}

void UnloadTitleScreen() {}
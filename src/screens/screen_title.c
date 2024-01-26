#include "core\game.h"

void init_title_screen() {}

void update_title_screen() {
    // Update TITLE screen data here!
    game.framesCounter++;
    if (IsKeyPressed(KEY_ENTER)) game.currentScreen = GAMEPLAY;
    update_menu(&game.menu);
}

void draw_title_screen() {
    // Draw TITLE screen here!
    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
    if ((game.framesCounter/30)%2 == 0) DrawText("PRESS [ENTER] to START", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to START", 20)/2, GetScreenHeight()/2 + 60, 20, DARKGRAY);
    draw_menu(game.menu);
}

void unload_title_screen() {}
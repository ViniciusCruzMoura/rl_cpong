#include "core\game.h"

void init_ending_screen() {}

void update_ending_screen() {
    // Update END screen data here!
    game.framesCounter++;
            
    if (IsKeyPressed(KEY_ENTER))
    {
        // Replay / Exit game logic
        game.currentScreen = TITLE;
    }
}

void draw_ending_screen() {
    // Draw END screen here!
    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);                
    if ((game.framesCounter/30)%2 == 0) DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 + 80, 20, GRAY);
}

void unload_ending_screen() {}

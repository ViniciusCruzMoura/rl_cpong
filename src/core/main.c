#include <string.h>
#include "game.h"

// Game required variables
CGame game;

int main(void)
{
    InitCGame();        // Initialize game setups

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateCGame();      // Update game logic
        DrawCGame();        // Update game render
    }

    UnloadCGame();         // Unload loaded data (textures, sounds, models...)
    CloseWindow();        // Close window and OpenGL context

    return 0;
}


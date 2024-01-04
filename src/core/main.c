#include <string.h>
#include "game.h"

// Game required variables
CGame game;

int main(void)
{
    InitGame();        // Initialize game setups

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateGame();      // Update game logic
        DrawGame();        // Update game render
    }

    UnloadGame();         // Unload loaded data (textures, sounds, models...)
    CloseWindow();        // Close window and OpenGL context

    return 0;
}


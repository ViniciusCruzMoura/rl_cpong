#include "raylib.h"
#include <string.h>
#include "core/game.h"

int main(void)
{
    screenScale = 3.0;
    screenWidth = WIN_RES_W*(int)screenScale;
    screenHeight = WIN_RES_H*(int)screenScale;
    
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "raylib - CPong");
    
    // Textures loading
    texLogo = LoadTexture("resources/raylib_logo.png");
    InitGame();

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    UnloadGame();         // Unload loaded data (textures, sounds, models...)
    CloseWindow();        // Close window and OpenGL context

    return 0;
}


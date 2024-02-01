#include "game.h"

void SetInitialScreenParams() {
    game.currentScreen = LOGO;
    game.screenScale = 3.0;
    game.screenWidth = WIN_RES_W * game.screenScale;
    game.screenHeight = WIN_RES_H * game.screenScale;
    game.fullscreen = false; // IsWindowFullscreen()
}

void SetWindowConfig() {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(game.screenWidth, game.screenHeight, "raylib - CPong");
}

void SetFullscreenMode() {
    if (game.fullscreen) {
        game.screenWidth = GetMonitorWidth(GetCurrentMonitor());
        game.screenHeight = GetMonitorHeight(GetCurrentMonitor());
        game.screenScale = game.screenHeight / WIN_RES_H;
        // game.screenScale = game.screenWidth / WIN_RES_W;
        SetWindowSize(game.screenWidth, game.screenHeight);
        ToggleFullscreen();
    }
}

void InitializeGameElements() {
    game.gamePaused = false;  // Game paused state toggle
    game.gameOver = false;
    game.elementPositionY = -128;
    game.framesCounter = 0;  // General purpose frames counter

    InitPlayer(&game.player, game.screenWidth - 50, game.screenHeight / 2, game.screenScale);
    InitBall(&game.ball, game.screenScale);
    InitMenu(&game.menu, (Vector2){game.screenWidth / 2, game.screenHeight / 2.5f});
}

void LoadAssets() {
    game.texLogo = LoadTexture("assets/textures/raylib_logo.png");
}

void LoadSounds() {
    InitAudioDevice();      // Initialize audio device
    game.soundArray[0] = LoadSound("assets/sounds/pong.wav");
}

void ConfigureFrameRate() {
    SetTargetFPS(60);
}

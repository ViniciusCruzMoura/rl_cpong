#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "entity.h"

#define WIN_RES_W 256
#define WIN_RES_H 192
#define MAX_SOUNDS 1

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

typedef struct CGame {
    GameScreen currentScreen;
    float screenScale;
    int screenWidth;
    int screenHeight;
    CPaddle paddleLeft;
    CPaddle paddleRight;
    CBall ball;
    int isMouseClickingPaddle;
    int isMouseOverPaddle;
    char winner[32];
    int elementPositionY;
    int framesCounter;
    Texture2D texLogo;
    bool gamePaused;
    Sound soundArray[MAX_SOUNDS];
} CGame;

extern CGame game;

void InitGame();         // Initialize game
void UpdateGame();       // Update game (one frame)
void DrawGame();         // Draw game (one frame)
void UnloadGame();       // Unload game assets

#endif // GAME_H
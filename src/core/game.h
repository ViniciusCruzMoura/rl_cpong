#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Paddle.h"
#include "Ball.h"

#define WIN_RES_W 256
#define WIN_RES_H 192

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

typedef struct CGame {
    GameScreen currentScreen;
    float screenScale;
    int screenWidth;
    int screenHeight;
    float delta;
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
} CGame;

extern CGame game;

void InitCGame();         // Initialize game
void UpdateCGame();       // Update game (one frame)
void DrawCGame();         // Draw game (one frame)
void UnloadCGame();       // Unload game assets

#endif // GAME_H
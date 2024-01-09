#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "entity.h"

#define WIN_RES_W 256
#define WIN_RES_H 192
#define MAX_SOUNDS 1

typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

typedef struct CGame {
    // game state
    GameScreen currentScreen;
    bool gamePaused;
    
    // window config
    float screenScale;
    int screenWidth;
    int screenHeight;
    
    // players and objects
    CPaddle paddleLeft;
    CPaddle paddleRight;
    CBall ball;
    
    // actions
    int isMouseClickingPaddle;
    int isMouseOverPaddle;
    
    // infos
    char winner[32];
    int elementPositionY;
    int framesCounter;
    bool gameOver;
    
    // resources
    Texture2D texLogo;
    Sound soundArray[MAX_SOUNDS];
} CGame;

extern CGame game;

void InitGame();         // Initialize game
void UpdateGame();       // Update game (one frame)
void DrawGame();         // Draw game (one frame)
void UnloadGame();       // Unload game assets

#endif // GAME_H
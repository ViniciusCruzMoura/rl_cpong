#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "menu.h"
#include "ball.h"
#include "player.h"
#include "screens.h"
#include "settings.h"
#include <string.h>
#include <stdio.h>
// #include <unistd.h>

#define WIN_RES_W 256
#define WIN_RES_H 192
#define MAX_SOUNDS 1

// typedef enum GameScreen { LOGO, TITLE, GAMEPLAY, ENDING } GameScreen;

typedef struct Game {
    // game state
    GameScreen currentScreen;
    bool gamePaused;
    
    // window config
    float screenScale;
    int screenWidth;
    int screenHeight;
    bool fullscreen;
    
    // players and objects
    struct Ball ball;
    struct Player player;
    
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

    // menus
    Menu menu;
} Game;

extern Game game;

void InitGame();         // Initialize game
void UpdateGame();       // Update game (one frame)
void DrawGame();         // Draw game (one frame)
void UnloadGame();       // Unload game assets

#endif // GAME_H
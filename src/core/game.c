#include <string.h>
#include <stdio.h>
#include "core/Game.h"

void InitCGame() 
{
    game.currentScreen = LOGO;
    game.screenScale = 3.0;
    game.screenWidth = GetMonitorWidth(GetCurrentMonitor());
    game.screenHeight = GetMonitorHeight(GetCurrentMonitor());
    
    game.screenWidth = WIN_RES_W*game.screenScale;
    game.screenHeight = WIN_RES_H*game.screenScale;
    InitWindow(game.screenWidth, game.screenHeight, "raylib - CPong");

    game.gamePaused = false;  // Game paused state toggle
    game.elementPositionY = -128;
    game.framesCounter = 0;  // General pourpose frames counter

    game.paddleLeft = InitCPaddle(50, game.screenHeight / 2, game.screenScale);
    game.paddleRight = InitCPaddle(game.screenWidth - 50, game.screenHeight / 2, game.screenScale);
    game.ball = InitCBall(GetRenderWidth() / 2.0f, GetScreenHeight() / 2.0f, game.screenScale);

    // SetConfigFlags(FLAG_VSYNC_HINT);
    // InitWindow(game.screenWidth, game.screenHeight, "raylib - CPong");
    // if (!IsWindowFullscreen()) {
    //     SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
    //     ToggleFullscreen();
    // }

    // Textures loading
    game.texLogo = LoadTexture("resources/raylib_logo.png");
    
    SetTargetFPS(60);
}

void UpdateCGame()
{
    switch(game.currentScreen)
    {
        case LOGO: 
        {
            // Update LOGO screen data here!
            
            game.framesCounter++;
            
            if (game.framesCounter > 180) 
            {
                game.currentScreen = TITLE;    // Change to TITLE screen after 3 seconds
                game.framesCounter = 0;
            }
            
        } break;
        case TITLE: 
        {
            // Update TITLE screen data here!
            
            game.framesCounter++;
            
            if (IsKeyPressed(KEY_ENTER)) game.currentScreen = GAMEPLAY;

        } break;
        case GAMEPLAY:
        { 
            // Update GAMEPLAY screen data here!

            if (IsKeyPressed(KEY_SPACE)) game.gamePaused = !game.gamePaused;

            if (!game.gamePaused)
            {
                // TODO: Gameplay logic
                game.ball.position.x += game.ball.speed.x * GetFrameTime();
                game.ball.position.y += game.ball.speed.y * GetFrameTime();
                if (game.ball.position.y < 0) {
                    game.ball.position.y = 0;
                    game.ball.speed.y *= -1;
                }
                if (game.ball.position.y > GetScreenHeight()) {
                    game.ball.speed.y *= -1;
                }

                if (IsKeyDown(KEY_W)) game.paddleLeft.rec.y -= game.paddleLeft.speed * GetFrameTime();
                if (IsKeyDown(KEY_S)) game.paddleLeft.rec.y += game.paddleLeft.speed * GetFrameTime();
                if (IsKeyDown(KEY_UP)) game.paddleRight.rec.y -= game.paddleRight.speed * GetFrameTime();
                if (IsKeyDown(KEY_DOWN)) game.paddleRight.rec.y += game.paddleRight.speed * GetFrameTime();
                
                // left paddle AI
                if (game.ball.position.x > GetScreenWidth()/2 && game.ball.speed.x > 0) {
                    int debuff = 1.2f;
                    if (game.paddleRight.rec.y == game.ball.position.y) {
                    game.paddleRight.rec.y = game.ball.position.y + -game.paddleRight.rec.height/2;
                    } else if (game.paddleRight.rec.y - -game.paddleRight.rec.height/2 > game.ball.position.y) {
                        game.paddleRight.rec.y -= game.paddleRight.speed/debuff * GetFrameTime();
                    } else if (game.paddleRight.rec.y - -game.paddleRight.rec.height/2 < game.ball.position.y) {
                        game.paddleRight.rec.y += game.paddleRight.speed/debuff * GetFrameTime();
                    }
                }
                // right paddle AI
                if (game.ball.position.x < GetScreenWidth()/2 && game.ball.speed.x < 0) {
                    int debuff = 1.2f;
                    if (game.paddleLeft.rec.y == game.ball.position.y) {
                    game.paddleLeft.rec.y = game.ball.position.y + -game.paddleLeft.rec.height/2;
                    } else if (game.paddleLeft.rec.y - -game.paddleLeft.rec.height/2 > game.ball.position.y) {
                        game.paddleLeft.rec.y -= game.paddleLeft.speed/debuff * GetFrameTime();
                    } else if (game.paddleLeft.rec.y - -game.paddleLeft.rec.height/2 < game.ball.position.y) {
                        game.paddleLeft.rec.y += game.paddleLeft.speed/debuff * GetFrameTime();
                    }
                }
                
                

                if (CheckCollisionCircleRec(game.ball.position, game.ball.radius, game.paddleLeft.rec) && game.ball.speed.x < 0) {
                    game.ball.speed.x *= -1.1f;
                    game.ball.speed.y = (game.ball.position.y - game.paddleLeft.rec.y) / (game.paddleLeft.rec.height / 2) * game.ball.speed.x;
                }
                if (CheckCollisionCircleRec(game.ball.position, game.ball.radius, game.paddleRight.rec) && game.ball.speed.x > 0) {
                    game.ball.speed.x *= -1.1f;
                    game.ball.speed.y = (game.ball.position.y - game.paddleRight.rec.y) / (game.paddleRight.rec.height / 2) * -game.ball.speed.x;
                }

                if (game.ball.position.x < 0) {
                    strcpy(game.winner, "RIGHT_PADDLE_WIN");
                    game.gamePaused = !game.gamePaused;
                }
                else if (game.ball.position.x > GetScreenWidth()) {
                    strcpy(game.winner, "LEFT_PADDLE_WIN");
                    game.gamePaused = !game.gamePaused;
                }

                game.showRedScreen = 0;
                game.showGreenScreen = 0;
                if (CheckCollisionPointRec(GetMousePosition(), game.paddleLeft.rec)) {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) game.showGreenScreen = 1;
                    else game.showRedScreen = 1;
                }
            }

        } break;
        case ENDING: 
        {
            // Update END screen data here!
            
            game.framesCounter++;
            
            if (IsKeyPressed(KEY_ENTER))
            {
                // Replay / Exit game logic
                game.currentScreen = TITLE;
            }
            
        } break;
        default: break;
    }
}

void DrawCGame()
{
    BeginDrawing();

        // ClearBackground(RAYWHITE);
        ClearBackground(BLACK);
        
        switch(game.currentScreen) 
        {
            case LOGO: 
            {
                // Draw LOGO screen here!
                
                DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);

                game.elementPositionY += 3;
                if (game.elementPositionY > (game.screenHeight/3 - 64)) game.elementPositionY = game.screenHeight/3 - 64;
                DrawTexturePro(
                    game.texLogo,
                    (Rectangle){ 0, 0, game.texLogo.width, game.texLogo.height },
                    (Rectangle){ game.screenWidth/2, game.screenHeight/2, game.texLogo.width, game.texLogo.height },
                    (Vector2){ game.texLogo.width / 2, game.texLogo.height / 2 - game.elementPositionY /4 },
                    0,
                    WHITE
                );
                
            } break;
            case TITLE: 
            {
                // Draw TITLE screen here!
                
                DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                
                if ((game.framesCounter/30)%2 == 0) DrawText("PRESS [ENTER] to START", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] to START", 20)/2, GetScreenHeight()/2 + 60, 20, DARKGRAY);
                
            } break;
            case GAMEPLAY:
            { 
                // Draw GAMEPLAY screen here!

                // Draw pause message when required
                if (game.gamePaused) DrawText("GAME PAUSED", game.screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, game.screenHeight/2 + 60, 40, GRAY);

                if (game.showGreenScreen) ClearBackground(GREEN);
                if (game.showRedScreen) ClearBackground(RED);
                DrawCBall(game.ball);
                DrawCPaddle(game.paddleLeft);
                DrawCPaddle(game.paddleRight);

                if (strcmp(game.winner, "RIGHT_PADDLE_WIN") == 0) {
                    char msg[] = "Congrats! The right player win the game!";
                    DrawText(
                        msg,
                        GetScreenWidth()/2.0f - MeasureText(msg, 12*game.screenScale)/2,
                        GetScreenHeight()/4.0f, 
                        12*game.screenScale, 
                        LIGHTGRAY
                    );
                }
                else if (strcmp(game.winner, "LEFT_PADDLE_WIN") == 0) {
                    char msg[] = "Congrats! The left player win the game!";
                    DrawText(
                        msg,
                        GetScreenWidth()/2.0f - MeasureText(msg, 12*game.screenScale)/2, 
                        GetScreenHeight()/4.0f, 
                        12*game.screenScale, 
                        LIGHTGRAY
                    );
                }
                
            } break;
            case ENDING: 
            {
                // Draw END screen here!
                
                DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                
                if ((game.framesCounter/30)%2 == 0) DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth()/2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20)/2, GetScreenHeight()/2 + 80, 20, GRAY);
                
            } break;
            default: break;
        }
        /** 
        char buf[1024];
        snprintf(
            buf, 1024, 
            "Debug:\n" \
            "- GetMonitorWidth: (%d)\n" \
            "- GetMonitorHeight: (%d)\n" \
            "- game.currentScreen (%d)\n" \
            "- game.framesCounter (%d)\n" \
            "- game.elementPositionY (%d)\n" \
            "- game.winner (%s)\n"
            , GetMonitorWidth(GetCurrentMonitor())
            , GetMonitorHeight(GetCurrentMonitor())
            , game.currentScreen
            , game.framesCounter
            , game.elementPositionY
            , game.winner
            );
        DrawRectangle(0, 0, MeasureText(buf, 10), GetScreenHeight()/2, Fade(SKYBLUE, 0.5f));        
        DrawRectangleLines(0, 0, MeasureText(buf, 10), GetScreenHeight()/2, BLUE);
        DrawText(TextFormat(buf), 0, 0, 10, WHITE);
        */
    EndDrawing();
}

void UnloadCGame()
{
    // Unload textures
    UnloadTexture(game.texLogo);
}
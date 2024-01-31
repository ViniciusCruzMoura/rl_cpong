#include "game.h"

void init_gameplay_screen() {}

void update_gameplay_screen() {
    // Update GAMEPLAY screen data here!
    if (IsKeyPressed(KEY_SPACE)) game.gamePaused = !game.gamePaused;

    if (!game.gamePaused && !game.gameOver)
    {
        // TODO: Gameplay logic

        UpdateBall(&game.ball, &game.player, &game.soundArray);

        UpdatePlayer(&game.player, &game.ball);

        // THE MOUSE IS COLLIDING WITH THE PADDLE
        game.isMouseOverPaddle = 0;
        game.isMouseClickingPaddle = 0;
        if (CheckCollisionPointRec(GetMousePosition(), game.player.paddleLeft.rec)) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) game.isMouseClickingPaddle = 1;
            else game.isMouseOverPaddle = 1;
        }

        // THE PLAYER WON THE GAME
        if (game.ball.position.x < 0) {
            strcpy(game.winner, "RIGHT_PADDLE_WIN");
            //game.gamePaused = !game.gamePaused;
            game.gameOver = true;
        }
        else if (game.ball.position.x > GetScreenWidth()) {
            strcpy(game.winner, "LEFT_PADDLE_WIN");
            //game.gamePaused = !game.gamePaused;
            game.gameOver = true;
        }
        
    }

    // RESET GAME
    if (IsKeyDown(KEY_Q)) {
        strcpy(game.winner, "");
        game.currentScreen = LOGO;
        game.gameOver = false;
        game.gamePaused = false;  // Game paused state toggle
        game.elementPositionY = -128;
        game.framesCounter = 0;  // General pourpose frames counter
        
        InitPlayer(&game.player, game.screenWidth - 50, game.screenHeight / 2, game.screenScale);
        InitBall(&game.ball, game.screenScale);
    }
}

void draw_gameplay_screen() {
    // Draw GAMEPLAY screen here!
    // Draw pause message when required
    if (game.gamePaused) DrawText("GAME PAUSED", game.screenWidth/2 - MeasureText("GAME PAUSED", 40)/2, game.screenHeight/2 + 60, 40, GRAY);

    if (game.isMouseOverPaddle) ClearBackground(GREEN);
    if (game.isMouseClickingPaddle) ClearBackground(RED);
    DrawBall(game.ball);
    DrawPlayer(game.player);

    if (game.gameOver) {
        if (strcmp(game.winner, "RIGHT_PADDLE_WIN") == 0) {
            char msg[] = "Congrats! The right player win the game!";
            DrawText(
                msg,
                GetScreenWidth()/2.0f - MeasureText(msg, 12*game.screenScale)/2,
                GetScreenHeight()/4.0f, 
                12*game.screenScale, 
                LIGHTGRAY
            );
            char msg2[] = "PRESS [Q] TO PLAY AGAIN";
            DrawText(
                msg2, 
                GetScreenWidth()/2 - MeasureText(msg2, 20)/2, 
                GetScreenHeight()/2 + 180, 
                20, 
                GRAY
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
            char msg2[] = "PRESS [Q] TO PLAY AGAIN";
            DrawText(
                msg2, 
                GetScreenWidth()/2 - MeasureText(msg2, 20)/2, 
                GetScreenHeight()/2 + 280, 
                20, 
                GRAY
            );
        }
    }
}

void unload_gameplay_screen() {}

#include "game.h"

CPaddle InitCPaddle(int x, int y, int screenScale)
{
    CPaddle paddle;
    paddle.rec.x = x;
    paddle.rec.y = y;
    paddle.rec.width = 5 * screenScale;
    paddle.rec.height = 50 * screenScale;
    paddle.speed = 300 * screenScale;
    return paddle;
}

void DrawCPaddle(CPaddle paddle)
{
    DrawRectangleRec(paddle.rec, WHITE);
}

void MoveCPaddle()
{
    if (IsKeyDown(KEY_W)) game.paddleLeft.rec.y -= game.paddleLeft.speed * GetFrameTime();
    if (IsKeyDown(KEY_S)) game.paddleLeft.rec.y += game.paddleLeft.speed * GetFrameTime();
    if (IsKeyDown(KEY_UP)) game.paddleRight.rec.y -= game.paddleRight.speed * GetFrameTime();
    if (IsKeyDown(KEY_DOWN)) game.paddleRight.rec.y += game.paddleRight.speed * GetFrameTime();
}

void AI_CPaddle()
{
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
}
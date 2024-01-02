#include "game.h"

CBall InitCBall(int x, int y, int screenScale)
{
    CBall ball;
    ball.position.x = x;
    ball.position.y = y;
    ball.speed.x = 100 * screenScale;
    ball.speed.y = 100 * screenScale;
    ball.radius = 3 * screenScale;
    return ball;   
}

void DrawCBall(CBall ball)
{
    DrawCircleV(ball.position, ball.radius, WHITE);
}

void MoveCBall()
{
    game.ball.position.x += game.ball.speed.x * GetFrameTime();
    game.ball.position.y += game.ball.speed.y * GetFrameTime();
    if (game.ball.position.y < 0) {
        game.ball.position.y = 0;
        game.ball.speed.y *= -1;
    }
    if (game.ball.position.y > GetScreenHeight()) {
        game.ball.speed.y *= -1;
    }
}
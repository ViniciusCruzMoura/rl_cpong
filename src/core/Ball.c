#include "core/Ball.h"

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
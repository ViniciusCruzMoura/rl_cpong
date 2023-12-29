#include "core/Paddle.h"

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
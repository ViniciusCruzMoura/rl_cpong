#include "Collision.h"
#include "game.h"

void IsBallCollidingPaddle()
{
    if (CheckCollisionCircleRec(game.ball.position, game.ball.radius, game.paddleLeft.rec) && game.ball.speed.x < 0) {
        game.ball.speed.x *= -1.1f;
        game.ball.speed.y = (game.ball.position.y - game.paddleLeft.rec.y) / (game.paddleLeft.rec.height / 2) * game.ball.speed.x;
    }
    if (CheckCollisionCircleRec(game.ball.position, game.ball.radius, game.paddleRight.rec) && game.ball.speed.x > 0) {
        game.ball.speed.x *= -1.1f;
        game.ball.speed.y = (game.ball.position.y - game.paddleRight.rec.y) / (game.paddleRight.rec.height / 2) * -game.ball.speed.x;
    }
}

void IsMouseCollidingPaddle()
{
    game.isMouseOverPaddle = 0;
    game.isMouseClickingPaddle = 0;
    if (CheckCollisionPointRec(GetMousePosition(), game.paddleLeft.rec)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) game.isMouseClickingPaddle = 1;
        else game.isMouseOverPaddle = 1;
    }
}

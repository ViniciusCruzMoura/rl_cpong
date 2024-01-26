#include "core\game.h"

void init_ball(CBall *ball, int scale) {
    // Init Ball
    ball->position.x = GetRenderWidth() / 2.0f;
    ball->position.y = GetScreenHeight() / 2.0f;
    ball->speed.x = 100 * scale;
    ball->speed.y = 100 * scale;
    ball->radius = 3 * scale;
}

void update_ball(CBall *ball, CPlayer *player, Sound *sfx) {
    // BALL MOVEMENT
    ball->position.x += ball->speed.x * GetFrameTime();
    ball->position.y += ball->speed.y * GetFrameTime();
    if (ball->position.y < 0) {
        ball->position.y = 0;
        ball->speed.y *= -1;
    }
    if (ball->position.y > GetScreenHeight()) {
        ball->speed.y *= -1;
    }

    // THE BALL IS COLLIDING WITH THE PADDLE
    if (CheckCollisionCircleRec(ball->position, ball->radius, player->paddleLeft.rec) && ball->speed.x < 0) {
        PlaySound(sfx[0]);      // play the next open sound slot
        ball->speed.x *= -1.1f;
        ball->speed.y = (ball->position.y - player->paddleLeft.rec.y) / (player->paddleLeft.rec.height / 2) * ball->speed.x;
    }
    if (CheckCollisionCircleRec(ball->position, ball->radius, player->paddleRight.rec) && ball->speed.x > 0) {
        PlaySound(sfx[0]);      // play the next open sound slot
        ball->speed.x *= -1.1f;
        ball->speed.y = (ball->position.y - player->paddleRight.rec.y) / (player->paddleRight.rec.height / 2) * -ball->speed.x;
    }
}

void draw_ball(CBall ball) {
    DrawCircleV(ball.position, ball.radius, WHITE);
}

#include "game.h"

void init_player(Player *player, int pos_x, int pos_y, int scale) {
    // Init Left Paddle
    player->paddleLeft.rec.x = 50;
    player->paddleLeft.rec.y = pos_y;
    player->paddleLeft.rec.width = 4 * scale;
    player->paddleLeft.rec.height = 30 * scale;
    player->paddleLeft.speed = 300 * scale;

    // Init Right Paddle
    player->paddleRight.rec.x = pos_x;
    player->paddleRight.rec.y = pos_y;
    player->paddleRight.rec.width = 4 * scale;
    player->paddleRight.rec.height = 30 * scale;
    player->paddleRight.speed = 300 * scale;
}

void update_player(Player *player, Ball *ball) {
    // PADDLE MOVEMENT
    if (IsKeyDown(KEY_W)) player->paddleLeft.rec.y -= player->paddleLeft.speed * GetFrameTime();
    if (IsKeyDown(KEY_S)) player->paddleLeft.rec.y += player->paddleLeft.speed * GetFrameTime();
    if (IsKeyDown(KEY_UP)) player->paddleRight.rec.y -= player->paddleRight.speed * GetFrameTime();
    if (IsKeyDown(KEY_DOWN)) player->paddleRight.rec.y += player->paddleRight.speed * GetFrameTime();
    
    // LEFT PADDLE ARTIFICIAL INTELLIGENCE
    if (ball->position.x > GetScreenWidth()/2 && ball->speed.x > 0) {
        int debuff = 1.0f;
        if (player->paddleRight.rec.y == ball->position.y) {
            player->paddleRight.rec.y = ball->position.y + -player->paddleRight.rec.height/2;
        } else if (player->paddleRight.rec.y - -player->paddleRight.rec.height/2 > ball->position.y) {
            player->paddleRight.rec.y -= player->paddleRight.speed/debuff * GetFrameTime();
        } else if (player->paddleRight.rec.y - -player->paddleRight.rec.height/2 < ball->position.y) {
            player->paddleRight.rec.y += player->paddleRight.speed/debuff * GetFrameTime();
        }
    }
    // RIGHT PADDLE ARTIFICIAL INTELLIGENCE
    if (ball->position.x < GetScreenWidth()/2 && ball->speed.x < 0) {
        int debuff = 1.0f;
        if (player->paddleLeft.rec.y == ball->position.y) {
            player->paddleLeft.rec.y = ball->position.y + -player->paddleLeft.rec.height/2;
        } else if (player->paddleLeft.rec.y - -player->paddleLeft.rec.height/2 > ball->position.y) {
            player->paddleLeft.rec.y -= player->paddleLeft.speed/debuff * GetFrameTime();
        } else if (player->paddleLeft.rec.y - -player->paddleLeft.rec.height/2 < ball->position.y) {
            player->paddleLeft.rec.y += player->paddleLeft.speed/debuff * GetFrameTime();
        }
    }
}

void draw_player(Player player) {
    DrawRectangleRec(player.paddleLeft.rec, WHITE);
    DrawRectangleRec(player.paddleRight.rec, WHITE);
}
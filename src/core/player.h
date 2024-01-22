#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct CPaddle CPaddle;
typedef struct CBall CBall;

typedef struct CPlayer {
    CPaddle paddleLeft;
    CPaddle paddleRight;
} CPlayer;

void init_player(CPlayer *player, int pos_x, int pos_y, int scale);
void update_player(CPlayer *player, CBall *ball);
void draw_player(CPlayer *player);

#endif // PLAYER_H
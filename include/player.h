#ifndef PLAYER_H
#define PLAYER_H

typedef struct CPaddle {
    float speed;
    Rectangle rec;
} CPaddle;

typedef struct CPlayer {
    CPaddle paddleLeft;
    CPaddle paddleRight;
} CPlayer;

void init_player(CPlayer *player, int pos_x, int pos_y, int scale);
void update_player(CPlayer *player, CBall *ball);
void draw_player(const CPlayer player);

#endif // PLAYER_H
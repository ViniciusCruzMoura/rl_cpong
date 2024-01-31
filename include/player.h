#ifndef PLAYER_H
#define PLAYER_H

typedef struct Paddle {
    float speed;
    Rectangle rec;
} Paddle;

typedef struct Player {
    Paddle paddleLeft;
    Paddle paddleRight;
} Player;

void init_player(Player *player, int pos_x, int pos_y, int scale);
void update_player(Player *player, Ball *ball);
void draw_player(const Player player);

#endif // PLAYER_H
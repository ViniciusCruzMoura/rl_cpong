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

void InitPlayer(Player *player, int pos_x, int pos_y, int scale);
void UpdatePlayer(Player *player, Ball *ball);
void DrawPlayer(const Player player);

#endif // PLAYER_H
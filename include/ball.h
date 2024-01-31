#ifndef BALL_H
#define BALL_H

typedef struct Player Player;

typedef struct Ball {
    float radius;
    Vector2 position;
    Vector2 speed;
} Ball;

void InitBall(Ball *ball, int scale);
void UpdateBall(Ball *ball, Player *player, Sound *sfx);
void DrawBall(const Ball ball);

#endif // BALL_H
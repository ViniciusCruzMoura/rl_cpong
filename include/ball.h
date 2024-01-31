#ifndef BALL_H
#define BALL_H

typedef struct Player Player;

typedef struct Ball {
    float radius;
    Vector2 position;
    Vector2 speed;
} Ball;

void init_ball(Ball *ball, int scale);
void update_ball(Ball *ball, Player *player, Sound *sfx);
void draw_ball(const Ball ball);

#endif // BALL_H
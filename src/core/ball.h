#ifndef BALL_H
#define BALL_H

typedef struct CPlayer CPlayer;

typedef struct CBall {
    float radius;
    Vector2 position;
    Vector2 speed;
} CBall;

void init_ball(CBall *ball, int scale);
void update_ball(CBall *ball, CPlayer *player, Sound *sfx);
void draw_ball(CBall *ball);

#endif // BALL_H
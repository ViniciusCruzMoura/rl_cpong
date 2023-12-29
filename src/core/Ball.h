#include "raylib.h"

typedef struct CBall {
    float radius;
    Vector2 position;
    Vector2 speed;
} CBall;

CBall InitCBall(int x, int y, int screenScale);
void DrawCBall(CBall ball);
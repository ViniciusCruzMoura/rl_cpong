#include "game.h"

typedef struct CPaddle {
    float speed;
    Rectangle rec;
} CPaddle;

CPaddle InitCPaddle(int x, int y, int screenScale);
void DrawCPaddle(CPaddle paddle);
void MoveCPaddle();
void AI_CPaddle();
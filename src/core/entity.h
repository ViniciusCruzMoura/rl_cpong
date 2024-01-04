#ifndef ENTITY_H
#define ENTITY_H

typedef struct CBall {
    float radius;
    Vector2 position;
    Vector2 speed;
} CBall;

typedef struct CPaddle {
    float speed;
    Rectangle rec;
} CPaddle;

#endif // ENTITY_H
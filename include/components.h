#ifndef COMPONENTS_H
#define COMPONENTS_H

typedef struct CFlags {
    bool isVisible;
    bool hasCollided;
    bool isCircleCollision;
    bool isRectangleCollision;
} CFlags;

typedef struct CInput {
    bool up;
    bool left;
    bool right;
    bool down; 
} CInput;

typedef struct CShape {
    float circle_radius;
    Rectangle rec;
    Color color;
} CShape;

typedef struct CCollision {
    float radius;
    Rectangle rec;
} CCollision;

typedef struct CScore {
    int score;
} CScore;

typedef struct CTransform {
    Vector2 pos;
    Vector2 velocity;
    float angle;
} CTransform;

typedef struct CLifespan {
    int remaining_life;
    int total_life;
} CLifespan;

#endif //COMPONENTS_H

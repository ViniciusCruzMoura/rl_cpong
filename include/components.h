#ifndef COMPONENTS_H
#define COMPONENTS_H

typedef struct CFlags {
    bool is_visible;
    bool has_collided;
    bool is_circle_collision;
    bool is_rectangle_collision;
} CFlags;

typedef struct CInput {
    bool up;
    bool left;
    bool right;
    bool down; 
} CInput;

typedef struct CShape {
    float radius;
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
    float rotation;
    Vector2 scale;
} CTransform;

typedef struct CLifespan {
    int remaining_life;
    int total_life;
} CLifespan;

typedef struct CAnimation {
    bool loop;
    //sprite
} CAnimation;

#endif //COMPONENTS_H

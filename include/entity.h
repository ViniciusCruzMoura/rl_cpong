#ifndef ENTITY_H
#define ENTITY_H

typedef struct Entity {
    bool m_active;
    size_t m_id;
    char *m_tag;

    //flags

    //componets
    //input
    bool up;
    bool left;
    bool right;
    bool down;
    //transform
    Vector2 pos;
    Vector2 velocity;
    float angle;
    //collision
    float radius;
    //shape
    //score
    int score;
    //lifespan
    int remaining_life;
    int total_life;

} Entity;

#endif //ENTITY_H

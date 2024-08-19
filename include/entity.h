#ifndef ENTITY_H
#define ENTITY_H

typedef struct Entity {
    bool m_active;
    size_t m_id;
    char *m_tag;

    //flags
    bool isVisible;
    bool hasCollided;
    //bool isCircleCollision; //maybe it's could be useful to change collision type
    //bool isRectangleCollision;

    //componets //i think use pointers is better
    //input
    bool up; //use the enum with status could be a better option
    bool left;
    bool right;
    bool down;
    
    //transform
    Vector2 pos;
    Vector2 velocity;
    float angle;
    
    //collision
    //float radius_collision; //rectangle collision is a alternative
    Rectangle rec_collision;
    
    //shape
    //float circle_radius; //rectangle shape is a alternative
    Rectangle rec_shape;
    Color color_shape;
    
    //score
    int score;
    
    //lifespan
    int remaining_life;
    int total_life;

} Entity;

#endif //ENTITY_H

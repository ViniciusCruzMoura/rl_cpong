#ifndef ENTITY_H
#define ENTITY_H

typedef enum
{
    ENTITY_TYPE_NOTHING = 0,
    ENTITY_TYPE_OBJECT,
    ENTITY_TYPE_PLAYER,
    ENTITY_TYPE_ENEMY,
    ENTITY_TYPE_ITEM,
} EntityTypes;

typedef struct Entity {
    bool m_active;
    size_t m_id;
    EntityTypes m_tag;

    //flags
    CFlags flags;

    //componets
    CInput input;
    CTransform transform;
    CCollision collision;
    CShape shape;
    CScore score;
    CLifespan lifespan;

} Entity;

#endif //ENTITY_H
